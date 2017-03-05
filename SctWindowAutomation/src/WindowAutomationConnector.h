/* Generated by YAKINDU Statechart Tools for Arduino v0.4.0 */

#ifndef WINDOWAUTOMATIONCONNECTOR_H
#define WINDOWAUTOMATIONCONNECTOR_H

#include <Arduino.h>
#include "../src-gen/HardwareConnector.h"
#include "../src-gen/WindowAutomation.h"

class WindowAutomationConnector: public HardwareConnector {
public:
	WindowAutomationConnector(WindowAutomation* statemachine);

	inline ~WindowAutomationConnector();

	/*
	 * Initialize the hardware.
	 */
	void init();

	/*
	 * Raise state machine events before processing them in the state machine's runCycle().
	 */
	void raiseEvents();

	/*
	 * Update the hardware depending on the state machine's state.
	 */
	void syncState();

	/*
	 * Optimize power consumption by turning off modules that are not needed.
	 * Return one of the following sleep states:
	 * SLEEP_MODE_IDLE, SLEEP_MODE_ADC, SLEEP_MODE_PWR_DOWN, SLEEP_MODE_PWR_SAVE,
	 * SLEEP_MODE_STANDBY, SLEEP_MODE_EXT_STANDBY
	 * The returned sleep mode is just a recommendation, the actual timer implementation
	 * may not support the given sleep mode.
	 */
	uint8_t prepareSleepMode();
	
private:
	WindowAutomation* statemachine;
};
	
WindowAutomationConnector::~WindowAutomationConnector() {
}

#endif /* WINDOWAUTOMATIONCONNECTOR_H */
