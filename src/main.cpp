#include "main.h"

cv::Mat frame, HSV;

tracking::Object carAt9 = {.position.x = -1, .position.y = -1, .area = -1};
tracking::Object carAt12 = {.position.x = -1, .position.y = -1, .area = -1};
tracking::Object carAt3 = {.position.x = -1, .position.y = -1, .area = -1};

bool calibrationEnabled = false;
Mode mode = idle;

const int FRAME_WIDTH = 1200;
const int FRAME_HEIGHT = 600;

void setMode(Mode m)
{
    mode = m;
    switch(mode)
    {
        case intersection:
            for(int i = 0; i<10;i++)
            setupIntersection();
            break;
        default:
            break;
    }
}

int main()
{
   tracking::LoadCascades();
    //Open camera
    cv::VideoCapture cap(0); 
    //Close program on failure
    if(!cap.isOpened()){ return -1; }

    cap.set(cv::CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);

    if(calibrationEnabled)
    {
        calibration::createTrackbarWindow(); 
    }

    //Loop until Esc btn pressed
    while(1)
    {
        if(cv::waitKey(30) >= 0) break; //Await Esc
        //Extract frame
        cap.read(frame);
        //Turn into HSV
        cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);

        if(carAt3.area > 0){
            tracking::putText("sanic",frame);
        }
        //tracking::trackGrid(HSV,frame);
        switch(mode){
            case idle:
                doIdle(frame);
                break;
            case following:
                doFollow(frame);
                break; 
            case intersection:
                doIntersection(HSV,frame);
                break;
        }
        //show frames 
        cv::imshow("frame",frame);
        if(calibrationEnabled)
        {
            calibration::showTrackbarWindow(frame);
        }
    }
    return 0;
}

void doIdle(cv::Mat &frame)
{
    setMode(intersection);
}

void doFollow(cv::Mat &frame)
{
    tracking::detectStopSigns(frame);
    //             if Stopsign recognised
    //                 register stop sign 
    //             if stop sign registered && car not moving
    //                 enter Intersection mode
    //     else
    //         stop moving
}

void doIntersection(cv::Mat hsv,cv::Mat &frame)
{
   
    //Roll up to stop line
    //     await given direction
    //         if given direction not allowed by streets signs 
    //             refuse()
    //while count cars > 0 
    //  if car detected passing by
    //  countCars--
    //     move / turn in given direction
    //     enter standby mode
}

void setupIntersection()
{
    //Get cars from frame
    std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
    if(carAt9.area < 1)
    carAt9 = tracking::detectCarAt9oclock(cars);
    if(carAt12.area < 1)
    carAt12 = tracking::detectCarAt12oclock(cars);
    if(carAt3.area < 1)
    carAt3 = tracking::detectCarAt3oclock(cars);
}