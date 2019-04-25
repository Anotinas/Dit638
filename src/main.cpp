#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "string.h"

void showTrackbarWindow(cv::Mat frame);
void createTrackbarWindow();

const std::string windowName = "Trackbars";

int main(int args, char** argv)
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

void createTrackbarWindow(){

    int LowH = 0;
    int HighH = 179;

    int LowS = 0; 
    int HighS = 255;

    int LowV = 0;
    int HighV = 255;

    cv::createTrackbar("Hue Low", windowName, &LowH, 179); 
    cv::createTrackbar("Sat Low", windowName, &LowS, 255); 
    cv::createTrackbar("Val Low", windowName, &LowV, 255);

    cv::createTrackbar("Hue High", windowName, &HighH, 179);
    cv::createTrackbar("Sat High", windowName, &HighS, 255);
    cv::createTrackbar("Val High", windowName, &HighV, 255);

}

void showTrackbarWindow(cv::Mat frame){
    cv::Mat hsv;
    cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV); 

    int l_h = cv::getTrackbarPos("Hue Low", windowName);
    int l_s = cv::getTrackbarPos("Sat Low", windowName);
    int l_v = cv::getTrackbarPos("Val Low", windowName);
    int u_h = cv::getTrackbarPos("Hue High", windowName);
    int u_s = cv::getTrackbarPos("Sat High", windowName);
    int u_v = cv::getTrackbarPos("Val High", windowName);

    cv::Scalar lower_blue = cv::Scalar(l_h, l_s, l_v);
    cv::Scalar upper_blue = cv::Scalar(u_h, u_s, u_v);

    cv::Mat output;
    cv::inRange(hsv, lower_blue, upper_blue, output);
    printf("LH%d\nLS%d\nLV%d\nHH%d\nHS%d\nHV%d\n",l_h,l_s,l_v,u_h,u_s,u_v);
    //Display on screen
    cv::imshow(windowName, output);
}