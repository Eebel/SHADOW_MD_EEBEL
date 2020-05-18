/*
 * 	main.c
 *  MarcDuino Master (Dome Panel Controller)
 *  Created on: July 4th, 2012
 *  Author: Marc Verdiell
 *  Version 1.4r: original release 03/26/2013
 *  Version 1.5: with hololights commands, fix panel glitch
 *  Version 1.6: new sound: CF-III program, MP3 and R2 Touch all modified, cleanup of sequences
 *  Version 1.7: MarcDuino v2 support
 *  Version 1.8: I2C command parsing support, revised serial.c and i2c.h
 *
 */

/***********************
 *  Version 1.8:
 *  I2C command parsing support
 *  Updated serial.c and serial.h libraries
 *  	Changed serial_puts so it waits for available output buffer by default
 *  	If not characters were just dropped when sending too much data.
 *  	Renamed previous version serial_puts_nowait
 *  Updated the comments in i2c.h
 *  Tried hardware reset of the WiFly through AUX1 pin connected to pin 5 on Wifly
 *  	Not quite working yet. Commented out in production
 *
 ***********************/

/***********************
 *  Version 1.7:
 *
 *  MarcDuino V2 support
 *  	SUART2 sound output pin changed from PC4 to PC1 (made conditional change to suart.c)
 *  	SUART slave output still PC0 no change
 *  	Enable I2C Pins PC4 (SDA) and PC5 (SCL) (needed to convert i2C master library to use dynamic timers)
 *  	MP3 Trigger sounds startup on random by default to match R2 Touch
 *  	Suppress error messages for WiFly protection
 *
 ***********************/


/***********************
 *  Version 1.6:
 *
 *  Prepare for MP3Trigger and Teeces versions
 *  	Made abstract calls for all sounds and display actions
 *  	Code Naming of CF-III commands changed
 *  		Orchestral Cantina is now $C\r (was D)
 *  		Beep Cantina is now $c\r (was a $8 "sing" category file, now an unused category)
 *  		Disco is now D (used to be M, which is the Imperial March now)
 *  		All special sounds have a call letter code now
 *  Implements sequence completion callbacks
 *  	Works nicely around the JEDI not resetting properly after some modes
 *  	Returns own holos to default state
 *  Move in MP3Trigger code library
 *  	Was developed in MP3Sound-Dev project
 *
 ***********************/


/***********************
 *  Version 1.5:
 *  Merge private and release code (using compile switches)
 *  Adapt to new library
 *  	realtime.c 	- use dynamically registered callbacks and timers
 *  	serial.c	- refactor for cleaner semantics, pgm strings support
 *  Memory optimization
 *  	Strings constants moved to program memory
 *  Generate commands for new on-board connected HP Lights
 *  Support of two alternate start characters for custom expansion
 *  Disabled interrupts while transmitting in suart.h -> improved reliability
 *  Change to serial buffered/interrupt implementation
 *  	Fixed panel servo glitch due RX ISR was way too long.
 *  Reduce delays after JEDI commands now that suart is more reliable
 *  Add completion callback at end of sequences
 *  	Use to reset JEDI at the end of sequences that have bar graph display
 *
 ***********************/


/***********************
 *  Version 1.4r: original release 03/26/2013
 ***********************/

/** Command implementation
 *
 * Hardware setup: the board has
 * 	- 10 servo outputs for the dome panel doors
 * 	- one suart (suart) at 9600 bauds connected the slave HP Controller board
 * 	- a second suart (suart2) at 2400 bauds with RS232 level translation
 * 	- the main UART input at 9600 bauds connected to the XBee radio
 * 	- one RC input connected to a RC channel
 *
 * Every command must start with one of these special characters (defined in the hearder file)
 * The start character is recognized in the main loop:
 *
 * ":" Pie panel command, parsed and treated by this controller in the "process_command" routine
 * "*" HP commands, passed on to the HoloController board daisy chained to suart1, see "parse_hp_command"
 * "@" Display commands, also passed to the HoloController board, see "parse_display_command"
 * "$" Sound commands, passed to the CFIII sound controller on suart2 "parse_sound_command"
 * "!" Alt1 alternate sound command, passed to suart2 after stripping
 * "%" Alt2 alternate HP board command, passed to suart without stripping
 *		The slave HP board will output it on suart2 after stripping
 *
 * Panel commands
 * They must follow the syntax ":CCxx\r" where CC=command , xx= two digit decimal number, \r is carriage return
 * The following commands are recognized in v1.4 (in process_command)
 * :SExx launches sequences, see below
 * :OPxx open panel number xx=01-10. If xx=00, opens all panels
 * 		OP11= open top panels
 * 		OP12= open bottom panels
 * :CLxx close panel number xx=01-10, removes from RC if it was, stops servo. If xx=00, all panels, slow close.
 * :RCxx places panel xx=01-10 under RC input control. If xx=00, all panels placed on RC.
 * :STxx buzz kill/soft hold: removes panel from RC control AND shuts servo off to eliminate buzz.
 * 		xx=00 all panels off RC servos off.
 * :HDxx RC hold: removes from RC, but does not turn servo off, keeps at last position. xx=00 all panels hold.
 *
 *	Sequences details (see sequence_command, panel sequence matrices defined in panel_sequences.h)
 *	:SE00 Close all panels (full speed), servo off - use as init only. Use CL00 for all soft close.
 *	:SE01 Scream, with all panels open
 *	:SE02 Wave, one panel at a time
 *	:SE03 Fast (Smirk) back and forth wave
 *	:SE04 Wave 2 (open progressively all panels, then close one by one)
 *	:SE05 Beep Cantina (with marching ants panel action)
 *	:SE06 Faint/Short Circuit
 *	:SE07 Cantina dance (orchestral, rythmic panel dance)
 *	:SE08 Leia
 *	:SE09 Disco
 *	:SE10 Quite Mode reset (panel close, stop holos, stop sounds)
 *	:SE11 Full Awake Mode reset (panel close, random sound, holo movement, no holo lights)
 *	:SE12 Top Panels to RC
 *	:SE13 Mid Awake Mode reset (panel close, random sound, stop holos)
 *	:SE14 Awake+ Mode reset ((panel close, random sound, holo movement, lights on)
 *	:SE15 Screams no panels
 *  :SE16 Maxstang Wiggle and scream
 *	:SE17 WaveBye and WaveByeSound
 *
 *	Panel Moves Only
 *	:SE51 Scream, with all panels open
 *	:SE52 Wave, one panel at a time
 *	:SE53 Fast (Smirk) back and forth wave
 *	:SE54 Wave 2 (open progressively all panels, then close one by one)
 *	:SE55 Marching ants
 *	:SE56 Faint/Short Circuit
 *	:SE57 Rythmic panel dance)

 */

