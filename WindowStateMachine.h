// WindowStateMachine.h

#ifndef _WINDOWSTATEMACHINE_h
#define _WINDOWSTATEMACHINE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif


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
	bool openWindowCommandIsActive;
	bool closeWindowCommandIsActive;
	bool stopWindowCommandIsActive;

private:
	
	bool loggingActive;
	void Log(char*);

	// State
    enum WindowState windowState = WINDOW_STOPPED;

	// Pins
	const int motorClosePin = PIN2;
	const int motorOpenPin = PIN3;
	const int sensorClosedPin = PINA0;
	const int sensorOpenedPin = PINA1;


	void stopWindow(void);
	void openWindow(void);
	void closeWindow(void);


};