#include "opencv2/opencv.hpp"
#include "cv/calibration.h"
#include "cv/tracking.h"

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
        //Count cars on frame
        int carsCount = tracking::detectObjects(HSV,frame);
        //TODO Remove this line after debugging
        cv::putText(frame, std::to_string(carsCount), cv::Point(0,50), 1, 2, cv::Scalar(0,255,0));
        //show frames 
        cv::imshow("frame",frame);
    }

    calibration::showTrackbarWindow(frame);

    // Intersection mode
    //     detect and register streets signs
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

    // Follow car mode
    //     if isCarRecognised()
    //             if Stopsign recognised
    //                 register stop sign 
    //             if stop sign registered && car not moving
    //                 enter Intersection mode
    //     else
    //         stop moving

    return 0;
}