#include "main.h"

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>  // needed for the UART interrupt
#include <avr/pgmspace.h>	// for the sequencer data arrays defined with PROGMEM

#include <stdlib.h>			// for itoa(), integer to string conversion
#include <errno.h>			// for errors on atoi (check errno)
#include <stdio.h>			// for sprintf(), don't use if you are short on memory
#include <string.h>			// for strlen()


#include "toolbox.h"
#include "servo.h"			// servo drivers
#include "realtime.h"		// real time interrupt services
#include "serial.h"			// hardware serial
#include "suart.h"			// software serial (write only)
#include "sequencer.h"		// servo sequencer
#include "panel_sequences.h"	// panel sequences, moved off to another file for clarity

#ifdef _MP3TRIGGER_
#include "wmath.h"			// random
#include "mp3sound.h"
#endif

#ifdef _MARCDUINOV2_
#include "i2c.h"			// include I2C Master libraries for MarcDuino v2
#endif

// command globals
char command_buffer[CMD_MAX_LENGTH];		// command string buffer
uint8_t panel_rc_control[SERVO_NUM];		// flag array for which panels are under RC control
uint8_t panel_to_silence[SERVO_NUM];		// flag array for servos we need to turn off after a panel is closed

// set to 1 for debug, right now turning quiet not to mess up the WiFly during development
uint8_t errormessageon=_ERROR_MSG_;
uint8_t feedbackmessageon=_FEEDBACK_MSG_;

// timeout counter
rt_timer killbuzz_timer;

//### experimental: timer to close TCP connection if no data received, for 3 seconds
rt_timer TCP_timer;


// string constants are in program memory to save DRAM
const char strOK[] PROGMEM="OK\n\r";
const char strWelcome[] PROGMEM="\n\rMarcDuino Master v1.7 \n\r";
const char strEnterPrompt[] PROGMEM="Enter panel command starting with \':\' \n\r";
const char strSuart1OK[] PROGMEM="\n\rsuart1 Communication OK \n\r";
const char strSuart2OK[] PROGMEM="\n\rsuart2 Communication OK \n\r";
const char strStartCharErr[] PROGMEM="**Unrecognized Command Start Character\r\n";
const char strInitializing[] PROGMEM="Initializing...\r\n";

// utility to echo characters back cleanly
void echo(char ch)
{
	// echo return and line feeds nicely on a terminal
	if(ch=='\r' || ch=='\n' || ch == 0x0D )
	{
		serial_putc('\n');
		serial_putc('\r');
	}
	else serial_putc(ch);
}


int main(void) {

	// start hardware and software UARTs, send check string
	serial_init_9600b8N1();	// 9600 bauds, 8 bits, 1 stop, no parity, use for a regular terminal console
	serial_puts_p(strWelcome);
	serial_puts_p(strInitializing);


	// output test string on the Software UART on PC0
	// communicates with HPController MarcDuino board
	suart_init(9600);
	suart_puts_p(strSuart1OK);

#ifndef _MP3TRIGGER_
	// output test string on the suart2 on PC4 (MarcDuino v1) or PC1 (MarcDuino v2)
	// communicates with the CFIII sound controller
	suart2_init(9600);
	suart2_puts_p(strSuart2OK);
#endif

	// initialize servo, realtime and sequencer units
	servo_init();
	realtime_init();
	seq_init();

#ifdef _MARCDUINOV2_
	// initialize I2C hardware on MarcDuino v2's with 10k pull-up resistors on.
	i2c_init(TRUE);
#endif

	// register our buzz kill timer
	rt_add_timer(&killbuzz_timer);
	//### experimental
	digitalMode(WIFLY_RESETPORT, WIFLY_RESETPIN, OUTPUT);	// Wifly reset on PC2/AUX1
	digitalWrite(WIFLY_RESETPORT,WIFLY_RESETPIN,HIGH);		// deactivate reset
	rt_add_timer(&TCP_timer);

	// run a close sequence on the panels to make sure they are all shut
	seq_loadsequence(panel_init, SEQ_SIZE(panel_init));
	seq_startsequence();

#ifdef _MP3TRIGGER_
	// MP3 Trigger connects on suart2 on PC4 (MarcDuino v1) or PC1 (MarcDuino v2)
	suart2_init(9600);
	// Initialize the MP3Trigger sound driver
	_delay_ms(3000);	// need to wait for MP3 to power up
	// The mp3_init will also trigger the startup sound
	mp3_init();
	// wait for the startup sound to finish and start the random sound sequence
	_delay_ms(10000);
	mp3_start_random();
#endif

	// ready
	serial_puts_p(strEnterPrompt);
	TCP_timer=TCP_TIMER_VALUE;

  while (1)
  {
	/////////////////////////////////////////
	// Serial Command Input
	////////////////////////////////////////
	char command_str[CMD_MAX_LENGTH];
	bool command_available;

	// check for command line input
	if(serial_available())
	{
		//### experimental, reset TCP timeout timer
		TCP_timer=TCP_TIMER_VALUE;

		char ch;
		ch=serial_getc();										// get input
		echo(ch);												// echo back
		command_available=build_command(ch, command_str);		// build command line
		if (command_available) dispatch_command(command_str);	// send command line to dispatcher
	}

	///////////////////////////////////////////
	// ### experimental code to reset the Wifly if TCP connection times out
	// but even the Wifly reset does not fix what appears to be a DHCP problem
	/////////////////////////////////////////////

	/***************
	if(!TCP_timer) // strobe the WiFly reset pin
	{
		//serial_puts("TCP lost, resetting Wifly\r\n");
		digitalWrite(WIFLY_RESETPORT, WIFLY_RESETPIN, LOW);
		_delay_ms(20);
		digitalWrite(WIFLY_RESETPORT, WIFLY_RESETPIN, HIGH);
		TCP_timer=TCP_TIMER_VALUE;
	}
	**************/

	///////////////////////////////////////////
	// ### experimental code to close the Wifly TCP connection if timed out
	// but the Wifly does not seem to respond to the close command
	// when in AP mode
	/////////////////////////////////////////////

	/*********************
	if(!TCP_timer) // send a close port command
	{
		serial_disable_rx_interrupt();
		serial_puts("TCP lost, attempt to close TCP Connection\r\n");
		_delay_ms(400);
		serial_puts("$$$");
		_delay_ms(600);
		serial_puts("\r");
		serial_puts("\rclose\r");
		_delay_ms(600);
		serial_puts("\rexit\r");
		_delay_ms(400);
		serial_enable_rx_interrupt();
		TCP_timer=TCP_TIMER_VALUE;
	}
	*******************/




	////////////////////////////////////////
	// MP3 Trigger Random Sounds
	///////////////////////////////////////
#ifdef _MP3TRIGGER_
	// need to call this in main loop for random sounds to work
	mp3_do_random();
#endif

	/////////////////////////////////////////
	// RC Control of Panels
	////////////////////////////////////////
	int16_t servovalue= servo_RCread();
	uint8_t i;
	for(i=1; i<=SERVO_NUM; i++)
	{
		if(panel_rc_control[i-1]==1)
		{
			//automatically kill servo buzz by turning off servo if door is almost closed
			if(servovalue > _CLS -10)
			{
				// servo was not silenced yet
				if(panel_to_silence[i-1]==0 && servo_read(i)!=_NP)
				{
					servo_set(i, _CLS); 			// close servo
					killbuzz_timer=COUNT_PER_SECOND/3;	// wait 1/3 s for it to close
					panel_to_silence[i-1]=1;		// then silence it
				}
			}
			else
			{
				servo_set(i, servovalue);
			}
		}
	}

	// kill servo buzz if panel have been marked as just closed and the timeout period has expired
	if(killbuzz_timer==0)
	{
		for(int i=1; i<=SERVO_NUM; i++)
		{
			if(panel_to_silence[i-1])
			{
				servo_set(i,_NP);
				panel_to_silence[i-1]=0;
			}
		}
	}

	// simple debug RC input test: loopback input to servo
	// servo_set(2, servo_RCread());

	/***** simple input RC diagnostic test: prints out the RC input value
	char string[17]; 				// put outside while loop?
	sprintf(string, "RC-in: %04d \r\n", servo_RCread());
	serial_puts(string);
	********/

  } // end of while loop
return 0;
}

