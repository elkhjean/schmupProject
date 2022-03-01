#include <stdint.h>
#include <pic32mx.h>
#include "game.h"			/* Declaration of functions, arrays etc for this game */

volatile int* triseptr = (volatile int*) 0xbf886100;
volatile int* porteptr = (volatile int*) 0xbf886110;

void ioInit(){
	/*Initialization of leds and buttons*/
	*triseptr &= ~0xFF; 	//Setting LSB of TRISE register to all zeroes for output on those pins
	*porteptr = 0;				//Initializing value of PORTE to 0
	TRISDSET = 0xFE0;			//Setting TRISD bits 5 to 11 to all ones for input on those bits
	return;
}

int getsw(){
	return ((PORTD & 0xF00) >> 8);			//Returns bits 11 through 8 of PORTD register shifted to LSB
}

int getbtns(){
	return ((PORTD & 0xE0) >> 5);				//Returns bits 7 through 5 of PORTD register shifted to LSB
}
