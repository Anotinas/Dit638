//
// pch.h
// Header for standard system include files.
//

#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../cv/tracking.h"
#include "memoryCheck.h"
#include <thread>
#include "GmockExample/mainCopy.h"
#include "GmockExample/carHandler.h"

class carMock : public CarHandlerv2{
	public:
		MOCK_METHOD(bool, setPedal,(float pedal), (override));
		MOCK_METHOD(bool, setDir,(float dir), (override));
		MOCK_METHOD(float, getFrontSensor,(),(override));
		MOCK_METHOD(float, getLeftSensor,(),(override));
		MOCK_METHOD(float, getRightSensor,(),(override));
		MOCK_METHOD(float, getBackSensor,(),(override));
};
