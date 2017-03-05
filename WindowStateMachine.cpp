// 
// 
// 

#include "WindowStateMachine.h"

WindowStateMachine::WindowStateMachine()
{
}

WindowStateMachine::~WindowStateMachine()
{
}

void WindowStateMachine::init()
{
	pinMode(motorClosePin, OUTPUT);
	pinMode(motorOpenPin, OUTPUT);
	pinMode(sensorClosedPin, INPUT);
	pinMode(sensorOpenedPin, INPUT);

	windowState = WINDOW_STOPPED;
}

void WindowStateMachine::stopWindow(void)
{
	digitalWrite(motorClosePin, LOW);
	digitalWrite(motorOpenPin, LOW);
}

void WindowStateMachine::openWindow(void)
{
	digitalWrite(motorClosePin, LOW);
	digitalWrite(motorOpenPin, HIGH);
}

void WindowStateMachine::closeWindow(void)
{
	digitalWrite(motorOpenPin, LOW);
	digitalWrite(motorClosePin, HIGH);
}
