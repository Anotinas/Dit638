#include "../opencv2/opencv.hpp"
#include "cv/calibration.h"
#include "cv/tracking.h"
#include "carHandler.h"

enum Mode {idle,following, intersection};
void doIdle(cv::Mat &frame);
void doFollow(cv::Mat &frame, bool stopsignDetected);
void doIntersection(cv::Mat hsv,cv::Mat &frame);
void setupIntersection();
void setMode(Mode m);
CarHandlerv2 * getCarHandler();