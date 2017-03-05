
#include "arduino.h"


class WindowStateMachine
{

public:

	WindowStateMachine(bool);
	~WindowStateMachine();

	void init();
	void runCycle();

	// Sensors
	bool openedSensorIsActive(void);
	bool closedSensorIsActive(void);

	// Command flags
	bool openWindowCommandIsActive = false;
	bool closeWindowCommandIsActive = false;
	bool stopWindowCommandIsActive = false;

private:

	// Logging
	bool loggingActive;
	void Log(char*);
	char* lastLogEntry;

	// State
	enum WindowState { WINDOW_OPEN, WINDOW_CLOSED, WINDOW_OPENING, WINDOW_CLOSING, WINDOW_STOPPED };
    enum WindowState windowState = WINDOW_STOPPED;

	// Pins
	const int motorClosePin = PIN2;
	const int motorOpenPin = PIN3;
	const int sensorClosedPin = PIN6;
	const int sensorOpenedPin = PIN7;

	// Command flags
	void clearCommandFlags(void);

	// Motor commands
	void stopWindow(void);
	void openWindow(void);
	void closeWindow(void);


};