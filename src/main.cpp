#include "opencv2/opencv.hpp"
#include "cv/calibration.h"
#include "cv/tracking.h"

enum Mode {idle,following, intersection};
void doIdle(cv::Mat &frame);
void doFollow(cv::Mat &frame);
void doIntersection(cv::Mat hsv,cv::Mat &frame);

bool calibrationEnabled = false;

Mode mode = idle;

int main()
{
    
   tracking::LoadCascades();
    //Open camera
    cv::VideoCapture cap(0); 
    //Close program on failure
    if(!cap.isOpened()){ return -1; }

    cv::Mat frame, HSV;

    if(calibrationEnabled)
    {
        calibration::createTrackbarWindow(); 
    }

    //Loop until Esc btn pressed
    while(1)
    {
        if(cv::waitKey(30) >= 0) break; //Await Esc
        //Extract frame
        cap.read(frame);
        //Turn into HSV
        cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
        tracking::trackGrid(HSV,frame);
        switch(mode){
            case idle:
                doIdle(frame);
                break;
            case following:
                doFollow(frame);
                break; 
            case intersection:
                doIntersection(HSV,frame);
                break;
        }
        //show frames 
        cv::imshow("frame",frame);
        if(calibrationEnabled)
        {
            calibration::showTrackbarWindow(frame);
        }
    }
    return 0;
}

void doIdle(cv::Mat &frame)
{
     mode = intersection;
}

void doFollow(cv::Mat &frame)
{
    tracking::detectStopSigns(frame);
    //             if Stopsign recognised
    //                 register stop sign 
    //             if stop sign registered && car not moving
    //                 enter Intersection mode
    //     else
    //         stop moving
}

void doIntersection(cv::Mat hsv,cv::Mat &frame)
{
     std::vector<tracking::Object> cars = tracking::detectObjects(hsv,frame);
    tracking::Object o = tracking::detectCarAt9oclock(cars);
    if(o.area != -1)
    {
        mode = following;
    }
    //Roll up to stop line
    //     await given direction
    //         if given direction not allowed by streets signs 
    //             refuse()
    //while count cars > 0 
    //  if car detected passing by
    //  countCars--
    //     move / turn in given direction
    //     enter standby mode
}