// builds the command string from the character input
uint8_t build_command(char ch, char* output_str)
{
	static uint8_t pos=0;

	switch(ch)
	{
		case CMD_END_CHAR:								// end character recognized
			command_buffer[pos]='\0';					// append the end of string character
			pos=0;										// reset buffer pointer
			strcpy(output_str, (char*)command_buffer);	// copy result
			return TRUE;								// return and signal command ready
			break;

		default:										// regular character
			command_buffer[pos]=ch;						// append the  character to the command string
			if(pos<=CMD_MAX_LENGTH-1)pos++;				// too many characters, discard them.
			break;
	}
	return FALSE;
}

// dispatches further command processing depending on start character
void dispatch_command(char* command_str)
{
	char start_char=command_str[0];
	uint8_t length=strlen(command_str);

	// prompt on empty command to show life at console
	if(length==0)
	{
		serial_puts_p(strOK);
		return;
	}

	// dispatch the command to the appropriate parser depending on start character
	switch(start_char)
	{
	 case PANEL_START_CHAR:
		 parse_panel_command(command_str, length);
		 break;
	 case HP_START_CHAR:
		 parse_hp_command(command_str, length);
		 break;
	 case DISPLAY_START_CHAR:
		 parse_display_command(command_str,length);
		 break;
	 case SOUND_START_CHAR:
		parse_sound_command(command_str,length);
		break;
	 case ALT1_START_CHAR:
		parse_alt1_command(command_str,length);
		break;
	 case ALT2_START_CHAR:
		parse_alt2_command(command_str,length);
		break;
	 case I2C_START_CHAR:
		 parse_i2c_command(command_str,length);
		 break;
	 default:
		if(errormessageon) serial_puts_p(strStartCharErr);
		 break;
	}
}

const char strHPCommand[] PROGMEM="HP command\r\n";
void parse_hp_command(char* command, uint8_t length)
{
	if(feedbackmessageon) serial_puts_p(strHPCommand);
	// pass on command to hp controller on suart
	suart_puts(command);
	// need to add the \r which is not part of the command string
	suart_putc('\r');
}

const char strDisplayCommand[] PROGMEM="Display command\r\n";
void parse_display_command(char* command, uint8_t length)
{
	if(feedbackmessageon) serial_puts_p(strDisplayCommand);
	// pass on command to hp controller on suart
	suart_puts(command);
	// need to add the \r which is not part of the command string
	suart_putc('\r');
}

const char strSoundCommand[] PROGMEM="Sound command\r\n";
void parse_sound_command(char* command,uint8_t length)
{
	if(feedbackmessageon) serial_puts_p(strSoundCommand);

#ifdef _MP3TRIGGER_
	// pass on command to our own MP3_Trigger interpreter
	mp3_parse_command(command);
#else
	// pass on raw command to CF-III via suart2
	suart2_puts(command);
	// need to add the \r which is not part of the command string
	suart2_putc('\r');
#endif
}

// for custom/future expansion, forwarded to suart2 with start character dropped
const char strAlt1Command[] PROGMEM="Alt1 command, output to sound\r\n";
void parse_alt1_command(char* command, uint8_t length)
{
	if(feedbackmessageon) serial_puts_p(strAlt1Command);
	suart2_puts(command+1);  // discard the start character
	suart2_putc('\r');		 // add the termination character

}

// for custom/future expansion, forwarded to HP MarcDuino,
// which will forward it to it's suart2 after stripping
const char strAlt2Command[] PROGMEM="Alt2 command, forward to slave\r\n";
void parse_alt2_command(char* command, uint8_t length)
{
	if(feedbackmessageon) serial_puts_p(strAlt1Command);
	suart_puts(command);   	// keep the start character
	suart_putc('\r');		// add the termination character
}


