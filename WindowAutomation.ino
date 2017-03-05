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
	Scout.setup(SKETCH_NAME, SKETCH_REVISION, SKETCH_BUILD);

	windowStateMachine = new WindowStateMachine();
	windowStateMachine->init();


	Led.blinkCyan(500, true);

	Serial.print("Initializing");
	addBitlashFunction("openwindow", (bitlash_function)openWindow);
	addBitlashFunction("closewindow", (bitlash_function)closeWindow);
	addBitlashFunction("stopwindow", (bitlash_function)stopWindow);
}


void openWindow() {
	windowStateMachine->openWindow();
}
void closeWindow() {
	windowStateMachine->closeWindow();
}
void stopWindow() {
	windowStateMachine->stopWindow();
}

void loop()
{
	Scout.loop();
}

