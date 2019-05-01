#include "calibration.h"

const std::string windowName = "MaskAdjuster";

//Max values on bar
const int HueMax = 179;
const int SatMax = 255;
const int ValMax = 255;

void calibration::createTrackbarWindow(){
    //ints to capture value change
    int HueLow = 22;
    int SatLow = 71; 
    int ValLow = 110;

    //set highs to max value on bar
    int HueHigh = 92;
    int SatHigh = 222;
    int ValHigh = 235;

    //Open window
    cv::namedWindow(windowName); 

    //Add trackbars
    cv::createTrackbar("Hue Low", windowName, &HueLow, HueMax); 
    cv::createTrackbar("Sat Low", windowName, &SatLow, SatMax); 
    cv::createTrackbar("Val Low", windowName, &ValLow, ValMax);

    cv::createTrackbar("Hue High", windowName, &HueHigh, HueMax);
    cv::createTrackbar("Sat High", windowName, &SatHigh, SatMax);
    cv::createTrackbar("Val High", windowName, &ValHigh, ValMax);
}

void calibration::showTrackbarWindow(cv::Mat frame){
    cv::Mat HSV;
    cv::cvtColor(frame, HSV, cv::COLOR_BGR2HSV); 

    //Read values of trackbar
    int lowHue = cv::getTrackbarPos("Hue Low", windowName);
    int lowSat = cv::getTrackbarPos("Sat Low", windowName);
    int lowVal = cv::getTrackbarPos("Val Low", windowName);
    int highHue = cv::getTrackbarPos("Hue High", windowName);
    int highSat = cv::getTrackbarPos("Sat High", windowName);
    int highVal = cv::getTrackbarPos("Val High", windowName);

    //3 val array containers
    cv::Scalar low = cv::Scalar(lowHue, lowSat, lowVal);
    cv::Scalar high = cv::Scalar(highHue, highSat, highVal);

    cv::Mat output; //Variable to capture mask in
    //Mask everything outside of the range of low and high
    cv::inRange(HSV, low, high, output);  

    //Write values to console
    printf("LH%d    LS%d    LV%d\nHH%d  HS%d    HV%d\n",
    lowHue,lowSat,lowVal,
    highHue,highSat,highVal);

    //Display mask on screen
    cv::imshow(windowName, output);
}