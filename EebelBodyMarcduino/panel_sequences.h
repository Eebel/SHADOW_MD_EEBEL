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

 // Standard servo pulses vary from 1000 us to 2000us
 //Servo that can turn 180 deg. accept pulses from 500 us to 2500 us
 //Center is at 1500 us, which is SERVO_PULSE_CENTER


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
/*Eebel Notes
 * servo 1 - DPL Door
 * servo 2 - Top Utility Arm
 * Servo 3 - Bottom Utility Arm
 * Servo 4 - Left Body Door
 * servo 5 - Left Arm Raise/Lower
 * servo 6 - Left Arm use tool
 * servo 7 - Right Body Door
 * servo 8 - Right Arm Raise/Lower
 * servo 9 - Right Arm use tool
 * servo 10- unused right now
 */

#ifndef PANEL_SEQUENCES_H_
#define PANEL_SEQUENCES_H_

#include <avr/pgmspace.h>	// for the sequencer data arrays defined with PROGMEM
#include "sequencer.h"		// servo sequencer

// Body panel sequences
//180 Degree Servos: 500-2500:  1500 Middle
//STD servos are 1000 to 2000

// pulse values for opening and closing panel servos
#define _OPN 1000 //1000
#define _CLS 2000 //was 2000


//Eebel START
// pulse values for opening and closing DPL (Data Panel Door)
#define _ODP 700 //1000
#define _CDP 2000 //was 2000


// pulse values for opening and closing UTILITY ARM servos
#define _OUTL 2500  //Was 1100, 2800, 2900,2700
#define _CUTL 1300   //Was 1970, 1300 - too much, 1400,1350,1325, 1305 - not enough closed

// pulse values for opening and closing body LEFT DOOR servo
//This rotates the opposite of right door
#define _OLD 2000 //was 2000,2500, 2300
#define _CLD 500  //was 1000, 500, 700, 600

// pulse values for opening and closing LEFT ARM Raise servos
#define _OLA 2150 //1100, 2000,2100
#define _CLA 800 //1970,500

// pulse values for opening and GRIPPER TOOL in left door servo
//This rotates the opposite of right door
#define _OGT 900 //was1200,1000,850
#define _CGT 1600  //was 1500

// pulse values for opening and closing body RIGHT DOOR servo
//This rotates the opposite of left door
#define _ORD 1000 //was 2000,1200, 500
#define _CRD 2500// was 3000, 2500,2300

// pulse values for opening and closing RIGHT ARM Raise servos
//Rotates the opposite of Left ARM Raise
#define _ORA 700  //was 1970, 500
#define _CRA 2450  //was 2500,2000,2300

// pulse values for opening and INTERFACE TOOL in RIGHT DOOR servo
//This rotates the opposite of right door
#define _OIT 2150 //was 2000,2500,2100
#define _CIT 1250  //was 1000,1500

