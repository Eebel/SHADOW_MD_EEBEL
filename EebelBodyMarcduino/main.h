/*
 * main.h
 * 		MarcDuino Master (Dome Panel Control)
 *      Author: Marc Verdiell
 *      v1.7
 *
 *      See description in implementation file
 *
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h> 		// uint8_t and companions

/********* BUILD SETTINGS FOR ALL VARIANTS, COMMENT OUT TO CHANGE OPTION *******************/
#define _RELEASEVERSION_		// comment out for private release version
#define _MP3TRIGGER_			// uncomment to use MP3 Trigger sounds instead of CF-III
#define _MARCDUINOV2_			// for the V2 boards
/*****************************************************************************************/

// turn to 1 for debug only
#define _ERROR_MSG_ 0
#define _FEEDBACK_MSG_ 0

// defaults to private version settings when _RELEASEVERSION_ is undefined
#ifndef _RELEASEVERSION_
#define _PRIVATEVERSION_		// settings for my own droid
#endif


// settings for the public release version are here
#ifdef _RELEASEVERSION_
	//#define _9600BAUDSJEDI_				// for future compatibility with new version of JEDI display
#endif

// settings for my own droid version are here
#ifdef _PRIVATEVERSION_
	#define _DIGITALJEDI_					// my JEDI setting is non-standard
//#define _9600BAUDSJEDI_				// for future compatibility with new version of JEDI display
#endif

// experimental, reset WiFly if TCP connection lost for more than timer (30s)
// Assumes the Wifly Reset is on PC2/AUX1
#define TCP_TIMER_VALUE 30*COUNT_PER_SECOND
#define WIFLY_RESETPIN  2
#define WIFLY_RESETPORT PORTC

#define CMD_MAX_LENGTH   64		//Max length of the command string

// all commands must start with one of these characters
#define PANEL_START_CHAR 	':'
#define HP_START_CHAR		'*'
#define DISPLAY_START_CHAR 	'@'
#define SOUND_START_CHAR 	'$'
#define ALT1_START_CHAR		'!'	// for custom extensions, messages get forwarded on SUART2 (PC4) pin of master DomePanel Marcduino
#define ALT2_START_CHAR		'%'	// for custom extensions, messages get forwarded on SUART2 (PC4) pin of slave HPPanel Marcduino
#define I2C_START_CHAR		'&' // for outputting an i2c commands on all the boards

#define CMD_END_CHAR 	'\r'// all command must end with one of these characters

// I2C control characters (not used, hard coded for now)
#define CMD_SEP_CHAR	','		// separator for I2C arguments
#define CMD_HEX_CHAR	'x' 	// for hex numbers
#define CMD_CHAR_CHAR	'\'' 	// char delimiter
#define CMD_STR_CHAR	'"'		// string delimiter

// Panel command vocabulary
#define CMD_SEQUENCE 	"SE"		// launches a sequence
#define CMD_OPEN 		"OP"		// opens a panel (00=all panels)
#define CMD_CLOSE 		"CL"		// closes a panel, removes from RC, kill servos (00=all panels)
#define CMD_RC			"RC"		// put the panels under RC control (0=remove all, >=11 put them all)
#define CMD_STOP		"ST"		// buzz kill/soft hold: remove a panel from RC control, turn servo off (0=all)
#define CMD_HOLD		"HD"		// hard hold: remove panel from RC and hold in last position (0=all that where on RC)

/*
//Eebel START - define open and close Defaults for all servos.
//An OPEN value greater than close moves clockwise
//An OPEN value less then CLOSE moves counter clockwise
//I am use servos that travel 180 degress so range is 500 to 2500 with 1500 in the middle
//Most servos only need to travels 90 degrees
#define SERVO1_OPEN 1500  //Data Panel
#define SERVO1_CLOSE 2500
#define SERVO2_OPEN 2500  //Top Utility Arm
#define SERVO2_CLOSE 1300
#define SERVO3_OPEN 2500  //Bottom Utility Arm
#define SERVO3_CLOSE 1300
#define SERVO4_OPEN 2500  //Left Body Door
#define SERVO4_CLOSE 700
#define SERVO5_OPEN 2000  //Left Arm Raise/lower
#define SERVO5_CLOSE 500
#define SERVO6_OPEN 1200  //Left Arm Tool - Gripper Tool
#define SERVO6_CLOSE 1500
#define SERVO7_OPEN 500  //Right Body Door
#define SERVO7_CLOSE 2300
#define SERVO8_OPEN 500  //Right Arm Raise/lower
#define SERVO8_CLOSE 2000
#define SERVO9_OPEN 2500  //Right Arm Tool - Interface Tool
#define SERVO9_CLOSE 1500
#define SERVO10_OPEN 1500  //CBI Door OPEN/CLOSE
#define SERVO10_CLOSE 2500
#define SERVO11_OPEN 1500  //Currently Unused
#define SERVO11_CLOSE 2500
#define SERVO12_OPEN 1500  //Currently Unused
#define SERVO12_CLOSE 2500
//Eebel END
*/


void echo(char ch);
uint8_t build_command(char ch, char* output_str);
void dispatch_command(char* command_str);
void parse_panel_command(char* command, uint8_t length);
void parse_hp_command(char* command,uint8_t length);
void parse_display_command(char* command,uint8_t length);
void parse_sound_command(char* command,uint8_t length);
void parse_alt1_command(char* command, uint8_t length);
void parse_alt2_command(char* command, uint8_t length);
void process_command(char* thecommand, char* theargument);
void sequence_command(uint8_t value);
void open_command(uint8_t value);
void close_command(uint8_t value);
void rc_command(uint8_t value);
void stop_command(uint8_t value);
void hold_command(uint8_t value);

// i2c parsing (v1.8)
void parse_i2c_command(char* command,uint8_t length);
void sendI2C(uint8_t address, uint8_t* payload, uint8_t payload_length);
uint8_t append_token(uint8_t* payload, uint8_t* index, char* token);


void init_jedi();
void resetJEDIcallback();


////////////////////////////////////////////
// below are the internally generated
// serial commands (not sent directly by R2 Touch)
// Mostly to generate sequence scripts
///////////////////////////////////////////

// Perform HP actions
void HPOff();
void HPOn();
void HPStop();
void HPRandom();
void HPFlicker(uint8_t seconds);
void HP1Flicker(uint8_t seconds);
void HPFlash(uint8_t seconds);
void HP1RC();

// Perform Magic Panel actions
void MagicFlash(uint8_t seconds);
void MagicFlicker(uint8_t seconds);

// Perform Display actions
void DisplayNormal();
void DisplayScream();
void DisplayFlash4();
void DisplaySpectrum();
void DisplayShortCircuit();
void DisplayLeia();

// RLD text
void RLDSetMessage(char* message);
void RLDDisplayMessage();

// Perform Sound
void Sound(uint8_t bank, uint8_t number);
void SoundScream();
void SoundWave();
void SoundDisco();
void SoundFastWave();
void SoundOpenWave();
void SoundBeepCantina();
void SoundFaint();
void SoundCantina();
void SoundLeia();
void SoundRandom();
void SoundStop();



#endif /* MAIN_H_ */
