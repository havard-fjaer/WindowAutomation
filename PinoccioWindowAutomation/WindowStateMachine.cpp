
#include "WindowStateMachine.h"

WindowStateMachine::WindowStateMachine(bool loggingActive)
{
	WindowStateMachine::loggingActive = loggingActive;
}

WindowStateMachine::~WindowStateMachine()
{
}

// Initialize pins and state.
void WindowStateMachine::init()
{
	Log("WindowStateMachine::init()");
	pinMode(motorClosePin, OUTPUT);
	pinMode(motorOpenPin, OUTPUT);
	pinMode(sensorClosedPin, INPUT_PULLUP);
	pinMode(sensorOpenedPin, INPUT_PULLUP);
	windowState = WINDOW_STOPPED;
}


// Check sensors and command flags based on current state -- and act accordingly.
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
		windowState = newState;
		switch (windowState)
		{
			// TODO: Find something more elegant, such as a dicitionary.
		case WINDOW_OPEN: Log("WINDOW_OPEN"); break;
		case WINDOW_CLOSED: Log("WINDOW_CLOSED"); break;
		case WINDOW_OPENING: Log("WINDOW_OPENING"); break;
		case WINDOW_CLOSING: Log("WINDOW_CLOSING"); break;
		case WINDOW_STOPPED: Log("WINDOW_STOPPED"); break;
		}
	}
}

// Need to remember clearing all flags when running a command in order to avoid strange behaviour.
void WindowStateMachine::clearCommandFlags() {
	openWindowCommandIsActive = false;
	closeWindowCommandIsActive = false;
	stopWindowCommandIsActive = false;
}

/*** Motor commands ***/

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

/*** Sensors ***/

bool WindowStateMachine::openedSensorIsActive(void)
{
	return !digitalRead(sensorOpenedPin);
}

bool WindowStateMachine::closedSensorIsActive(void)
{
	return !digitalRead(sensorClosedPin);
}

/*** Logging ***/

void WindowStateMachine::Log(char* log) {
	if (loggingActive)
	{
		Serial.println(log);
	}
}



