#include "opencv2/opencv.hpp"
#include "cv/color_calibration.h"

int main()
{
    //Open camera
    cv::VideoCapture cap(0); 
    //Close program on failure
    if(!cap.isOpened()){ return -1; }

    createTrackbarWindow(); 

    //Loop until Esc btn pressed
    while(1)
    {
        if(cv::waitKey(30) >= 0) break;

        //Extract frame
        cv::Mat frame;
        cap >> frame;

        showTrackbarWindow(frame);
        //cv::imshow("frame", frame);
    }

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