/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author: Adham Nour
 *
 *******************************************************************************/

#include "Keypad.h"
#include "../../MCAL/GPIO/gpio.h"
#include <util/delay_basic.h>

#include <util/delay.h>
/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLS == 3)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x3 keypad
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);
#elif (KEYPAD_NUM_COLS == 4)
/*
 * Function responsible for mapping the switch number in the keypad to
 * its corresponding functional number in the proteus for 4x4 keypad
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);
#endif

#endif /* STANDARD_KEYPAD */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Initializing the Keypad
 */
void KEYPAD_init() {
	uint8 i;
	for (i = 0; i < KEYPAD_NUM_ROWS; ++i) {
		GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + i,
				PIN_OUTPUT);
		GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + i,
				LOGIC_HIGH);
	}
	for (i = 0; i < KEYPAD_NUM_COLS; ++i) {
		GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+i,
				PIN_INPUT);
	}

}
uint8 KEYPAD_getPressedKey(void) {
	uint8 i,j;
	for (i = 0; i < KEYPAD_NUM_ROWS; ++i) {

		GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + i,
						LOGIC_LOW);

		for(j=0;j<KEYPAD_NUM_COLS;++j){
			if(!GPIO_readPin(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+j)){
				GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + i,
										LOGIC_HIGH);
				return KEYPAD_4x4_adjustKeyNumber((j+KEYPAD_NUM_COLS*i+1));
			}
		}

		GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + i,
						LOGIC_HIGH);
	}
	return 255;
}

#ifndef STANDARD_KEYPAD

#if (KEYPAD_NUM_COLS == 3)
/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x3 shape
 */
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
		case 10: keypad_button = '*'; // ASCII Code of *
				 break;
		case 11: keypad_button = 0;
				 break;
		case 12: keypad_button = '#'; // ASCII Code of #
				 break;
		default: keypad_button = button_number;
				break;
	}
	return keypad_button;
}

#elif (KEYPAD_NUM_COLS == 4)

/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number) {
	uint8 keypad_button = 0;
	switch (button_number) {
	case 1:
		keypad_button = '7';
		break;
	case 2:
		keypad_button = '8';
		break;
	case 3:
		keypad_button = '9';
		break;
	case 4:
		keypad_button = '%'; // ASCII Code of %
		break;
	case 5:
		keypad_button = '4';
		break;
	case 6:
		keypad_button = '5';
		break;
	case 7:
		keypad_button = '6';
		break;
	case 8:
		keypad_button = '*'; /* ASCII Code of '*' */
		break;
	case 9:
		keypad_button = '1';
		break;
	case 10:
		keypad_button = '2';
		break;
	case 11:
		keypad_button = '3';
		break;
	case 12:
		keypad_button = '-'; /* ASCII Code of '-' */
		break;
	case 13:
		keypad_button = 13; /* ASCII of Enter */
		break;
	case 14:
		keypad_button = '0';
		break;
	case 15:
		keypad_button = '='; /* ASCII Code of '=' */
		break;
	case 16:
		keypad_button = '+'; /* ASCII Code of '+' */
		break;
	default:
		keypad_button = 255;
		break;
	}
	return keypad_button;
}

#endif

#endif /* STANDARD_KEYPAD */
