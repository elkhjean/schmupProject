#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game.h"			/* Declaration of functions, arrays etc for this game */



void set_bit(int x, int y, uint8_t map[]){
	int row = y/8;
	map[x + row*128] |= (1 << (y - row*8));
}

void clr_bit(int x, int y, uint8_t map[]){
	int row = y/8;
	map[x + row*128] &= (0 << (y - row*8));
}

void move_sprite(int x, int y, struct object *obj, uint8_t map[]){
		int i;
		int len = (*obj).arrLength;
		int* currentX = (*obj).x;
		int* currentY = (*obj).y;

		for(i=0; i<len; i++)
			if(currentX[i] + x > 127 || currentX[i] + x < 0 
							|| currentY[i] + y > 31 || currentY[i] + y < 0)
				return;
					
		for(i=0; i<len; i++){
			clr_bit(currentX[i], currentY[i], map);
			currentX[i] += x;
			currentY[i] += y;
		}
			
		for(i=0; i<len; i++)
			set_bit(currentX[i], currentY[i], map);
}

void fire_projectile(struct object *obj){
		int* currentX = (*obj).x;
		int* currentY = (*obj).y;
		
		if((*obj).isPlayer == 1)
			set_bit( currentX[10], currentY[10], playerProjectileMap);
		else(set_bit( currentX[10], currentY[10], enemyProjectileMap));
}

void update_projectile_maps(){
		int i;
		uint8_t temp[512];
		
		for(i = 0; i<512; i++){
			display[i] &= playerProjectileMap[i];
			display[i] &= enemyProjectileMap[i];
		}
		for(i = 0; i<511; i++)
				temp[i] = playerProjectileMap[i+1];
		temp[511]=0;
		for(i = 0; i<512; i++)
				playerProjectileMap[i] = temp[i];
						
				
		for(i = 511; i>1; i--)
				temp[i] = enemyProjectileMap[i-1];
		temp[0]=0;
		for(i = 511; i>0; i--)
				enemyProjectileMap[i] = temp[i];
				
		for(i = 0; i<512; i++){
				display[i] |= playerProjectileMap[i];
				display[i] |= enemyProjectileMap[i];
			}
}

int projectile_hit(struct object *obj){
		int* currentX = (*obj).x;
		int* currentY = (*obj).y;
		int i;
		uint8_t tempBitMap[512];
		move_sprite(0, 0, obj, tempBitMap);
			
		if((*obj).isPlayer == 1){
				for(i = 0; i < 512; i++)
						if(enemyProjectileMap[i] != 0 && enemyProjectileMap[i] == tempBitMap[i])
							return 1;
		}
							
		if((*obj).isPlayer == 0){
				for(i = 0; i < 512; i++)
						if(playerProjectileMap[i] != 0 && playerProjectileMap[i] == tempBitMap[i])
							return 1;
		}					
		return 0;
}

