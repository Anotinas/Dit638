/*****************
 * First test of making the car autonomously drive and follow another car.
 * Author: Filip Fatic
 * Date: 2019-04-15
 * Version: 1.0
 *****************/

#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

#include "cluon-complete.hpp"
#include "messages.hpp"

int32_t main(int32_t argc, char **argv) {
    
    //Initial operations for program,
    //including but not limited to checking for command line args, checking for an od4 session
    //and base for reading sensor distance
    //copied from example code provided by Yue Kang and Christian Berger

    auto commandlineArguments = cluon::getCommandlineArguments(argc, argv);

    if ( (0 == commandlineArguments.count("cid")) || (0 != commandlineArguments.count("help")) )
    {
        std::cerr << argv[0] << " is an example application for miniature vehicles (Kiwis) of DIT638 course." << std::endl;
        std::cerr << "Usage:  " << argv[0] << " --cid=<CID of your OD4Session> [--freq=<Frequency>] [--verbose] [--help]" << std::endl;
        std::cerr << "example:  " << argv[0] << " --cid=112 --freq=30 --verbose" << std::endl;
        return -1;
    }
    else
    {
        //starts OD4 session using provided cid
        //cid is hardcoded to 112
        cluon::OD4Session od4{static_cast<uint16_t>(std::stoi(commandlineArguments["cid"]))};

        if (0 == od4.isRunning())
        {
            std::cerr << "ERROR: No OD4Session running!!!" << std::endl;
            return -2;
        }
        
        //enables additional debug info if specified in command line
        const bool VERBOSE{commandlineArguments.count("verbose") != 0};

        //sets specific frequency of something
        //TODO check what something is LUL
        const float FREQ{(commandlineArguments["freq"].size() != 0) ? static_cast<float>(std::stof(commandlineArguments["freq"])) : static_cast<float>(-1.0)};

        float distanceReading{0.0};
        
        //function keeps reading the distance reading and stores it in a variable
        auto onDistanceReading
        {
            [VERBOSE, &distanceReading](cluon::data::Envelope &&envelope)
            {
                //defines how close to an object the car must be to stop
                const float PROXIMITY_LIMIT = 6.0;

                //auto is necessary because each message is it's own type
                //could put proxy as the superclass instead, but idk if this will have consequences
                auto message = cluon::extractMessage<opendlv::proxy::DistanceReading>(std::move(envelope));
                const uint16_t stamp = envelope.senderStamp();
                
                if(stamp == 0) 
                {
                    distanceReading = msg.distance();
                    if(VERBOSE)
                    {
                        std::cout << "onCarDetected: Received distance reading from front: " << distanceReading << std::endl;
                    }
                }
            }
        };
        od4.dataTrigger(opendlv::proxy::DistanceReading::ID(), onDistanceReading);
        
        auto sendCarSpeed
        {
            [VERBOSE, &distanceReading]() -> bool
            {
                opendlv::proxy::pedalPositionRequest pedalReq;
                float speed = 0.4;
                //checks the bracket for each distance and breaks if it's too close
                switch(distanceReading)
                {
                    case (distanceReading <= 0.675):
                    speed -= 0.1;

                    case (distanceReading <= 0.45):
                    speed -= 0.1;

                    case (distanceReading <= 0.225):
                    speed -= 0.1;

                    case (distanceReading <= 0.1):
                    speed -= 0.1;
                }
                pedalReq.position(speed);
                od4.send(pedalReq);
                if(VERBOSE)
                {
                    std::cout << "sendCarSpeed: Setting speed to: " << speed << std::endl;
                }
                return true;
            }
        };

        while(od4.isRunning())
        {
            sendCarSpeed();
        }
        return 0;
    }  
}