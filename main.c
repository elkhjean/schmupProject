
#include <stdlib.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game.h"			/* Declaration of functions, arrays etc for this game */
/*
int runGame = 0;

int main(void) {

	setup();
	display_init();
	ioInit();
	while(1){
	interrupts_and_timers_init();
	main_menu();
	T2CONSET = (1 << 15);	//Turning on timer 2
	initialize_player_sprite();
	
	while( runGame == 1 )
	{		
				gameWork();
	}
}
	
	return 0;
}

void main_menu(){

	display_string(0, " SPACE SHOOTER");
	display_string(1, "BTN 4 = highscore");
	display_string(2, "BTN 3 = start game");
	display_string(3, "Welcome!");
	display_update();
	
	while(runGame == 0){
		if(getsw()>>1 & 0x1 == 1)
				runGame = 1;
	}
}
*/