const char strI2CCmdErr[] PROGMEM="**Invalid I2C Command\r\n";
void parse_i2c_command(char* cmd, uint8_t length)
{
	/*****************************************
	 * I2C Command structure:
	 *
	 * &device_address(in decimal),<arg>,<arg>,<arg>\r
	 *
	 * Where <arg> is to be sent on i2c as a byte according to
	 * one of four converions:
	 * 	decimal number: 210 (no prefix, max 255, min -128)
	 * 	hex number: xA7 (x prefix, max FF)
	 * 	single char: 'c' (' prefix, optional ' at the end)
	 * 	ASCII string:"hello world (" prefix, no other " at the end)
	 *
	 * Note that numbers are one byte max. To send larger numbers
	 * you have to break them in hex bytes and send them one byte
	 * at a time
	 *
	 * To debug it is useful to set #define _FEEDBACK_MSG_ 1
	 * in main.h, it shows how it interpreted the command payload
	 * on the serial console output
	 *
	 */

	uint8_t i2caddress=0;
	uint8_t payload[256];
	uint8_t payloadIndex=0;
	uint8_t success=0;
	const char delim[]=",";
	char* token;
	//### for debug output
#if _FEEDBACK_MSG_ == 1
	char str[65];
#endif

	// a properly constructed command should have at least 2 chars
	if (length<2)
	{
		if(errormessageon) serial_puts_p(strI2CCmdErr);
#if _FEEDBACK_MSG_ == 1
		serial_puts("Err 1\n\r");
#endif
		return;
	}

	// check first character '&' begins command
	if(cmd[0]!=I2C_START_CHAR)
	{
		if(errormessageon) serial_puts_p(strI2CCmdErr);
#if _FEEDBACK_MSG_ == 1
		serial_puts("Err 2\n\r");
#endif
		return;
	}

	// good enough to send on to the next slave
	// so all slaves execute the same I2C command
	suart_puts(cmd);
	suart_putc('\r');	// add the termination character

	// get the address field. Need to tokenize on the next "," or "\0"
	token = strtok(cmd+1, delim);
	if(token == NULL )
	{
		if(errormessageon) serial_puts_p(strI2CCmdErr);
#if _FEEDBACK_MSG_ == 1
		serial_puts("Err 3\n\r");
#endif
		return;
	}

	// convert and check the address
	unsigned int temp;
	success=sscanf(token, "%u", &temp);
	//i2caddress=atoi(token);
	// make sure I can do the conversion to uint8_t
	if(temp<255) i2caddress=(uint8_t)temp;
	else success=0;

	//### confirm first address token is read correctly
#if _FEEDBACK_MSG_ == 1
	if (success) sprintf(str, "Token: %s, recognized address: %u \r\n", token, i2caddress);
	else sprintf(str, "Token: %s, unrecognized address\r\n", token);
	serial_puts(str);
#endif

	if(i2caddress > 127 || !success)
	{
		if(errormessageon) serial_puts_p(strI2CCmdErr);
#if _FEEDBACK_MSG_ == 1
		serial_puts("Err 4\n\r");
#endif
		return;
	}

	// get all arguments separated by commas
	while(token!=NULL)
	{
		token=strtok(NULL, delim); 	// get next token
		if(token==NULL) break;		// exit immediately if token no good

#if _FEEDBACK_MSG_ == 1	// verify token
		serial_puts("Token: "); serial_puts(token); serial_puts("\r\n");
#endif

		// try to convert and append to payload
		success=append_token(payload, &payloadIndex, token);

#if _FEEDBACK_MSG_ == 1 // verify payload
		if(success) serial_puts("Data Good - ");
		else serial_puts("Data Error - ");
		sprintf(str, "Index = %u \r\n", payloadIndex);
		serial_puts(str);
#endif

		//break immediately on payload error
		if(!success) break;
	}

	// send the I2C command if good payload
	if(success && payloadIndex!=0)	sendI2C(i2caddress, payload, payloadIndex);
	else
	{
		if(errormessageon) serial_puts_p(strI2CCmdErr);
#if _FEEDBACK_MSG_ == 1
		serial_puts("Err 5\n\r");
#endif
	}
}

uint8_t append_token(uint8_t* payload, uint8_t* index, char* token)
{
	uint8_t result=0;
	unsigned int unum;
	int num;
	char ch;
	uint8_t i;
	switch(token[0])
	{
		case 'x':	// hex character
			result=sscanf(token+1, "%x", &unum); // skip the x and read the hex number
			if(result)
			{
				if(unum>255) return 0; // limited to 8 bit hex values
				payload[*index]=(uint8_t)unum;
				(*index)++;
				if (*index==0) return 0; // force error on max payload overrun
			}
			break;
		case '"':	// string
			i=1; 	// start after the "
			while(i<255)
			{
				ch=token[i];				// read all the characters in the token
				if(ch=='\0') break;			// end of string
				payload[*index]=ch;			// put in the payload
				(*index)++;					// advance payload index
				if (*index==0) return 0; 	// index wrapped around, exit with error
				i++;						// advance string index
			}
			result=1;
			break;
		case '\'':	// single character
			result=sscanf(token+1, "%c", &ch);
			if(result)
			{
				payload[*index]=ch;
				(*index)++;
				if (*index==0) return 0;
			}
			break;
		default:
			// I have problem here if I get a 16 bit int and it doesn't fit in an int8_t or uint8_t.
			// So I am reducing the allowed range to -128 / +255
			result=sscanf(token, "%d", &num);
			if(result)
			{
				if(num>255 || num<-128) return 0; 				// limited to 8 bit signed or unsigned arguments
				if(num<=127) payload[*index]=(int8_t)num;	// allow signed from -128 to 127
				else payload[*index]=(uint8_t)num;			// but allow unsigned numbers up to 255
				(*index)++;
				if (*index==0) return 0; // force error on max payload overrun
			}
			break;
	}
	return result;
 }

void sendI2C(uint8_t address, uint8_t* payload, uint8_t payload_length)
{
#if _FEEDBACK_MSG_ == 1 // ifdef it to save memory when not using
	serial_puts("### RESULT IS ####\r\n");
	char str[65];
	sprintf(str, "I2C address = %u \r\n", address);
	serial_puts(str);
	sprintf(str, "Payload length= %u \r\n", payload_length);
	serial_puts(str);
	serial_puts("Payload = \r\n");
	for(uint8_t i=0; i<payload_length; i++)
	{
		sprintf(str, "Byte %u = %u \r\n", i, payload[i]);
		serial_puts(str);
	}
	serial_puts("\r\n");
#endif
	// send the data via i2c
	i2c_send_data(address,payload, payload_length, TRUE);
}


const char strPanelCmdErr[] PROGMEM="**Invalid Panel Command\r\n";
void parse_panel_command(char* command_string, uint8_t length)
{
	/************************************
	 * Command vocabulary
	 * : as start command sign
	 * :SExx as play sequence
	 * 	argument: 00 01 ... 10 sequence number
	 * :OPxx as open panel:
	 *  argument 01...10 as panel number
	 *  00 = all panels
	 *  11 = top panels
	 *  12 = bottom panels
	 * :CLxx as close panel, remove RC, kill servo
	 *  argument 01...10 as panel number
	 *  00 = close all panels using a slow close sequence
	 * :RCxx as listen to RC
	 * 	argument 00 -> move all panels
	 *  argument 01 ... 10 -> move corresponding panels
	 * :STxx as stop (soft hold/buzz kill)
	 * 	Removes RC, and kill servo power
	 * 	00=all panels servo off
	 * :HDxx as hold (hard hold)
	 * 	Removes RC, hold the servo to last position
	 * 	00=all panels that had RC will hold
	 *
	 */

	char cmd[3];
	char arg[3];

	// a properly constructed command should have 5 chars
	if (length!=5)
	{
		if(errormessageon) serial_puts_p(strPanelCmdErr);
		return;
	}

	// character ':' begins command, just double check, should not happen
	if(command_string[0]!=PANEL_START_CHAR)
	{
		if(errormessageon) serial_puts_p(strPanelCmdErr);
		return;
	}

	cmd[0]=command_string[1];
	cmd[1]=command_string[2];
	cmd[2]='\0';
	arg[0]=command_string[3];
	arg[1]=command_string[4];
	arg[2]='\0';

	process_command(cmd, arg);
}

