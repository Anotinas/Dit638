#pragma once

#include <string>
#include <iostream>
#include <vector>  
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp> 

namespace tracking
{
    typedef struct
    {
        int x;
        int y;
    } Position;

    typedef struct
    {
        Position position;
        double area;    
    } Object;

    int detectObjects(cv::Mat hsv, cv::Mat &frame);
    void markObjects(std::vector<Object> objects,cv::Mat &frame);
    void morphFrame(cv::Mat &frame);
}