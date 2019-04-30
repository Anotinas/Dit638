#pragma once

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

namespace calibration{
    void showTrackbarWindow(cv::Mat frame);
    void createTrackbarWindow();
}