void process_command(char* thecommand, char* theargument)
{
	// hex conversion example
	// result=(int)strtol(str,(char **)NULL,16);
	// for now use base10 value conversion

	uint8_t value;
	value=atoi(theargument);

	if(strcmp(thecommand,CMD_SEQUENCE )==0)
	{
		serial_puts_p(strOK);
		sequence_command(value);
		return;
	};

	if(strcmp(thecommand,CMD_OPEN )==0)
	{
		serial_puts_p(strOK);
		open_command(value);
		return;
	};
	if(strcmp(thecommand,CMD_CLOSE )==0)
	{
		serial_puts_p(strOK);
		close_command(value);
		return;
	};
	if(strcmp(thecommand,CMD_RC )==0)
	{
		serial_puts_p(strOK);
		rc_command(value);
		return;
	};
	if(strcmp(thecommand,CMD_STOP )==0)
	{
		serial_puts_p(strOK);
		stop_command(value);
		return;
	};
	if(strcmp(thecommand,CMD_HOLD )==0)
	{
		serial_puts_p(strOK);
		hold_command(value);
		return;
	};

	if(errormessageon) serial_puts_p(strPanelCmdErr);

}


const char strSeqCloseAll[] PROGMEM="(Close all panels) \r\n";
const char strSeqScream[] PROGMEM="(Scream) \r\n";
const char strSeqWave[] PROGMEM="(Wave) \r\n";
const char strSeqFastWave[] PROGMEM="(Fast Wave) \r\n";
const char strSeqOpenCloseWave[] PROGMEM="(Open Close Wave) \r\n";
const char strSeqCantinaMarchingAnts[] PROGMEM="(Cantina Marching Ants) \r\n";
const char strSeqShortCircuit[] PROGMEM="(Short Circuit) \r\n";
const char strSeqCantinaDance[] PROGMEM="(Cantina Dance) \r\n";
const char strSeqLeia[] PROGMEM="(Leia Message) \r\n";
const char strSeqDisco[] PROGMEM="(Disco Dance) \r\n";
const char strSeqQuiet[] PROGMEM="(Set to Quiet) \r\n";
const char strSeqWideAwake[] PROGMEM="(Set to Wide Awake) \r\n";
const char strSeqTopRC[] PROGMEM="(All pie panels to RC) \r\n";
const char strSeqAwake[] PROGMEM="(Set to Awake) \r\n";
const char strSeqExcited[] PROGMEM="(Set to Excited) \r\n";
const char strSeqScreamNoPanels[] PROGMEM="(Scream No Panels) \r\n";
const char strSeqRythmicPanels[] PROGMEM="(Rythmic Panels) \r\n";
const char strSeqMarchingAnts[] PROGMEM="(Marching Ants Panels) \r\n";
//Eebel START
const char strSeqMaxstangWiggle[] PROGMEM="(Maxstang Wiggle Panels) \r\n";
const char strSeqPanelWaveBye[] PROGMEM="(Panel Wave Bye) \r\n";
const char strSeqPanelStarWarsDisco[] PROGMEM="(Star Wars Disco) \r\n";
const char strSeqPanelStarTrekDisco[] PROGMEM="(Star Trek Disco) \r\n";
//Eebel END


