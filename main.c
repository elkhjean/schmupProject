

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game.h"			/* Declaration of functions, arrays etc for this game */

int state = 0;

int main(void) {

	setup();
	display_init();
	ioInit();
	interrupts_and_timers_init();
	
	display_string(1, "Welcome");
	display_string(2, "switch btn 4");
	display_string(3, "to start!");
	display_update;
	
	while(state = 0)
	{
			if(getbtns() & 0x1 == 1)
			state = 1;
	}

	while( 1 )
	{
	  gameWork();
	}
	return 0;
}
