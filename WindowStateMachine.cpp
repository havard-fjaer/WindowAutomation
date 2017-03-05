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
	pinMode(sensorClosedPin, INPUT_PULLUP);
	pinMode(sensorOpenedPin, INPUT_PULLUP);
	windowState = WINDOW_STOPPED;

	Log("WindowStateMachine::init() - End");

}

void WindowStateMachine::runCycle()
{
	WindowState newState = windowState;

	switch (windowState)
	{
	case WINDOW_OPEN:
		if (closeWindowCommandIsActive)
		{
			Log("closeWindowCommandIsActive");
			closeWindow();
			clearCommandFlags();
			newState = WINDOW_CLOSING;
		}
		break;

	case WINDOW_CLOSED:
		if (openWindowCommandIsActive)
		{
			Log("openWindowCommandIsActive");
			openWindow();
			clearCommandFlags();
			newState = WINDOW_OPENING;
		}
		break;

	case WINDOW_OPENING:
		if (stopWindowCommandIsActive)
		{
			Log("stopWindowCommandIsActive");
			stopWindow();
			clearCommandFlags();
			newState = WINDOW_STOPPED;
		}
		if (openedSensorIsActive())
		{
			Log("openedSensorIsActive()");
			stopWindow();
			newState = WINDOW_OPEN;
		}
		break;

	case WINDOW_CLOSING:
		if (stopWindowCommandIsActive)
		{
			Log("stopWindowCommandIsActive");
			stopWindow();
			clearCommandFlags();
			newState = WINDOW_STOPPED;
		}
		if (closedSensorIsActive())
		{
			Log("closedSensorIsActive()");
			stopWindow();
			newState = WINDOW_CLOSED;
		}
		break;

	case WINDOW_STOPPED:
		if (openWindowCommandIsActive)
		{
			Log("openWindowCommandIsActive");
			openWindow();
			clearCommandFlags();
			newState = WINDOW_OPENING;
		}
		if (closeWindowCommandIsActive)
		{
			Log("closeWindowCommandIsActive");
			closeWindow();
			clearCommandFlags();
			newState = WINDOW_CLOSING;
		}
		break;

	default:
		Log("UNKNOWN_STATE");
		stopWindow();
		newState = WINDOW_STOPPED;
		break;

	}
	if (windowState != newState)
	{
		Log("State change:");
		windowState = newState;
		switch (windowState)
		{
		case WINDOW_OPEN: Log("WINDOW_OPEN"); break;
		case WINDOW_CLOSED: Log("WINDOW_CLOSED"); break;
		case WINDOW_OPENING: Log("WINDOW_OPENING"); break;
		case WINDOW_CLOSING: Log("WINDOW_CLOSING"); break;
		case WINDOW_STOPPED: Log("WINDOW_STOPPED"); break;
		}
	}
}

void WindowStateMachine::clearCommandFlags() {
	openWindowCommandIsActive = false;
	closeWindowCommandIsActive = false;
	stopWindowCommandIsActive = false;
}

void WindowStateMachine::stopWindow(void)
{
	digitalWrite(motorClosePin, LOW);
	digitalWrite(motorOpenPin, LOW);
	Log("stopWindow");

}

void WindowStateMachine::openWindow(void)
{
	digitalWrite(motorClosePin, LOW);
	digitalWrite(motorOpenPin, HIGH);
	Log("openWindow");
}

void WindowStateMachine::closeWindow(void)
{
	digitalWrite(motorOpenPin, LOW);
	digitalWrite(motorClosePin, HIGH);
	Log("closeWindow");
}

bool WindowStateMachine::openedSensorIsActive(void)
{
	return !digitalRead(sensorOpenedPin);
}

bool WindowStateMachine::closedSensorIsActive(void)
{
	return !digitalRead(sensorClosedPin);
}

void WindowStateMachine::Log(char* log) {
	if (loggingActive/* && strcmp(log, lastLogEntry) != 0*/)
	{
		Serial.println(log);
		/*strcpy(log, lastLogEntry);*/
	}
}



