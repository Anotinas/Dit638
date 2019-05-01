#include "tracking.h"

const cv::Scalar CAR_LOW_HSV = cv::Scalar(22,71,110);
const cv::Scalar CAR_HIGH_HSV = cv::Scalar(92,222,235);

const int frameBound = 1200;
const int gridUnit = frameBound/5;

const int left = 240;
const int leftMid =  480;
const int mid = 720;
const int rightMid = 960;
const int right = 1200;

const int carAt12XPos = -1;

cv::CascadeClassifier stopSignCascade;

void tracking::LoadCascades()
{
    stopSignCascade.load("/Users/mokkants/Documents/workspace/cpp/car/src/cv/classifiers/Stopsign_HAAR_19Stages.xml");
}

tracking::Object tracking::detectAtPosition(std::vector<tracking::Object> objects, int lowerBound,int upperBound)
{
    tracking::Object o;
    for(int i = 0; i < objects.size(); i++)
    {
        o = objects.at(i);
        if(o.position.x >= lowerBound && o.position.x <= upperBound )
        {
            return o;
        }
    }
    o = {.position.x = -1, .position.y=-1, .area=-1};
    return o;
}

tracking::Object tracking::detectCarAt9oclock(std::vector<tracking::Object> objects)
{
   return detectAtPosition(objects,0,left);
}

tracking::Object tracking::detectCarAt12oclock(std::vector<tracking::Object> objects)
{
   return detectAtPosition(objects,left,leftMid);
}

tracking::Object tracking::detectCarAt3oclock(std::vector<tracking::Object> objects)
{
   return detectAtPosition(objects,mid,right);
}

//Returns number of objects found on frame
std::vector<tracking::Object> tracking::detectObjects(cv::Mat hsv,cv::Mat &frame)
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

    std::vector <tracking::Object> objects; //Dynamic list of objects found
    if (hierarchy.size() > 0)
    {
        for (int i = 0, size = hierarchy.size(); i <= size-1; i++)
        {
            cv::Moments moment = cv::moments((cv::Mat)contours[i]);
            double area = moment.m00;
            if(area > minArea)
            {
                //Push object found to array
                tracking::Object o = 
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
    return objects;
}

void tracking::markObjects(std::vector<tracking::Object> objects,cv::Mat &frame)
{
    for(int i =0; i<objects.size(); i++)
    {
        cv::circle(
            frame,
            cv::Point(objects.at(i).position.x,objects.at(i).position.y),
            sqrt((int) objects.at(i).area)/2,
            cv::Scalar(255,0,0)
        );
        cv::putText(frame, std::to_string(objects.at(i).position.x),cv::Point(objects.at(i).position.x,objects.at(i).position.y), 1, 2, cv::Scalar(0,255,0));
        cv::putText(frame, std::to_string(objects.at(i).position.y),cv::Point(objects.at(i).position.x,objects.at(i).position.y-50), 1, 2, cv::Scalar(0,255,0));
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

bool carDetected = false;
int carNotSeenForFrames = 0;

//Run after car rolls up to stop line
bool tracking::scanForMovement(cv::Mat hsv, cv::Mat frame,int rightmostBound)
{
    int centerThreshold = 50;
    std::vector<tracking::Object> cars = tracking::detectObjects(hsv,frame);
    tracking::Object car = detectAtPosition(cars, 0, rightmostBound-centerThreshold);

    //If we detect any car at the leftmost part of the screen
    if(car.area > -1)
    {
        carDetected = true;
        if(carNotSeenForFrames > 0){
            carNotSeenForFrames = 0;
        }
    }

    if(car.area < 1 && carDetected && carNotSeenForFrames >= 50)
    {
        carDetected = false;
        return true;
    }
    else if(car.area < 1 && carDetected)
    {
        carNotSeenForFrames++;
        return false;
    }

    return false;
}

void tracking::detectStopSigns(cv::Mat &frame)
{
    cv::putText(frame, "followMode", cv::Point(0,50), 1, 2, cv::Scalar(255,0,0));
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

    std::vector<cv::Rect> stopSigns;

    stopSignCascade.detectMultiScale(gray, stopSigns,10, 1,0, cv::Size(1,1));

    if(stopSigns.size()>0)
    {
        cv::putText(frame, "thats", cv::Point(0,150), 1, 2, cv::Scalar(255,0,0));
    }
}

void tracking::putText(std::string s,cv::Mat &frame)
{
    cv::putText(frame, s, cv::Point(0,50), 1, 2, cv::Scalar(255,0,0));
}