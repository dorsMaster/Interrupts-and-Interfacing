/*
 * Keypad.cpp
 *
 *  Created on: Oct 14, 2016
 *      Author: nem
 *   Some of this code was originally written by Justin Smalley 2008
 */


#include <predef.h>
#include <stdio.h>
#include <ctype.h>
#include <basictypes.h>
#include <constants.h>
#include <pin_irq.h>
#include <pins.h>
#include <system.h>
#include <utils.h>
#include <startnet.h>
#include <sim5441x.h>
#include "Keypad.h"


/* Name:Keypad Constructor
* Description: Constructor for the Keypad class. Not much to do beyond
* initializing the only class ivar
* Inputs: none
* Outputs: none
*/
Keypad::Keypad(void)
{
last_encoded_data = 0;
}

/* Name:Init
* Description: Initializes all the GPIO pins that interface to the keypad.
* Inputs: mode KEYPAD_POLL_MODE or KEYPAD_INT_MODE
* Outputs: none
*/
void Keypad::Init(BYTE mode)
{
	byte_mode = mode;
// Set the DA, DB, DC, DD , and DAvail pins to be general purpose IO pins
	KEYPAD_DO_A.function(PINJ2_33_GPIO);	// Keypad Data out A
	KEYPAD_DO_A.hiz();	//Set KEYPAD Data A pin to input on J2 header

	KEYPAD_DO_B.function(PINJ2_34_GPIO);	// Keypad Data Out B
	KEYPAD_DO_B.hiz();	//Set KEYPAD Data B pin to input on J2 header

	KEYPAD_DO_C.function(PINJ2_36_GPIO);	// Keypad Data Out C
	KEYPAD_DO_C.hiz();	//Set KEYPAD Data out C pin to input

	// D_AVAIL and DO_D share the same pin
	if (mode == KEYPAD_POLL_MODE) {
		KEYPAD_D_AVAIL.function(PINJ2_45_GPIO);
		KEYPAD_D_AVAIL.hiz();	// Set KEYPAD Data Available
	} else if (mode == KEYPAD_INT_MODE) { // KEYPAD_INT_MODE

		// Insert interrupt init here for exercise 3

	}

	KEYPAD_MUX_CTRL.function(PINJ2_35_GPIO);
	KEYPAD_MUX_CTRL.drive();
	KEYPAD_MUX_CTRL.set();
}

/* Name:read_data
* Description: Reads the data on all the 4 Data Out lines from the 922
* encoder and stores it in last_encoded_data
* Inputs: none
* Outputs: none
*/
void Keypad::read_data(void)
{

	if(byte_mode == KEYPAD_INT_MODE){

		// Insert exercise 3 code here
	}

	// Change function of KEYPAD_DO_D/KEYPAD_D_AVAIL to GPIO
	KEYPAD_DO_D.function(PINJ2_45_GPIO);
	KEYPAD_DO_D.hiz();
	KEYPAD_MUX_CTRL.clr(); // all data from encoder are on A side


	last_encoded_data = 0;
	if (KEYPAD_DO_A) last_encoded_data += 0x01;
	if (KEYPAD_DO_B) last_encoded_data += 0x02;
	if (KEYPAD_DO_C) last_encoded_data += 0x04;
	if (KEYPAD_DO_D) last_encoded_data += 0x08;


	if(byte_mode == KEYPAD_INT_MODE) {

		// Insert exercise 3 code here

	}

}

/* Name:GetNewButtonNumber
* Description: reads the data out lines of the encoder and returns that
* newly read value
* Inputs: none
* Outputs: unsigned char from 0-15
*/
unsigned char Keypad::GetNewButtonNumber(void)
{

read_data();
return last_encoded_data;
}


/* Name:GetLastButtonNumber
* Description: Returns the previously read value on the Data out lines from
* the encoder
* Inputs:
* Outputs:
*/
unsigned char Keypad::GetLastButtonNumber(void)
{
return last_encoded_data;
}

/* Name:GetNewButtonString
* Description: Returns a pointer to a string that corresponds to the newly
* read value on the Data Out lines. Calling this method will read the new
* value on Data out lines on the encoder.
* Inputs: none
* Outputs: returns a pointer to a string in the string array that maps
* strings from the button number.
*/
const char * Keypad::GetNewButtonString(void)
{
read_data();
return(KeypadButtonMapText[last_encoded_data]);
}

/* Name: GetLastButtonString
* Description: Returns a pointer to a string that corresponds to the last
* value read on the Data Out lines. Calling this method will not read a new
* value on the Data Out lines on the encoder.
* Inputs: none
* Outputs: returns a pointer to a string in the string array that maps
* strings from the button number.
*/
const char * Keypad::GetLastButtonString(void)
{
return(KeypadButtonMapText[last_encoded_data]);
}

/* Name: ButtonPressed
* Description: The method reads the current value of the data available line
* on the encoder.
* Inputs: none
* Outputs: It returns TRUE is the Data available lines is high and FALSE
* if low. The data available line is high is any button is being pressed and
* low if no button is being pressed.
*/
unsigned char Keypad::ButtonPressed(void)
{
		KEYPAD_MUX_CTRL.set();
		if (KEYPAD_D_AVAIL == HIGH) {
			return TRUE;
		} else {
			return FALSE;
		}
}

/* Name: EdgePortISR1
* Description: Interrupt Service Routine (ISR) that handles key presses
* Inputs: none
* Outputs:
*/
void Keypad::EdgePortISR1(void) {
	// Insert your ISR code here for exercise 3

}




