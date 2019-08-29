#pragma once
#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

#include "cluon-complete.hpp"
#include "messages.hpp"

/*
class CarHandler {

    public:
    virtual auto getPedal() = 0;

    //we could not come up with a method
    //to dynamically know the distance to 
    //the intersection after our car has 
    //finished following the front car so 
    //instead it will be hardcoded
    virtual bool intersectionRoll() = 0;

    //Returns the frontsensor reading after
    //adding an auto function to update it.
    virtual auto getFrontSensor() = 0;
    virtual auto getLeftSensor() = 0;
    virtual auto getRightSensor() = 0;
    virtual auto getBackSensor() = 0;

    private:
}; 
*/


class CarHandlerv2{
    public:
    virtual bool setPedal(float pedal) = 0;
    virtual bool setDir(float dir) = 0;
    virtual float getFrontSensor() = 0;
    virtual float getLeftSensor() = 0;
    virtual float getRightSensor() = 0;
    virtual float getBackSensor() = 0;
};

class CarImplementation :public CarHandlerv2{

    bool setPedal(float pedal)override{
        return true;
    };

    bool setDir(float dir)override{
        return true;
    };

    float getFrontSensor()override{
        return 0.0;
    };
    float getLeftSensor()override{
        return 0.0;
    };
    float getRightSensor()override{
        return 0.0;
    };
    float getBackSensor() override{
        return 0.0;
    };


};