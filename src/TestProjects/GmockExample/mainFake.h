#include "opencv2/opencv.hpp"
#include "../../cv/calibration.h"
#include "../../cv/tracking.h"

enum Mode {idle,following, intersection};
void doIdle(cv::Mat &frame);
void doFollow(cv::Mat &frame);
void doIntersection(cv::Mat hsv,cv::Mat &frame);
void setupIntersection();
void setMode(Mode m);