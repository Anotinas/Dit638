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

    std::vector<Object> detectObjects(cv::Mat hsv, cv::Mat &frame);
    void markObjects(std::vector<Object> objects,cv::Mat &frame);
    void morphFrame(cv::Mat &frame);
    Object detectCarAt9oclock(std::vector<Object> objects);
    Object detectCarAt12oclock(std::vector<Object> objects);
    Object detectCarAt3oclock(std::vector<Object> objects);
    Object detectAtPosition(std::vector<Object> objects, int lowerBound,int upperBound);
    void doSHit(cv::Mat hsv,cv::Mat &frame);
    void trackGrid(cv::Mat hsv,cv::Mat &frame);

}