/************************************
* Header for sending messages to the vroom
* Author: Filip Fatic
* Date: 2019-04-22
* Version: 0.1
*************************************/
#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>
#include "cluon-complete.hpp"

class mservice_controller{
	//constants
	//IDs for sensors, used to check which sensor the data is coming from
	public:
	uint16_t status;

	//variables

	//functions
	mservice_controller();
	void controllerThread(cluon::OD4Session *od4);
	void sendSpeed(float speed, cluon::OD4Session *od4);
	void sendSteer(float steering, cluon::OD4Session *od4);
	float readSensorData(uint16_t sensor);
};

