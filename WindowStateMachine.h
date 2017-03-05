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

	WindowStateMachine();

	~WindowStateMachine();

	void init();

	void stopWindow(void);

	void openWindow(void);

	void closeWindow(void);

private:
	

	// State
	enum windowState { WINDOW_OPEN, WINDOW_CLOSED, WINDOW_OPENING, WINDOW_CLOSING, WINDOW_STOPPED };
    enum windowState windowState = WINDOW_STOPPED;

	// Pins
	const int motorClosePin = PIN2;
	const int motorOpenPin = PIN3;
	const int sensorClosedPin = PINA0;
	const int sensorOpenedPin = PINA1;

};