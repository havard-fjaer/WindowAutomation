// WindowStateMachine.h

#ifndef _WINDOWSTATEMACHINE_h
#define _WINDOWSTATEMACHINE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif
#include <stdio.h>
#include <string.h>


class WindowStateMachine
{

public:

	enum WindowState { WINDOW_OPEN, WINDOW_CLOSED, WINDOW_OPENING, WINDOW_CLOSING, WINDOW_STOPPED };

	WindowStateMachine(bool);

	~WindowStateMachine();

	void init();

	void runCycle();

	bool openedSensorIsActive(void);
	bool closedSensorIsActive(void);
	bool openWindowCommandIsActive = false;
	bool closeWindowCommandIsActive = false;
	bool stopWindowCommandIsActive = false;

private:
	
	bool loggingActive;
	void Log(char*);
	char* lastLogEntry;

	// State
    enum WindowState windowState = WINDOW_STOPPED;

	// Pins
	const int motorClosePin = PIN2;
	const int motorOpenPin = PIN3;
	const int sensorClosedPin = PIN6;
	const int sensorOpenedPin = PIN7;

	void clearCommandFlags(void);

	void stopWindow(void);
	void openWindow(void);
	void closeWindow(void);


};