#include "../opencv2/opencv.hpp"
#include "cv/calibration.h"
#include "cv/tracking.h"
#include "carHandler.h"

enum Mode {idle,following, intersection};
void doIdle(cv::Mat &frame);
void doFollow(cv::Mat &frame, bool stopsignDetected, CarHandlerv2 *CarHandler);
void doIntersection(cv::Mat hsv,cv::Mat &frame, CarHandlerv2 *CarHandler);
void setupIntersection(cv::Mat hsv,cv::Mat &frame);
void setMode(Mode m);
CarHandlerv2 * getCarHandler();