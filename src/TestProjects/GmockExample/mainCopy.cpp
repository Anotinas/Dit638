#include "mainCopy.h"

const int FRAME_WIDTH = 1200;
const int FRAME_HEIGHT = 600;

const int MOVEMENT_THRESHOLD = 10;

cv::Mat frame, HSV;

tracking::Object carAt9;

tracking::Object carAt12;

tracking::Object carAt3;

int carsCount = 0;

bool calibrationEnabled = false;
Mode mode = idle;

void setMode(Mode m)
{
    mode = m;
    switch(mode)
    {
        case intersection:
            for(int i = 0; i < 500; i++)
            setupIntersection();
            break;
        default:
            break;
    }
}

int mainFake()
{
    //Instaniating carAt vars //added by David
    carAt3.position.x = -1;
    carAt3.position.y = -1;
    carAt3.area = -1;

    carAt9.position.x = -1; 
    carAt9.position.y = -1; 
    carAt9.area = -1;

    carAt12.position.x = -1;
    carAt12.position.y = -1; 
    carAt12.area = -1;

    //instantiation complete
    CarHandlerv2 *CarHandler = getCarHandler();

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

        //tracking::trackGrid(HSV,frame);
        switch(mode){
            case idle:
                doIdle(frame);
                break;
            case following:
                doFollow(frame, true, CarHandler);
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

//I have to cheat on this one because something is wrong with detectStopsigns
void doFollow(cv::Mat &frame, bool stopsignDetected,CarHandlerv2 *CarHandler)
{
    //bool stopsignDetected =tracking::detectStopSigns(frame);
    //             if Stopsign recognised
    //                 register stop sign 
    //             if stop sign registered && car not moving
    //                 enter Intersection mode
    //     else
    //         stop moving
    //Test code
    //CarHandlerv2 *CarHandler = getCarHandler();
    
    if(!stopsignDetected){
       CarHandler->setPedal(0.0);
    }
    float speed = 0.2;
    while (mode==following && stopsignDetected)
    {
        float distanceReading = CarHandler->getFrontSensor();

        if (distanceReading <= 0.45) speed -= 0.1;

        if (distanceReading <= 0.225) speed -= 0.1;

        if (distanceReading <= 0.1) speed = 0.0;
                
        CarHandler->setPedal(speed);
        if(speed == 0){
            mode = intersection;
        }
    }
    
}

void doIntersection(cv::Mat hsv,cv::Mat &frame)
{
    //Roll up to stop line
    //     await given direction
    //         if given direction not allowed by streets signs 
    //             refuse()
    //Determine 12 o clock car position if we detected one earlier
    
    if(carsCount > 0)
    {
    tracking::putText(std::to_string(carsCount), frame);
        //  if car detected passing by
        bool carHasPassed = carAt12.area > 1 ?
            tracking::scanForMovement(hsv,frame,carAt12.position.x)
            :
            tracking::scanForMovement(hsv,frame,FRAME_WIDTH/3);      
        if(carHasPassed) 
        {
            carsCount--;
        }
    }
    else
    {
    tracking::putText("Time to vroom", frame);
    }

    //     move / turn in given direction
    //enter standby mode
}

void setupIntersection()
{
    //Get cars from frame
    std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
    tracking::Object o;

    if(carAt9.area < 1)
    {
        o = tracking::detectCarAt9oclock(cars);
        if(o.area > 0)
        {
            carAt9.position.x=o.position.x;
            carAt9.position.y = o.position.y; 
            carAt9.area = o.area;
            carsCount++;
        }
    }

    if(carAt12.area < 1)
    {
        o = tracking::detectCarAt12oclock(cars);
        if(o.area > 0)
        {
            carAt12.position.x=o.position.x; 
            carAt12.position.y = o.position.y; 
            carAt12.area = o.area;
            carsCount++;
        }
    }

    if(carAt3.area < 1)
    {
        o = tracking::detectCarAt3oclock(cars);
        if(o.area > 0)
        {
            carAt3.position.x=o.position.x; 
            carAt3.position.y = o.position.y; 
            carAt3.area = o.area;
            carsCount++;
        }
    }
}

CarHandlerv2 * getCarHandler(){
    CarHandlerv2 *carHandler = new CarImplementation();
    return carHandler;
}