sequence_t const utility_arms_open PROGMEM =
{
		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool
		{20, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{150, 	_CLS, 	_OUTL, 	_OUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{30, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{30, 	_CLS, 	_OUTL, 	_OUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{30, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{30, 	_CLS, 	_OUTL, 	_OUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{190, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
};


 sequence_t const panel_all_test PROGMEM =
 {
 		//Open all doors and use all tools
		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
 		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool
 		{20, 	_CDP, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{150, 	_CDP, 	_OUTL, 	_OUTL, 	_OLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS}, //Open Doors
 		{150, 	_CDP, 	_OUTL, 	_OUTL, 	_OLD,	_OLA, 	_OGT, 	_ORD, 	_ORA,	_OIT, 	_CLS}, //Raise Arms open tools
 		{300, 	_ODP, 	_OUTL, 	_OUTL, 	_OLD,	_OLA, 	_OGT, 	_ORD, 	_ORA,	_OIT, 	_CLS}, //Open DPL (it hits tool if opened first
 		{50, 	_ODP, 	_CUTL, 	_CUTL, 	_OLD,	_OLA, 	_CGT, 	_ORD, 	_ORA,	_CIT, 	_CLS}, //Close tools
 		{50, 	_ODP, 	_OUTL, 	_OUTL, 	_OLD,	_OLA, 	_OGT, 	_ORD, 	_ORA,	_OIT, 	_CLS}, //Open tools
 		{50, 	_ODP, 	_OUTL, 	_OUTL, 	_OLD,	_OLA, 	_CGT, 	_ORD, 	_ORA,	_CIT, 	_CLS}, //Close tools
 		{50, 	_ODP, 	_OUTL, 	_OUTL, 	_OLD,	_OLA, 	_OGT, 	_ORD, 	_ORA,	_OIT, 	_CLS}, //Open tools
 		{75, 	_CDP, 	_OUTL, 	_OUTL, 	_OLD,	_OLA, 	_CGT, 	_ORD, 	_ORA,	_CIT, 	_CLS}, //Close tools
 		{250, 	_CDP, 	_CUTL, 	_CUTL, 	_OLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS}, //Lower Arms
 		{200, 	_CDP, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS}, //Close Doors
 		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
 };

 sequence_t const panel_spook PROGMEM =
 {
 		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
	 	//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool
	 	{20, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{50, 	_OPN, 	_OUTL, 	_OUTL, 	_OLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS},
 		{15, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{15, 	_OPN, 	_OUTL, 	_OUTL, 	_OLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS},
 		{15, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{20, 	_OPN, 	_OUTL, 	_OUTL, 	_OLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS},
 		{20, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{10, 	_OPN, 	_OUTL, 	_OUTL, 	_OLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS},
 		{250, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
 };

 sequence_t const panel_use_gripper PROGMEM =
 {
 		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
	 	//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	Gripper	RBdyDr	RArm	IntfcTl
	 	{20, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{150, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{150, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_OLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{15, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_OLA, 	_OGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{15, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_OLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{15, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_OLA, 	_OGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{15, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_OLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{15, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_OLA, 	_OGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{20, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_OLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{175, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{250, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
 };

 sequence_t const panel_use_interface_tool PROGMEM =
 {
 		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
	 	//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	Gripper	RBdyDr	RArm	IntfcTl
	 	{20, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{150, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS},
 		{150, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_ORA,	_CIT, 	_CLS},
 		{20, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_ORA,	_OIT, 	_CLS},
 		{20, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_ORA,	_CIT, 	_CLS},
 		{20, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_ORA,	_OIT, 	_CLS},
 		{20, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_ORA,	_CIT, 	_CLS},
 		{20, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_ORA,	_OIT, 	_CLS},
 		{25, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_ORA,	_CIT, 	_CLS},
 		{20, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_ORA,	_CIT, 	_CLS},
 		{175, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS},
 		{250, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
 };

 sequence_t const panel_pingpong_Body_Doors PROGMEM =
 {
 		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
	 	//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	Gripper	RBdyDr	RArm	IntfcTl
	 	{20, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{150, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{150, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS},
 		{110, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{110, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS},
 		{80, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{80, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS},
 		{50, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{50, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS},
 		{130, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{130, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS},
 		{200, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
 		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
 };
//Eebel END

sequence_t const panel_all_open PROGMEM =
{
		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool
		{20, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{150, 	_OPN, 	_OUTL, 	_OUTL, 	_OLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS}, //Open Doors
		{150, 	_OPN, 	_NP, 	_NP, 	_NP,	_OLA, 	_OGT, 	_NP, 	_ORA,	_OIT, 	_CLS}, //Raise Arms open tools
		{50, 	_OPN, 	_NP, 	_NP, 	_NP,	_NP, 	_CGT, 	_NP, 	_NP,	_CIT, 	_CLS}, //Close tools
		{50, 	_OPN, 	_NP, 	_NP, 	_NP,	_NP, 	_OGT, 	_NP, 	_NP,	_OIT, 	_CLS}, //Open tools
		{50, 	_OPN, 	_NP, 	_NP, 	_NP,	_NP, 	_CGT, 	_NP, 	_NP,	_CIT, 	_CLS}, //Close tools
		{150, 	_OPN, 	_CUTL, 	_CUTL, 	_NP,	_CLA, 	_CGT, 	_NP, 	_CRA,	_CIT, 	_CLS}, //Lower Arms
		{200, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS}, //Close Doors
		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
};

sequence_t const panel_all_open_long PROGMEM =
{
		//Faint Body
		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool
		{20, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{500, 	_OPN, 	_OUTL, 	_OUTL, 	_OLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS},
		{500, 	_OPN, 	_OUTL, 	_OUTL, 	_OLD,	_OLA, 	_NP, 	_ORD, 	_ORA,	_NP, 	_NP},
		{300, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS},
		{300, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP}
};


sequence_t const panel_wave PROGMEM =
{
		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool
		{30, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{50, 	_OPN, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{50, 	_CLS, 	_OUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{50, 	_CLS, 	_CUTL, 	_OUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{50, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{50, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_OLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{50, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_OLA, 	_OGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
		{50, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_CLS},
		{50, 	_CLS, 	_CUTL, 	_CUTL, 	_OLD,	_CLA, 	_CGT, 	_ORD, 	_ORA,	_CIT, 	_CLS},
		{50, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_ORA,	_OIT, 	_CLS},
		{50, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_ORD, 	_CRA,	_CIT, 	_OPN},
		{150, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
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
		//Eebel
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool
		{130, 	_CLS, 	_CUTL, 	_CUTL, 	_CLD,	_CLA, 	_CGT, 	_CRD, 	_CRA,	_CIT, 	_CLS},
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

//Eebel START
int16_t panel_medium_speed[]={25,25,25,25,25,25,25,25,25,25};
//Eebel END

int16_t panel_slow_speed[]={15,15,15,15,15,15,15,15,15,15};

int16_t panel_super_slow_speed[]={9,9,9,9,9,9,9,9,9,9};


#endif /* PANEL_SEQUENCES_H_ */
