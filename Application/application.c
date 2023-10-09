/******************************************************************************
 *
 * Module: The Application
 *
 * File Name: Application.c
 *
 * Description: Header file for the Two Common Cathod Multiplexed Seven Segement driver
 * with no decoder IC
 *
 * Author: Adham Nour
 *
 *******************************************************************************/
#include <util/delay.h>
#include <stdlib.h>
#include "string.h"

#include "application.h"
#include "../HAL/Keypad/Keypad.h"
#include "../HAL/LCD/LCD.h"
#include "../MCAL/GPIO/gpio.h"
/*
 * Description:
 * this function is reponsable to inizialize the hardware
 */

static uint8 keypad_input = 255, i = 0;
static uint8 buffer[16] = { 0 };
static void performCalc();
void substr(uint8 *x, uint8 *y, uint8 start, uint8 end);

void APPLICATION_setup() {
	KEYPAD_init();
	LCD_init();
	LCD_displayString("Adham Nour ElWfa");
	_delay_ms(500);
	LCD_displayStringRowColumn(1, 0, "simpleCalculator");
	_delay_ms(500);

	LCD_clearScreen();
	LCD_displayString("Enter Your");
	LCD_displayStringRowColumn(1, 0, "Calculation Now");
	_delay_ms(500);
	LCD_clearScreen();

}

/*
 * Description:
 * this is the main loop of the application
 */

void APPLICATION_loop() {
	while (keypad_input == 255) {
		keypad_input = KEYPAD_getPressedKey();
	}

	if (keypad_input == '=') {
		performCalc();
	} else if (keypad_input == 13) {
		LCD_clearScreen();
		i = 0;
		for (int j = 0; j < 16; j++)
			buffer[j] = 0;
	} else {
		if (i < 16) {
			buffer[i] = keypad_input;
			i++;
			LCD_displayStringRowColumn(0, 0, buffer);

		} else {
			for (int j = 0; j < 16; j++)
				buffer[j] = 0;
			LCD_displayStringRowColumn(1, 0, "Long Exp, buff clrd");
		}
	}
	_delay_ms(200);
	keypad_input = 255;

}
static void performCalc() {
	uint8 operatorLocations[16];
	sint16 operands[17];
	for (int i = 0; i < 16; i++)
		operands[i] = -1;
	for (int i = 0; i < 16; i++)
			operatorLocations[i] = 255;
	for (int i = 0, j = 0; i < 16; i++) {
		if (buffer[i] == '+' || buffer[i] == '-' || buffer[i] == '*'
				|| buffer[i] == '%') {
			operatorLocations[j] = i;
			j++;
		}

	}
	if (operatorLocations[0] == 0) {
		LCD_displayStringRowColumn(1, 0, "Op in indx=0");
		return;
	}
	/*Parsing*/
	uint8 temp[16] = { '\0' };
	substr(buffer, temp, 0, operatorLocations[0]);
	operands[0] = atoi(temp);
	for (int i = 1, j = 1; i < 16; i++) {
		if (operatorLocations[i] == 255) {
			substr(buffer, temp, operatorLocations[i - 1] + 1, 16);
			operands[j] = atoi(temp);
			j++;
			break;
		} else {
			substr(buffer, temp, operatorLocations[i - 1] + 1,
					operatorLocations[i]);
			operands[j] = atoi(temp);
			j++;

		}
	}
	for (int i=0;i<17;i++) {
		if(operands[i]==-1)break;
		itoa(operands[i],temp,10);
		LCD_displayStringRowColumn(1, 0, temp);
		_delay_ms(500);

	}

}

void substr(uint8 *x, uint8 *y, uint8 start, uint8 end) {
	for (int i = 0; i < 16; i++)
		y[i] = '\0';
	for (int i = start, j = 0; i < end && j < 16; i++, j++) {
		y[j] = x[i];
	}
}

