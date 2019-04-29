#include "tracking.h"

const cv::Scalar CAR_LOW_HSV = cv::Scalar(22,71,110);
const cv::Scalar CAR_HIGH_HSV = cv::Scalar(92,222,235);

//Returns number of objects found on frame
int tracking::detectObjects(cv::Mat hsv,cv::Mat &frame)
{
    cv::Mat tracer; //Frame to be ___ANNIHILATED___ so objects are less likely to be identified as multiple objects
    cv::inRange(hsv, CAR_LOW_HSV, CAR_HIGH_HSV, tracer);
    morphFrame(tracer);

    //Output arrays
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    //Find filtered contours
    cv::findContours(tracer,contours,hierarchy,cv::RETR_CCOMP,cv::CHAIN_APPROX_SIMPLE);

    const int minArea = 250; //Filter detection by size to minimise false readings

    std::vector <Object> objects; //Dynamic list of objects found
    if (hierarchy.size() > 0)
    {
        for (int i = 0, size = hierarchy.size(); i <= size-1; i++)
        {
            cv::Moments moment = cv::moments((cv::Mat)contours[i]);
            double area = moment.m00;
            if(area > minArea)
            {
                //Push object found to array
                Object o = 
                {
                    .position.x =  static_cast<int>(moment.m10/area),
                    .position.y =  static_cast<int>(moment.m01/area),
                    .area = area
                };
                objects.push_back(o);
            }
        }
        //Draw objects found to screen
        markObjects(objects,frame);
    }
    return hierarchy.size();
}

void tracking::markObjects(std::vector<Object> objects,cv::Mat &frame)
{
    for(int i =0; i<objects.size(); i++)
    {
        cv::circle(
            frame,
            cv::Point(objects.at(i).position.x,objects.at(i).position.y),
            sqrt((int) objects.at(i).area)/2,
            cv::Scalar(255,0,0)
        );
    }
}

void tracking::morphFrame(cv::Mat &frame)
{
    int iteration = 3; //Number of iterations for erode and dilute

    //Kernels for morphological ops
    cv::Mat erodeElement = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(5,5));
    cv::Mat dilateElement = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(10,10));

    //Ruin the image beyond reason
    cv::erode(frame,frame,erodeElement, cv::Point(-1,-1),iteration);
    cv::dilate(frame,frame,dilateElement, cv::Point(-1,-1),iteration);
}
