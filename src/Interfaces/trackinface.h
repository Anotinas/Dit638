#pragma once

#include <string>
#include <iostream>
#include <vector>  

#include "cvdefs.h"


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
    bool scanForMovement(cv::Mat hsv, cv::Mat frame, int rightmostBound);
    void LoadCascades();
    void detectStopSigns(cv::Mat &frame);
    void putText(std::string s,cv::Mat &frame);

    class trackinface{
        private:
            /* data */
        public:
            virtual ~trackinface();
            virtual Object detectCarAt9oclock(std::vector<Object> objects) = 0;
            virtual Object detectCarAt12oclock(std::vector<Object> objects) = 0;
            virtual Object detectCarAt3oclock(std::vector<Object> objects) = 0;
            virtual Object detectAtPosition(std::vector<Object> objects, int lowerBound,int upperBound) = 0;
            virtual void LoadCascades() = 0;
            virtual void detectStopSigns(cv::Mat &frame) = 0;
            virtual void putText(std::string s,cv::Mat &frame) = 0;
            virtual bool scanForMovement(cv::Mat hsv, cv::Mat frame, int rightmostBound) = 0;
            virtual std::vector<Object> detectObjects(cv::Mat hsv, cv::Mat &frame) = 0;
};