void sequence_command(uint8_t value)
{
	char string[35];
	switch(value)
	{
		case 0: // CLOSE ALL PANELS
			seq_stopsequence(); 				// abort any previous sequence immediately
			seq_loadspeed(panel_slow_speed);	// slow speed for soft close
			seq_loadsequence(panel_init, SEQ_SIZE(panel_init));
			seq_startsequence();				// start panel sequence
			if(feedbackmessageon) serial_puts_p(strSeqCloseAll);		// debug console feedback
			break;

		case 1: // SCREAM
			seq_loadsequence(panel_all_open, SEQ_SIZE(panel_all_open));
			seq_loadspeed(panel_slow_speed);	// slow open
			SoundScream();						// scream sound
			DisplayScream(); 					// scream display
			MagicFlicker(4); 					// magic panel on for 4 seconds
			HPFlicker(4);						// HPs flicker for 4 seconds
			seq_startsequence();				// start panel sequence
			if(feedbackmessageon) serial_puts_p(strSeqScream);		// debug console feedback
			break;

		case 2: // WAVE
			seq_loadsequence(panel_wave, SEQ_SIZE(panel_wave));
			seq_resetspeed();
			HPFlash(4);							// flash holos for 4 seconds
			SoundWave(); 						// happy sound
			seq_startsequence();				// start sequence
			if(feedbackmessageon) serial_puts_p(strSeqWave);			// debug console feedback
			break;

		case 3: // MOODY FAST WAVE
			seq_loadsequence(panel_fast_wave, SEQ_SIZE(panel_fast_wave));
			seq_resetspeed();
			DisplayFlash4();  					// 4 seconds flash display
			HPFlicker(4);						// HPs flicker for 4 seconds
			SoundFastWave(); 					// moody sound
			seq_startsequence();				// start panel sequence
			if(feedbackmessageon) serial_puts_p(strSeqFastWave);		// debug console feedback
			break;

		case 4: // OPEN WAVE
			seq_loadsequence(panel_open_close_wave, SEQ_SIZE(panel_open_close_wave));
			seq_resetspeed();
			HPFlash(5); 	 					// HPs flash for 5 seconds
			SoundOpenWave(); 					// long happy sound
			seq_startsequence();				// start panel sequence
			if(feedbackmessageon) serial_puts_p(strSeqOpenCloseWave);	// debug console feedback
			break;

		case 5: // Beep Cantina (R2 beeping the cantina, panels doing marching ants)
			seq_add_completion_callback(resetJEDIcallback); 	// callback to reset displays at end of sequence
			seq_loadsequence(panel_marching_ants, SEQ_SIZE(panel_marching_ants));
			seq_loadspeed(panel_slow_speed);					// slow speed marching ants
			DisplaySpectrum();	 								// spectrum display
			HPFlash(17); 	 									// HPs flash for 17 seconds
			SoundBeepCantina(); 								// beeping cantina sound
			seq_startsequence();								// start panel sequence
			if(feedbackmessageon) serial_puts_p(strSeqCantinaMarchingAnts);			// debug console feedback
			break;

		case 6: // SHORT CIRCUIT / FAINT
			seq_loadsequence(panel_all_open_long, SEQ_SIZE(panel_all_open_long));
			seq_loadspeed(panel_super_slow_speed);	// very slow speed open
			DisplayShortCircuit();  				// short circuit display
			SoundFaint(); 							// Faint sound
			MagicFlicker(10);  						// Magic Panel Flicker for 10 seconds
			HPFlicker(10);  						// HPs flicker 10 seconds
			seq_startsequence();					// start panel sequence
			if(feedbackmessageon) serial_puts_p(strSeqShortCircuit);		// debug console feedback
			break;

		case 7: // Cantina (Orchestral Cantina, Rhythmic Panels)
			seq_add_completion_callback(resetJEDIcallback); 	// callback to reset displays at end of sequence
			seq_loadsequence(panel_dance, SEQ_SIZE(panel_dance));
			seq_resetspeed();
			SoundCantina();		 				// code for dance sound
			DisplaySpectrum();	 				// spectrum display
			HPFlicker(46); 						// HPs flicker for 46 sec
			seq_startsequence();				// start panel sequence
			if(feedbackmessageon) serial_puts_p(strSeqCantinaDance);	// debug console feedback
			break;

		case 8: // LEIA
			seq_stopsequence(); 				// Abort previous sequence
			seq_loadspeed(panel_slow_speed);	// Go slow
			seq_loadsequence(panel_init, SEQ_SIZE(panel_init));	// Close panels
			seq_startsequence();

			HP1RC();			 				// HP 01 in RC mode
			SoundLeia();						// Leia message sound
			HP1Flicker(34); 					// front holos flicker for 34 sec
			DisplayLeia();		 				// Leia display
			if(feedbackmessageon) serial_puts_p(strSeqLeia);			// debug console feedback
			break;

		case 9:	// DISCO
			seq_add_completion_callback(resetJEDIcallback); // callback to reset displays at end of sequence
			seq_resetspeed();
			seq_loadsequence(panel_long_disco, SEQ_SIZE(panel_long_disco)); // 6:26 seconds sequence
			// message on the logics
			//suart_puts("@1MR2 D2   \r"); 		// message is top front is R2
			//_delay_ms(200);
			//suart_puts("@2M  D2  \r");		// message is lower front is D2
			//_delay_ms(200);
			RLDSetMessage("STAR WARS   "); 		// message in rear is STAR WARS...
			// suart_puts("@3P61\r");			// ... in Aurabesh!
			//_delay_ms(100);
			DisplaySpectrum();	 				// all logics in disco spectrum mode
			RLDDisplayMessage();				// put rear logic in text mode
			SoundDisco();						// disco music
			HPFlicker(99);		 				// all holos flciker for as long as possible
			seq_startsequence();				// start panel sequence
			if(feedbackmessageon) serial_puts_p(strSeqDisco);			// debug console feedback
			break;

		case 10: // QUIET   sounds off, holo stop, panel closed
			seq_stopsequence(); 				// abort any previous sequence immediately
			seq_loadspeed(panel_slow_speed);	// go slow
			seq_loadsequence(panel_init, SEQ_SIZE(panel_init));
			seq_startsequence();				// close panels

			init_jedi();						// JEDI back to default
			HPStop(); 							// all holos to stop
			SoundStop();						// stop sounds
			seq_resetspeed();					// sequence speed to fast
			stop_command(0);					// all panels off RC
			if(feedbackmessageon) serial_puts_p(strSeqQuiet);			// debug console feedback
			break;

		case 11: // WIDE AWAKE	random sounds, holos on random, panels closed

			seq_stopsequence(); 				// abort any previous sequence immediately
			seq_loadspeed(panel_slow_speed);	// go slow
			seq_loadsequence(panel_init, SEQ_SIZE(panel_init));
			seq_startsequence();				// close panels

			init_jedi();						// JEDI back to default
			HPRandom();			 				// all HPs to random
			SoundRandom();						// random sounds mode
			seq_resetspeed();					// sequence speed to fast
			stop_command(0);					// all panels off RC and closed
			if(feedbackmessageon) serial_puts_p(strSeqWideAwake);		// debug console feedback
			break;

		case 12: // TOP PIE PANELS RC
			rc_command(7);
			rc_command(8);
			rc_command(9);
			rc_command(10);
			if(feedbackmessageon) serial_puts_p(strSeqTopRC);
			break;

		case 13: // AWAKE	random sounds, holos off, panels closed

			seq_stopsequence(); 				// abort any previous sequence immediately
			seq_loadspeed(panel_slow_speed);	// go slow
			seq_loadsequence(panel_init, SEQ_SIZE(panel_init));
			seq_startsequence();				// close panels

			init_jedi();						// JEDI back to default
			HPStop(); 							// all HPs to stop
			SoundRandom();						// random sounds mode
			seq_resetspeed();					// sequence speed to fast
			stop_command(0);					// all panels off RC and closed
			if(feedbackmessageon) serial_puts_p(strSeqAwake);			// debug console feedback
			break;
		case 14: // EXCITED	random sounds, holos movement, holo lights on, panels closed
			seq_stopsequence(); 				// abort any previous sequence immediately
			seq_loadspeed(panel_slow_speed);	// go slow
			seq_loadsequence(panel_init, SEQ_SIZE(panel_init));
			seq_startsequence();				// close panels

			init_jedi();						// JEDI back to default
			HPRandom();			 				// all HPs to random
			HPOn(); 							// all HPs lights on
			SoundRandom();						// random sounds mode
			seq_resetspeed();					// sequence speed to fast
			stop_command(0);					// all panels off RC and closed
			if(feedbackmessageon) serial_puts_p(strSeqExcited);		// debug console feedback
			break;

		case 15: // SCREAM no panels: sound + lights but no panels
			SoundScream();		 				// code for scream sound
			DisplayScream(); 					// scream display
			HPFlicker(3);						// holos flicker for 4 seconds
			MagicFlicker(3); 					// magic panel on for 4 seconds
			if(feedbackmessageon) serial_puts_p(strSeqScreamNoPanels); // debug console feedback
			break;

		case 16: // Maxstang Wiggle and SCREAM
			seq_loadsequence(panel_maxstang_wiggle, SEQ_SIZE(panel_maxstang_wiggle));
			seq_loadspeed(panel_medium_speed);	// fast open
			SoundScream();						// scream sound
			DisplayScream(); 					// scream display
			MagicFlicker(4); 					// magic panel on for 4 seconds
			HPFlicker(4);						// HPs flicker for 4 seconds
			seq_startsequence();				// start panel sequence
			if(feedbackmessageon) serial_puts_p(strSeqMaxstangWiggle);		// debug console feedback
			break;

		case 17: // Maxstang WaveBye and SoundWaveBye
			seq_loadsequence(panel_wave_bye, SEQ_SIZE(panel_wave_bye));
			seq_loadspeed(panel_medium_speed);	// fast open
			SoundWaveBye();						// Bye sound
			//DisplayScream(); 					// scream display
			MagicFlicker(2); 					// magic panel on for 4 seconds
			HPFlicker(2);						// HPs flicker for 4 seconds
			seq_startsequence();				// start panel sequence
			if(feedbackmessageon) serial_puts_p(strSeqPanelWaveBye);		// debug console feedback
			break;

		case 18:	// Star Wars DISCO
			seq_add_completion_callback(resetJEDIcallback); // callback to reset displays at end of sequence
			seq_resetspeed();
			seq_loadsequence(panel_long_disco, SEQ_SIZE(panel_long_disco)); // 6:26 seconds sequence
			// message on the logics
			//suart_puts("@1MR2 D2   \r"); 		// message is top front is R2
			//_delay_ms(200);
			//suart_puts("@2M  D2  \r");		// message is lower front is D2
			//_delay_ms(200);
			RLDSetMessage("STAR WARS   "); 		// message in rear is STAR WARS...
			// suart_puts("@3P61\r");			// ... in Aurabesh!
			//_delay_ms(100);
			DisplaySpectrum();	 				// all logics in disco spectrum mode
			RLDDisplayMessage();				// put rear logic in text mode
			SoundStarWarsDisco();						// disco music
			HPFlicker(99);		 				// all holos flciker for as long as possible
			seq_startsequence();				// start panel sequence
			if(feedbackmessageon) serial_puts_p(strSeqPanelStarWarsDisco);			// debug console feedback
			break;

		case 19:	// Star Trek DISCO
			seq_add_completion_callback(resetJEDIcallback); // callback to reset displays at end of sequence
			seq_resetspeed();
			seq_loadsequence(panel_long_disco, SEQ_SIZE(panel_long_disco)); // 6:26 seconds sequence
			// message on the logics
			//suart_puts("@1MR2 D2   \r"); 		// message is top front is R2
			//_delay_ms(200);
			//suart_puts("@2M  D2  \r");		// message is lower front is D2
			//_delay_ms(200);
			RLDSetMessage("STAR TREK   "); 		// message in rear is STAR WARS...
			// suart_puts("@3P61\r");			// ... in Aurabesh!
			//_delay_ms(100);
			DisplaySpectrum();	 				// all logics in disco spectrum mode
			RLDDisplayMessage();				// put rear logic in text mode
			SoundStarTrekDisco();						// disco music
			HPFlicker(99);		 				// all holos flciker for as long as possible
			seq_startsequence();				// start panel sequence
			if(feedbackmessageon) serial_puts_p(strSeqPanelStarTrekDisco);			// debug console feedback
			break;


		///////////////////////////////////////////
		//	sequences of panels only, no sounds or light effects
		//
		//	:SE51 Scream, with all panels open
		//	:SE52 Wave, one panel at a time
		//	:SE53 Fast (Smirk) back and forth wave
		//	:SE54 Wave 2 (open progressively all panels, then close one by one)
		//	:SE55 Marching ants
		//	:SE56 Faint/Short Circuit
		//	:SE57 Rythmic panel dance
		//////////////////////////////////////////

		case 51: // SCREAM
			seq_loadsequence(panel_all_open, SEQ_SIZE(panel_all_open));
			seq_loadspeed(panel_slow_speed);	// softer close
			seq_startsequence();
			if(feedbackmessageon) serial_puts_p(strSeqScream);
			break;
		case 52: // WAVE1
			seq_loadsequence(panel_wave, SEQ_SIZE(panel_wave));
			seq_resetspeed();
			seq_startsequence();
			if(feedbackmessageon) serial_puts_p(strSeqWave);
			break;
		case 53: // MOODY FAST WAVE
			seq_loadsequence(panel_fast_wave, SEQ_SIZE(panel_fast_wave));
			seq_resetspeed();
			seq_startsequence();
			if(feedbackmessageon) serial_puts_p(strSeqFastWave);
			break;
		case 54: // WAVE2
			seq_loadsequence(panel_open_close_wave, SEQ_SIZE(panel_open_close_wave));
			seq_resetspeed();
			seq_startsequence();
			if(feedbackmessageon) serial_puts_p(strSeqOpenCloseWave);
			break;
		case 55: // Marching ant
			seq_loadsequence(panel_marching_ants, SEQ_SIZE(panel_marching_ants));
			seq_loadspeed(panel_slow_speed);	// softer close
			seq_startsequence();
			if(feedbackmessageon) serial_puts_p(strSeqMarchingAnts);
			break;
		case 56: // SHORT CIRCUIT / FAINT
			seq_loadsequence(panel_all_open_long, SEQ_SIZE(panel_all_open_long));
			seq_loadspeed(panel_super_slow_speed);	// very slow close
			seq_startsequence();
			if(feedbackmessageon) serial_puts_p(strSeqShortCircuit);
			break;
		case 57: // Rhythmic Panels
			seq_loadsequence(panel_dance, SEQ_SIZE(panel_dance));
			seq_resetspeed();
			if(feedbackmessageon) serial_puts_p(strSeqRythmicPanels);
			seq_startsequence();
			break;

		default:
			sprintf(string, "(Sequence %02d not implemented) \r\n", value);
			seq_resetspeed();
			if(errormessageon) serial_puts(string);
			break;
	}
}




