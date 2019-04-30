#include "opencv2/opencv.hpp"
#include "cv/calibration.h"
#include "cv/tracking.h"

enum Mode {idle,following, intersection};
void doIdle(cv::Mat hsv, cv::Mat &frame);
void doFollow(cv::Mat &frame);
void doIntersection(cv::Mat hsv,cv::Mat &frame);

Mode mode = idle;

int main()
{
    //Open camera
    cv::VideoCapture cap(0); 
    //Close program on failure
    if(!cap.isOpened()){ return -1; }

    cv::Mat frame, HSV;

    calibration::createTrackbarWindow(); 

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
                doIdle(HSV,frame);
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
        calibration::showTrackbarWindow(frame);
   
        // Follow car mode
        //     if isCarRecognised()
        //             if Stopsign recognised
        //                 register stop sign 
        //             if stop sign registered && car not moving
        //                 enter Intersection mode
        //     else
        //         stop moving

        // Intersection mode
            //Count cars on frame
        //     await given direction
        //         if given direction not allowed by streets signs 
        //             refuse()
        //     Count cars q
        //     Roll up to stop line
        //     while count cars > 0 
        //         if car detected passing by
        //             countCars--
        //     move / turn in given direction
        //     enter standby mode
    }
   
    return 0;
}

void doIdle(cv::Mat hsv,cv::Mat &frame)
{
    std::vector<tracking::Object> cars = tracking::detectObjects(hsv,frame);
    tracking::Object o = tracking::detectCarAt9oclock(cars);
    if(o.area != -1)
    {
        mode = intersection;
    }
}

void doFollow(cv::Mat &frame)
{
}

void doIntersection(cv::Mat hsv,cv::Mat &frame)
{
     std::vector<tracking::Object> cars = tracking::detectObjects(hsv,frame);
    tracking::Object o = tracking::detectCarAt9oclock(cars);
    if(o.area == -1)
    {
        mode = idle;
    }
}