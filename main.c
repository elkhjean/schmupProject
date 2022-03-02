

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game.h"			/* Declaration of functions, arrays etc for this game */

int state = 0;

int main(void) {

	setup();
	display_init();
	ioInit();
	interrupts_and_timers_init();
	
	display_image(0, display);
	display_update();
	display_string(0, "KTH/ICT lab");
	display_string(1, "in Computer");
	display_string(2, "Engineering");
	display_string(3, "Welcome!");
	display_update();
	
	initialize_player_sprite();
	
	while( 1 )
	{
	  gameWork();
	}
	return 0;
}
