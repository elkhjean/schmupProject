#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game.h"			/* Declaration of functions, arrays etc for this game */



void set_bit(int x, int y, uint8_t objectBits[]){
	int yOffset = y/8;
	objectBits[x + yOffset*128] |= (1 << (y - yOffset*8));
}



void clr_bit(int x, int y, uint8_t objectBits[]){
	int yOffset = y/8;
	objectBits[x + yOffset*128] &= (0 << (y - yOffset*8));
}



void move_sprite(int x, int y, struct object *obj){
	int i;
	int len = (*obj).arrLength;
	for(i=0; i<len; i++){
		clr_bit((*obj).x[i], (*obj).y[i], display);
		(*obj).x[i] += x;
		(*obj).y[i] += y;
		}
	for(i=0; i<len; i++)
		set_bit((*obj).x[i], (*obj).y[i], display);
}
