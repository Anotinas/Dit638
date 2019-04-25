#ifndef COLOR_CALIBRATION_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define COLOR_CALIBRATION_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

void showTrackbarWindow(cv::Mat frame);
void createTrackbarWindow();

#endif