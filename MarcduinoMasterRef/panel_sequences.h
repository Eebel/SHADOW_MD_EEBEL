/*
 * panel_sequences.h
 *
 *  Created on: Aug 5, 2012
 *  Author: Marc Verdiell
 *  Defines the sequences matrices for the dome panel moves
 *  Each of them is stored in program memory
 *  See sequencer.h for details on how to declare and use them
 *  See examples on how they are used in main.c
 *
 */

/************ example of how to use the sequencer
* define a sequence matrix like this
* make sure to follow exactly this declaration to put the array in program memory
* (it needs the const and the PROGMEM):

	sequence_t const servo_dance PROGMEM=
	{
			// time	servo1	servo2	servo3	servo4
			{50, 	1000, 	1000, 	1000, 	1000},
			{50, 	2000, 	1000, 	1000, 	1000},
			{50, 	1000, 	2000, 	1000, 	1000},
			{50, 	1000, 	1000, 	2000, 	1000},
			{50, 	1000, 	1000, 	1000, 	2000},
			{50, 	1000, 	1000, 	1000, 	1000},
			{50, 	2000, 	2000, 	1000, 	1000},
			{50, 	1000, 	1000, 	1000, 	1000},
			{50, 	1000, 	1000, 	2000, 	2000},
			{50, 	1500, 	1500, 	1500, 	1500},
			{0, 	_NP, 	_NP, 	_NP, 	_NP},
	};

	// time units are 1/100 seconds. Max is 65535.
	// 10 is 1/10 of a second
	// 100 is 1 second
	// 1000 is 10 second
	// 6000 is a minute
	// 36000 is 6 minutes

	// optionally define a speed matrix for each servo, (0 = max speed, larger numbers = lower speed)
	int16_t servo_dance_speed[]={50,20,0,20};


	in main() or elsewhere call:

	seq_loadsequence(servo_dance, SEQ_SIZE(servo_dance));		// SEQ_SIZE macro defined in sequencer.h to calculate the sequence length
	seq_loadspeed(servo_dance_speed);							// optional, to set the speed of servos
	seq_startsequence();

	To stop it:
	seq_stopsequence();

**************************************/
#ifndef PANEL_SEQUENCES_H_
#define PANEL_SEQUENCES_H_

#include <avr/pgmspace.h>	// for the sequencer data arrays defined with PROGMEM
#include "sequencer.h"		// servo sequencer

// Dome panel sequences

// pulse values for opening and closing panel servos
#define _OPN 1000
#define _CLS 2000




sequence_t const panel_all_open PROGMEM =
{
		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
		{20, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{300, 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN},
		{150, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
};

sequence_t const panel_all_open_long PROGMEM =
{
		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
		{20, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{1000, 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN},
		{150, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
};


sequence_t const panel_wave PROGMEM =
{
		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
		{30, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{30, 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{30, 	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{30, 	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{30, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{30, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{30, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{30, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS},
		{30, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS},
		{30, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS},
		{30, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN},
		{30, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
};

sequence_t const panel_fast_wave PROGMEM=
{
		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
};



sequence_t const panel_open_close_wave PROGMEM=
{
		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
		{20, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{20, 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{20, 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{20, 	_OPN, 	_OPN, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{20, 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{20, 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{20, 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{20, 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_CLS,	_CLS, 	_CLS},
		{20, 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS},
		{20, 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS},
		{80, 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN},
		{20, 	_CLS, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN},
		{20, 	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN},
		{20, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN},
		{20, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN},
		{20, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN},
		{20, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_OPN},
		{20, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN},
		{20, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_OPN},
		{20, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN},
		{40, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
};

sequence_t const panel_marching_ants PROGMEM =
{
		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
		{20, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{50, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{50, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{50, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{50, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{50, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{50, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{50, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{50, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{50, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{50, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{50, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{50, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{50, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{50, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{50, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{50, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{50, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{50, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{50, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{50, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{50, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{50, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{50, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{50, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{50, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{50, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{50, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{50, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{50, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{50, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{100, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
};

sequence_t const panel_dance PROGMEM =
{
		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
		{20, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS}, // 4 pie, 1 by one
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_OPN},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS}, // 4 side, 1 by one
		{45, 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_OPN, 	_OPN, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS}, // 4 pies. 2 by 2
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_OPN},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS}, // 2 large sides
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS}, // interleaved
		{45, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS}, // 2nd interleaved
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_OPN},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{45, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{45, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{45, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS}, //
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{45, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{45, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN},
		{45, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS}, //
		{45, 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_OPN, 	_OPN},
		{45, 	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS},
		{45, 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_OPN, 	_OPN},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS}, // transition
		{45, 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_OPN, 	_OPN, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_OPN, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS}, // Good
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_OPN},
		{45, 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{45, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
};
sequence_t const panel_init PROGMEM =
{
		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
		{100, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
};

// 6min26sec disco sequence to trigger callback at the right time
sequence_t const panel_long_disco PROGMEM=
{
		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS},
		{15, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS}, // 3.45 seconds
		{36000, _NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP},  // 6 minutes
		{2200, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP},  // 22 seconds
		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
};
int16_t panel_fast_speed[]={0,0,0,0,0,0,0,0,0,0};

int16_t panel_slow_speed[]={15,15,15,15,15,15,15,15,15,15};

int16_t panel_super_slow_speed[]={9,9,9,9,9,9,9,9,9,9};


#endif /* PANEL_SEQUENCES_H_ */