void open_command(uint8_t value)
{
	uint8_t i;
	if(value==0) // open all
	{
		for (i=1; i<=SERVO_NUM; i++)
		{
			servo_set(i, _OPN);
		}
		return;
	}
	if(value<=SERVO_NUM) // open specific panel
	{
		servo_set(value, _OPN);
		return;
	}
	if(value==11) // open top panels
	{
		for (i=7; i<=SERVO_NUM; i++)
		{
			servo_set(i, _OPN);
		}
		return;
	}
	if(value==12) // open bottom panels
	{
		for (i=1; i<=6; i++)
		{
			servo_set(i, _OPN);
		}
		return;
	}
}

void close_command(uint8_t value)
{
	if(value==0)
	{
		// all panels off RC
		for(int i=1; i<=SERVO_NUM; i++)
		{
			panel_rc_control[i-1]=0;
		}

		//sequence to close all panels, turn them off slowly
		seq_stopsequence(); // abort any previous sequence immediately
		seq_loadspeed(panel_slow_speed);
		seq_loadsequence(panel_init, SEQ_SIZE(panel_init));
		seq_startsequence();
		return;
	}
	if(value<=SERVO_NUM)
	{
		panel_rc_control[value-1]=0;	// turn off RC control which would re-open the panel
		servo_set(value, _CLS);			// close the servo

		// Give time for the panel to close, then shut it off for buzz control
		killbuzz_timer=COUNT_PER_SECOND/3; // set a 1/3s timer
		panel_to_silence[value-1]=1;	// flag the panel to silence, will be caught in main loop
		return;							// return immediately without blocking
	}
}

void rc_command(uint8_t value)
{
	uint8_t i;

	if(value>SERVO_NUM) return;

	if(value==0) // all on
	{
		for(i=0; i<SERVO_NUM; i++)
		{
			panel_rc_control[i]=1;
		}
		return;
	}

	// add the panel to RC controlled list
	panel_rc_control[value-1]=1;
}

