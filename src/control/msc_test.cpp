/************************************
* Class used to smoke test the mservice_controller
* Author: Filip Fatic
* Date: 2019-04-18
* Version: 0.1
*************************************/

#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

#include "cluon-complete.hpp"
#include "messages.hpp"
#include "mservice_controller.h"

    int32_t main()
    {
        cluon::OD4Session od4val{static_cast<uint16_t>(112)};
        cluon::OD4Session *od4 = &od4val;
        mservice_controller msc;
        msc.controllerThread(od4);
        /*cunt->controllerThread();
        float testData = cunt->readSensorData(0);
        std::cout << "Test data: " << testData << std::endl;

        cunt->sendSpeed(0.4);*/
        return 0;
    }