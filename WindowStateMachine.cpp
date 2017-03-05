// 
// 
// 

#include "WindowStateMachine.h"

WindowStateMachine::WindowStateMachine(bool la)
{
	loggingActive = la;
}

WindowStateMachine::~WindowStateMachine()
{
}

void WindowStateMachine::init()
{
	Log("WindowStateMachine::init() - Start");

	pinMode(motorClosePin, OUTPUT);
	pinMode(motorOpenPin, OUTPUT);
	pinMode(sensorClosedPin, INPUT);
	pinMode(sensorOpenedPin, INPUT);
	windowState = WINDOW_STOPPED;

	Log("WindowStateMachine::init() - End");

}

void WindowStateMachine::runCycle()
{
	WindowState newState = windowState;

	switch (windowState)
	{
	case WINDOW_OPEN:
		Log("WINDOW_OPEN");
		if (closeWindowCommandIsActive)
		{
			closeWindow();
			closeWindowCommandIsActive = false;
			newState = WINDOW_CLOSING;
		}
		break;

	case WINDOW_CLOSED:
		if (openWindowCommandIsActive)
		{
			openWindow();
			openWindowCommandIsActive = false;
			newState = WINDOW_OPENING;
		}
		break;

	case WINDOW_OPENING:
		if (openedSensorIsActive())
		{
			stopWindow();
			newState = WINDOW_OPEN;
		}
		break;

	case WINDOW_CLOSING:
		if (closedSensorIsActive())
		{
			stopWindow();
			newState = WINDOW_CLOSED;
		}
		break;

	case WINDOW_STOPPED:
		if (openWindowCommandIsActive)
		{
			openWindow();
			openWindowCommandIsActive = false;
			newState = WINDOW_OPENING;
		}
		if (closeWindowCommandIsActive)
		{
			closeWindow();
			closeWindowCommandIsActive = false;
			newState = WINDOW_CLOSING;
		}
		break;

	default:
		stopWindow();
		newState = WINDOW_STOPPED;
		break;

	}
	windowState = newState;
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

bool WindowStateMachine::openedSensorIsActive(void)
{
	return digitalRead(sensorOpenedPin);
}

bool WindowStateMachine::closedSensorIsActive(void)
{
	return digitalRead(sensorClosedPin);
}

void WindowStateMachine::Log(char* log) {
	if (loggingActive)
		Serial.println(log);
}