void stop_command(uint8_t value)
{
	// panel hold with buzz kill: remove from RC and stop servos

	uint8_t i;
	if(value>SERVO_NUM) return;

	// all panels hold to last position and servo off
	if(value==0)
	{
		for(i=1; i<=SERVO_NUM; i++)
		 {
			 panel_rc_control[i-1]=0;
			 servo_set(i,SERVO_NO_PULSE);
		 }
		return;
	}

	// remove just one panel to RC controlled list and turn it off
	panel_rc_control[value-1]=0;
	servo_set(value,SERVO_NO_PULSE);
}


void hold_command(uint8_t value)
{
	// hard hold to last position, leave servo on.
	uint8_t i;
	if(value>SERVO_NUM) return;

	// all servos off RC control
	if(value==0) // all off
	{
		for(i=1; i<=SERVO_NUM; i++)
		 {
			 panel_rc_control[i-1]=0;
		 }
		return;
	}

	// remove the panel to RC controlled list
	panel_rc_control[value-1]=0;
}

// sets JEDI display and Holos in their default state
void init_jedi()
{
	seq_remove_completion_callback(); // remove any competing completion callback
	suart_puts("*H000\r");	// quick way to turn off holos if connected to MarcDuino
	_delay_ms(100);
	suart_puts("@0T1\r");	// abort test routine, reset all to normal
	_delay_ms(20);
#ifdef _DIGITALJEDI_
	/**** initialize JEDI display for digital output on HPs and PSI ******/
	// I connected Mike Velchecks rear PSI to the JEDI, which requires output to be turned to digital
	// My holo lights are the older version and also require HPs to be set to digital
	suart_puts("@6P91\r");	// change front holo (6) parameter 9 (P9) to digital (1)
	_delay_ms(20);
	suart_puts("@5P91\r");   // change rear PSI (5) parameter 9 (P9) to digital (1)
	_delay_ms(20);
#endif
}

// callback to reset JEDI to normal after a sequence, works only once
void resetJEDIcallback()
{
	suart_puts("*H000\r");	// quick way to turn off holos if connected to MarcDuino
	_delay_ms(100);
	suart_puts("@0T1\r");	// abort test routine, reset all to normal
	_delay_ms(20);
	seq_remove_completion_callback();	// one shot, remove yourself
}


//////////////////////////////////////////////////
// HP & Magic Panel Actions Commands
/////////////////////////////////////////////////

void HPOff()
{
	suart_puts("*H000\r");
}

void HPOn()
{
	suart_puts("*ON00\r"); 	// holo lights on
}

void HPStop()
{
	suart_puts("*ST00\r"); 	// all holos to stop and lights off
}

void HPRandom()
{
	suart_puts("*RD00\r"); 	// all holos to random
}

void HPFlicker(uint8_t seconds)	// all HP flicer seconds from 0 (off) to 99
{
	char string[7];
	sprintf(string, "*F0%02d\r", seconds);
	suart_puts(string);
}

void HP1Flicker(uint8_t seconds) // front HP flicker
{
	char string[7];
	sprintf(string, "*F1%02d\r", seconds);
	suart_puts(string);
}

void HPFlash(uint8_t seconds)	// seconds from 0 (off) to 99 (always on)
{
	char string[7];
	sprintf(string, "*H0%02d\r", seconds);
	suart_puts(string);
}

void HP1RC()
{
	suart_puts("*RC01\r"); 	// HP 01 (front) in RC mode
}

void MagicFlash(uint8_t seconds)	// seconds from 0 (off) to 99 (always on)
{
	char string[7];
	sprintf(string, "*MO%02d\r", seconds);
	suart_puts(string);
}

void MagicFlicker(uint8_t seconds)	// seconds from 0 (off) to 99 (always on)
{
	char string[7];
	sprintf(string, "*MF%02d\r", seconds);
	suart_puts(string);
	_delay_ms(50);
}

//////////////////////////////////////////////////
// JEDI Actions Commands
/////////////////////////////////////////////////

void DisplayScream()
{
	suart_puts("@0T5\r"); 	// scream display
	_delay_ms(100);
}

void DisplayNormal()
{
	suart_puts("@0T1\r");
}

void DisplayFlash4()
{
	suart_puts("@0T2\r");  	// flash display
	_delay_ms(100);
	suart_puts("@0W4\r");  	// for 4 seconds
	_delay_ms(50);
}

void DisplaySpectrum()
{
	suart_puts("@0T92\r"); 	// spectrum display
	_delay_ms(200);			// JEDI needs a large amount of time to setup, 100 ms not enough
}

void DisplayShortCircuit()
{
	suart_puts("@0T4\r");	// short circuit display
	_delay_ms(100);
	suart_puts("@0W10\r");  // for 10 seconds (this one does not seem to respond)
	_delay_ms(20);
}

void DisplayLeia()
{
	suart_puts("@0T6\r"); 	// Leia display
	_delay_ms(100);
}

void RLDSetMessage(char* message)
{
	suart_puts("@3M");
	suart_puts(message);
	suart_putc('\r');
	_delay_ms(250);
}

void RLDDisplayMessage()
{
	suart_puts("@3T100\r");	// put rear logic in text mode
	_delay_ms(100);
}


//////////////////////////////////////////////////
// Sound Actions Commands
/////////////////////////////////////////////////

//EebelSound
void SoundWaveBye()
{
	parse_sound_command("$205", 2);	// chat sound bank 2 #05, duration 2 sec
}
void SoundStarWarsDisco()
{
	parse_sound_command("$807", 2);	// chat sound bank 8 #07, File 182
}
void SoundStarTrekDisco()
{
	parse_sound_command("$808", 2);	// chat sound bank 8 #08, File 183
}

//End Eebel Sound
void SoundScream()
{
	//suart2_puts("$S\r"); 	// code for scream sound
	parse_sound_command("$S", 2);	// send through parser so it can get to the MP3 interpreter
}

void SoundWave()
{
	parse_sound_command("$213",4); 	// chat sound bank 2 #13
}

void SoundDisco()
{
	parse_sound_command("$D",2);	// disco music
}

void SoundFastWave()
{
	parse_sound_command("$34",3); 	// long happy sound bank 3 #4
}

void SoundOpenWave()
{
	parse_sound_command("$36",3); 	// long happy sound bank 3 #6
}

void SoundBeepCantina()
{
	parse_sound_command("$c",2); 	// beeping cantina sound
}

void SoundFaint()
{
	parse_sound_command("$F",2); 	// Faint sound
}

void SoundCantina()
{
	parse_sound_command("$C",2); 	// Actual cantina song
}

void SoundLeia()
{
	parse_sound_command("$L",2); 	// Leia message sound
}

void Sound(uint8_t bank, uint8_t number)
{
	char string[7];
	sprintf(string, "$%1d%2d", bank, number);
	parse_sound_command(string, strlen(string));
}

void SoundRandom()
{
	parse_sound_command("$R",2);		// random sounds on
}

void SoundStop()
{
	parse_sound_command("$s",2);	// stop sounds
}

