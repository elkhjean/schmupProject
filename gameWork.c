#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game.h"			/* Declaration of functions, arrays etc for this game */

int timeoutcount = 0;
int moveX= 0;
int moveY= 0;


struct object playerShip = {playerSpriteXs, playerSpriteYs, 19};


/*initialization of interrupts and timers*/
void interrupts_and_timers_init( void ){
	T2CON = 0; 						//Stopping and clearing the timer control register
	TMR2 = 0;							//Resetting timer count to zero
	T2CONSET  = (7 << 4);	//Initializing timer 2 to 1:256 prescale by setting bits 6:4 to 111, clock rate is now 312500HZ.
	PR2 = 31250;					//Setting one clock period to be 31250 cycles to get 10 time-outs per second: 31250*10=312500
	IPC(2) = 0xF;					//setting proity to 3 and subpriority to 3
	IFSCLR(0) = (1 << 8);	//Clear timer 2 interrupt flag
	IECSET(0) = (1 << 8);	//Enable interrupts for timer 2
	enable_interrupts();	//Enable interrupts for microcontroller
	T2CONSET = (1 << 15);	//Turning on timer 2
  return;
}



/* Interrupt Service Routine */
void user_isr( void ){
	IFSCLR(0) = (1<<8);									//Clear timer 2 interrupt flag
	timeoutcount++;
	if(moveX !=0 || moveY !=0){									
		move_sprite(moveX, moveY, &playerShip);
		moveX = 0;
		moveY = 0;
	}
	display_image(0, display);
}



/* This function is called repetitively from the main program */
void gameWork( void )
{
	if(getbtns() & 0x1 == 1)
		moveX = 1;
		
	if(getbtns()>>1 & 0x1 == 1)
		moveX = -1;
		
	if(getbtns()>>2 & 0x1 == 1)
		moveY = 1;

	if(timeoutcount == 1){
		timeoutcount = 0;
		}
}
