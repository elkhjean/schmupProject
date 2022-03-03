#include <stdlib.h>
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

void move_sprite(int x, int y, struct object *obj, uint8_t mapFrom[], uint8_t mapTo[]){
		int i;
		int len = (*obj).arrLength;
		int* currentX = (*obj).x;
		int* currentY = (*obj).y;

		for(i=0; i<len; i++)
			if(currentX[i] + x > 127 || currentX[i] + x < 0 
							|| currentY[i] + y > 31 || currentY[i] + y < 0){
					x =0;
					y =0;
					break;
				}			
		for(i=0; i<len; i++){
			clr_bit(currentX[i], currentY[i], mapFrom);
			currentX[i] += x;
			currentY[i] += y;
		}
			
		for(i=0; i<len; i++)
			set_bit(currentX[i], currentY[i], mapTo);
}

void reset_sprite(struct object *obj, int spriteOriginXs[], int spriteOriginYs[]){
		int i;
		int len = (*obj).arrLength;
		int* currentX = (*obj).x;
		int* currentY = (*obj).y;
		for(i=0; i<len; i++){
			currentX[i] = spriteOriginXs[i];
			currentY[i] = spriteOriginYs[i];
			}
}

void fire_projectile(struct object *obj, int isPlayer){
		int* currentX = (*obj).x;
		int* currentY = (*obj).y;
		
		if(isPlayer == 1){
			set_bit( currentX[10], currentY[10], playerProjectileMap);
			set_bit( currentX[10]+1 , currentY[10], playerProjectileMap);
			}
		else{
				set_bit( currentX[10], currentY[10], enemyProjectileMap);
				set_bit( currentX[10]-1, currentY[10], enemyProjectileMap);
				set_bit( currentX[10], currentY[10]+1, enemyProjectileMap);
				set_bit( currentX[10]-1, currentY[10]+1, enemyProjectileMap);
				};
}


void update_projectile_maps(){
		int i;
		int j;
		uint8_t temp[512];
		
		
		for(i = 0; i<512; i++)
				temp[i] = playerProjectileMap[i];		
		for(j=0; j<4; j++){
				for(i = 1; i<128; i++)
						playerProjectileMap[i - 1 + j*128] = temp[i + j*128];
				playerProjectileMap[127 + j*128] = 0;
		}
		
		
		for(i = 0; i<512; i++)
				temp[i] = enemyProjectileMap[i];		
		for(j=0; j<4; j++){
				for(i = 0; i<127; i++)
						enemyProjectileMap[i + 1 + j*128] = temp[i + j*128];
				enemyProjectileMap[j*128] = 0;
		}
		
		for(i = 0; i<512; i++){
				display[i] |= playerProjectileMap[i];
				display[i] |= enemyProjectileMap[i];
		}
}

void clr_display(uint8_t map[]){
		int i;
		for(i = 0; i<512; i++)
		map[i] =0;
}

int projectile_hit(struct object *obj, uint8_t map[]){
		int i;
		int len = (*obj).arrLength;
		int* currentX = (*obj).x;
		int* currentY = (*obj).y;
		int row;

		for(i = 0; i<len; i++){
				row = currentY[i]/8;
				if((map[currentX[i] + row*128] & (1 << (currentY[i] - row*8))) != 0){
						clr_bit(currentX[i], currentY[i], map);
						return 1;
				}
		}
		return 0;
}
