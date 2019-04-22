#include "opencv2/opencv.hpp"

int main(int args, char** argv)
{
    //Open camera
    cv::VideoCapture cap(0); 
    //Close program on failure
    if(!cap.isOpened()){ return -1; } 

    //Loop until Esc btn pressed
    while(1)
    {
        if(cv::waitKey(30) >= 0) break;

        //Extract frame
        cv::Mat frame;
        cap >> frame; 
        //Display on screen
        cv::imshow("frame", frame);
    }
    return 0;
}