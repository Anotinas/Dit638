/*************************************
* Controller class that handles microservices
* related to moving the car and reading sensor output.
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


    static float m_dataFront, m_dataBack, m_dataLeft, m_dataRight = 0.0; 
    mservice_controller::mservice_controller()
    {

    }
    //status = 0;

    const uint16_t SENSOR_FRONT = 0;
	const uint16_t SENSOR_BACK = 1;
	const uint16_t SENSOR_LEFT = 2;
	const uint16_t SENSOR_RIGHT = 3;

    void /***/mservice_controller::controllerThread(cluon::OD4Session *od4)
    {
        //od4 = new cluon::OD4Session(112);
        if(od4->isRunning() == 0)
        {
            std::cerr << "ERROR: No od4 session running." << std::endl;
            status = -1;
            exit(-1);
            //pthread_exit(-1);
        }

        //function that constantly reads distance for every sensor
        auto onDistanceReading
            {
                //the keyword this just straight up accesses all vars in this file's scope
                //there was no other way i am sorry
                [this](cluon::data::Envelope &&envelope)
                {
                    //auto is necessary because each message is it's own type
                    auto message = cluon::extractMessage<opendlv::proxy::DistanceReading>(std::move(envelope));
                    const uint16_t stamp = envelope.senderStamp();
                    
                    //this should be a switch but i'm honestly too lazy to change it now
                    if(stamp == SENSOR_FRONT) 
                    {
                        m_dataFront = message.distance();
                    }
                    else if(stamp == SENSOR_BACK)
                    {
                        m_dataBack = message.distance();
                    }
                    else if(stamp == SENSOR_LEFT)
                    {
                        m_dataLeft = message.distance();
                    }
                    else if(stamp == SENSOR_RIGHT)
                    {
                        m_dataRight = message.distance();
                    }
                }
            };
        od4->dataTrigger(opendlv::proxy::DistanceReading::ID(), onDistanceReading);
    }

    //sends the speed at which the car should move
    //ranges from 0 to 1, but dont do 1
    //fastest value I personally use is 0.4
    //use negative to go backwards
    bool mservice_controller::sendSpeed(float speed, cluon::OD4Session od4)
    {
        auto sendCarSpeed
        {
            [&od4, &speed]()-> bool
            {
                //creates a pedal request to fill with data and send
                opendlv::proxy::PedalPositionRequest pedalReq;
                
                //sets the speed and sends it to the car
                pedalReq.position(speed);
                od4.send(pedalReq);

                return true;
            }
        };
        return false;
    }
        //make method for ultrasonic sensor output

    //returns data read from corresponding sensor
    //NOTE TO ARAZ: Write a unit test for this by creating a mock
    //for the sensors please and thank you
    float mservice_controller::readSensorData(uint16_t sensor)
    {
        switch(sensor)
        {
            case SENSOR_FRONT:
            return m_dataFront;
            break;

            case SENSOR_BACK:
            return m_dataBack;
            break;

            case SENSOR_LEFT:
            return m_dataLeft;
            break;

            case SENSOR_RIGHT   :
            return m_dataRight;
            break;

            default:
            throw new std::invalid_argument("mservice_controller: Invalid sensor ID provided");
            break;
        }
    }