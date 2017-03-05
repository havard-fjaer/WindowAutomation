#include "WindowStateMachine.h"
#include <bitlash.h>
#include <SleepHandler.h>
#include <Shell.h>
#include <ScoutHandler.h>
#include <Scout.h>
#include <Pinoccio.h>
#include "version.h"


WindowStateMachine* windowStateMachine;

void setup()
{
	Serial.println("Initializing");
	Scout.setup(SKETCH_NAME, SKETCH_REVISION, SKETCH_BUILD);
	windowStateMachine = new WindowStateMachine(true);
	windowStateMachine->init();
	initBitlashFunctions();
	Serial.println("Initializing Done");
}

void loop()
{
	Scout.loop();
	windowStateMachine->runCycle();
}

// Connecting blitlash commands to commands in the state machine
void initBitlashFunctions(void) {
	addBitlashFunction("openwindow", (bitlash_function)openWindow);
	addBitlashFunction("closewindow", (bitlash_function)closeWindow);
	addBitlashFunction("stopwindow", (bitlash_function)stopWindow);
}

void openWindow() {
	windowStateMachine->openWindowCommandIsActive = true;
}

void closeWindow() {
	windowStateMachine->closeWindowCommandIsActive = true;
}

void stopWindow() {
	windowStateMachine->stopWindowCommandIsActive = true;
}


