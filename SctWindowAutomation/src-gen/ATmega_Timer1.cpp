/* Generated by YAKINDU Statechart Tools for Arduino v0.4.0 */

#include "ATmega_Timer1.h"

bool runCycleFlag = false;

ISR(TIMER1_COMPA_vect) {
	runCycleFlag = true;
}

ATmega_Timer1::ATmega_Timer1(StatemachineInterface* statemachine, HardwareConnector* hardware,
		unsigned char maxParallelTimeEvents, unsigned int period) {
	this->statemachine = statemachine;
	this->hardware = hardware;
	this->maxParallelTimeEvents = maxParallelTimeEvents;
	this->period = period;
	
	events = new TimeEvent[maxParallelTimeEvents];
	for (unsigned char i = 0; i < maxParallelTimeEvents; i++) {
		events[i].eventId = NULL;
	}
}

void ATmega_Timer1::start() {
	statemachine->init();
	statemachine->enter();
	hardware->init();
	init();
}

void ATmega_Timer1::init() {
	// initialize Timer1
	noInterrupts();
	TCCR1A = 0;     // set entire TCCR1A register to 0
	TCCR1B = 0;     // same for TCCR1B
	
	// set compare match register to desired timer count
	// period in ms, Arduino runs at 16 MHz, prescaler at 1024
	OCR1A = (period * 0.001f * (16000000 / 1024)) - 1;
	
	// turn on CTC mode
	TCCR1B |= (1 << WGM12);
	
	// Set CS12 and CS10 bits for 1024 prescaler
	TCCR1B |= (1 << CS12);
	TCCR1B |= (1 << CS10);
	
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);
	
	// enable global interrupts
	interrupts();
}

void ATmega_Timer1::setTimer(TimedStatemachineInterface* timedStatemachine, sc_eventid eventId, sc_integer duration,
		sc_boolean isPeriodic) {
	for (unsigned char i = 0; i < maxParallelTimeEvents; i++) {
		if (events[i].eventId == NULL) {
			events[i].timedStatemachine = timedStatemachine;
			events[i].eventId = eventId;
			events[i].overflows = duration / period;
			events[i].periodic = isPeriodic;
			events[i].overflowCounter = 0;
			events[i].eventRaised = false;
			break;
		}
	}
}

void ATmega_Timer1::unsetTimer(TimedStatemachineInterface* timedStatemachine, sc_eventid eventId) {
	for (unsigned char i = 0; i < maxParallelTimeEvents; i++) {
		if (events[i].eventId == eventId) {
			events[i].eventId = NULL;
			break;
		}
	}
}

void ATmega_Timer1::runCycle() {
	if (runCycleFlag) {
		raiseTimeEvents();
		hardware->raiseEvents();
		statemachine->runCycle();
		hardware->syncState();
		runCycleFlag = false;
	}
	sleep();
}

void ATmega_Timer1::raiseTimeEvents() {
	for (unsigned char i = 0; i < maxParallelTimeEvents; i++) {
		if (events[i].eventId == NULL) {
			continue;
		}
	
		events[i].overflowCounter++;
	
		if ((events[i].overflowCounter >= events[i].overflows) && !events[i].eventRaised) {
			events[i].timedStatemachine->raiseTimeEvent(events[i].eventId);
			events[i].overflowCounter = 0;
	
			if (!events[i].periodic) {
				events[i].eventRaised = true;
			}
		}
	}
}

void ATmega_Timer1::sleep() {
	hardware->prepareSleepMode();
	
	set_sleep_mode(SLEEP_MODE_IDLE);
	noInterrupts();
	sleep_enable();
	interrupts();
	sleep_cpu();
	sleep_disable();
}

void ATmega_Timer1::cancel() {
	TCCR1B = 0; // turn off the timer
}