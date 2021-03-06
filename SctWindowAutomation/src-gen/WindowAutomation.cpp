/* Generated by YAKINDU Statechart Tools for Arduino v0.4.0 */

#include "WindowAutomation.h"
#include <string.h>

/*! \file Implementation of the state machine 'WindowAutomation'
*/

WindowAutomation::WindowAutomation()
{
	
	
	stateConfVectorPosition = 0;
	
}

WindowAutomation::~WindowAutomation()
{
}


void WindowAutomation::init()
{
	for (int i = 0; i < maxOrthogonalStates; ++i)
		stateConfVector[i] = WindowAutomation_last_state;
	
	stateConfVectorPosition = 0;

	clearInEvents();
	clearOutEvents();
	
}

void WindowAutomation::enter()
{
	/* Default enter sequence for statechart WindowAutomation */
	enseq_main_region_default();
}

void WindowAutomation::exit()
{
	/* Default exit sequence for statechart WindowAutomation */
	exseq_main_region();
}

sc_boolean WindowAutomation::isActive()
{
	return stateConfVector[0] != WindowAutomation_last_state;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean WindowAutomation::isFinal()
{
   return false;}

void WindowAutomation::runCycle()
{
	
	clearOutEvents();
	
	for (stateConfVectorPosition = 0;
		stateConfVectorPosition < maxOrthogonalStates;
		stateConfVectorPosition++)
		{
			
		switch (stateConfVector[stateConfVectorPosition])
		{
		case main_region_StateA :
		{
			react_main_region_StateA();
			break;
		}
		default:
			break;
		}
	}
	
	clearInEvents();
}

void WindowAutomation::clearInEvents()
{
}

void WindowAutomation::clearOutEvents()
{
}


sc_boolean WindowAutomation::isStateActive(WindowAutomationStates state)
{
	switch (state)
	{
		case main_region_StateA : 
			return (sc_boolean) (stateConfVector[0] == main_region_StateA
			);
		default: return false;
	}
}

WindowAutomation::DefaultSCI* WindowAutomation::getDefaultSCI()
{
	return &iface;
}



// implementations of all internal functions

/* 'default' enter sequence for state StateA */
void WindowAutomation::enseq_main_region_StateA_default()
{
	/* 'default' enter sequence for state StateA */
	stateConfVector[0] = main_region_StateA;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for region main region */
void WindowAutomation::enseq_main_region_default()
{
	/* 'default' enter sequence for region main region */
	react_main_region__entry_Default();
}

/* Default exit sequence for state StateA */
void WindowAutomation::exseq_main_region_StateA()
{
	/* Default exit sequence for state StateA */
	stateConfVector[0] = WindowAutomation_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for region main region */
void WindowAutomation::exseq_main_region()
{
	/* Default exit sequence for region main region */
	/* Handle exit of all possible states (of WindowAutomation.main_region) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case main_region_StateA :
		{
			exseq_main_region_StateA();
			break;
		}
		default: break;
	}
}

/* The reactions of state StateA. */
void WindowAutomation::react_main_region_StateA()
{
	/* The reactions of state StateA. */
}

/* Default react sequence for initial entry  */
void WindowAutomation::react_main_region__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_main_region_StateA_default();
}


