#include <stdlib.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game.h"			/* Declaration of functions, arrays etc for this game */

int playerSpriteYs[] = {0,	 1, 1,	 2, 2, 2, 2,	 3, 3, 3, 3, 3, 	 4, 4, 4, 4,  	5, 5, 	6};
int playerSpriteXs[] = {3,	 3, 2,	 4, 3, 2, 1,	 3, 4, 2, 1, 0,		 4, 3, 2, 1,  	3, 2, 	3};

int enemySpriteYs[] = {1, 1,	2, 2, 	3, 3, 3,	4, 4, 4, 4, 4,	5, 5, 5, 5, 5, 5, 5, 5,		6, 6, 6, 6, 6,	7, 7,	7, 	8, 8, 	9, 9};
int enemySpriteXs[] = {1, 2,	0, 3,		3, 4, 5,	3, 4, 5, 6, 7,	1, 2, 3, 4, 5, 6, 7, 8,		3, 4, 5, 6, 7,	3, 4, 5,	0, 3,		1, 2};
