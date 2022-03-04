#include <stdlib.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game.h"			/* Declaration of functions, arrays etc for this game */

#define MAX_ENEMIES 6

int gameOver = 0;
int runGame = 0;
int timeoutcount = 0;
int moveX= 0;
int moveY= 0;
int fireFlag = 0;
int activeEnemies[] ={0, 0, 0, 0, 0, 0};
int eX[] ={1, 1, 1, 1, 1, 1};
int eY[] ={0, 0, 0, 0, 0, 0};
int score = 0;
char textstring[] = "    ";
struct object playerShip;
struct object enemies[MAX_ENEMIES];
	
	
int main(void) {

	setup();
	
	display_init();
	
	ioInit();
	
	interrupts_and_timers_init();
	
	while(1){
		
		main_menu();
		
		start_game();
		
		while( runGame == 1 )
		{		
			gameWork();
		}
		
		interrupts_and_timers_init();
		
		game_over();
	}
		
	return 0;
}
	
	
/*initialization of interrupts and timers*/
void interrupts_and_timers_init( void ){
	T2CON = 0; 						//Stopping and clearing the timer control register
	TMR2 = 0;							//Resetting timer count to zero
	T2CONSET  = (7 << 4);	//Initializing timer 2 to 1:256 prescale by setting bits 6:4 to 111, clock rate is now 312500HZ.
	PR2 = 6250;						//Setting one clock period to be 31250 cycles to get 10 time-outs per second: 31250*10=312500
	IPC(2) = 0xF;					//setting proity to 3 and subpriority to 3
	IFSCLR(0) = (1 << 8);	//Clear timer 2 interrupt flag
	IECSET(0) = (1 << 8);	//Enable interrupts for timer 2
	enable_interrupts();	//Enable interrupts for microcontroller
  return;
}



/* Interrupt Service Routine */
void user_isr( void ){
		IFSCLR(0) = (1<<8);	//Clear timer 2 interrupt flag
		int i;
		timeoutcount++;
		
		clr_display(display);
		
		if(fireFlag == 1 && (timeoutcount % 20 == 0)){
				fire_projectile(&playerShip, 1);
				fireFlag = 0;
				}
		
		update_projectile_maps();
		
		move_sprite(0, moveY, &playerShip, display, display);	
		moveY = 0;
		
		if(timeoutcount == 99)
			spawn_enemies();
		
		if(timeoutcount % 2 == 0)
			move_enemies();

		for(i = 0; i<MAX_ENEMIES; i++)
						if(activeEnemies[i] != 0)
								enemy_advance(0, 0, i);
		
		check_enemies_hit();
		
		
		if(timeoutcount % 20 == 0)
			enemy_fiire();
			for(i=0; i<MAX_ENEMIES; i++){
					if((enemies[i].x[i] + enemies[i].y[i]) % 4 == 0)
							fire_projectile(&enemies[i], 0);
					}
					
		check_player_hit();
		
		display_image(0, display);
		
		if(timeoutcount>99)
			timeoutcount = 0;
}



void enemy_advance(int x, int y, int i){
		move_sprite(x, y, &enemies[i], display, display);
}


void initialize_player_sprite(){
	move_sprite(120, 16, &playerShip, display, display);
}



void gameWork( void )
{

		
		if(getbtns() & 0x1 == 1)
			moveY = 1;
			
		if(getbtns()>>1 & 0x1 == 1)
			moveY = -1;
			
		if(getbtns()>>2 & 0x1 == 1)
			fireFlag = 1;

}




void main_menu(){

	display_string(0, " SPACE SHOOTER");
	display_string(1, "	");
	display_string(2, " sw2: Start Game");
	display_string(3, " 	");
	display_update();
	
	while(runGame == 0){
		if(getsw()>>1 & 0x1 == 1)
				runGame = 1;

/*				
		uint8_t score = 25;
		int result =0;
		
		WRITE_EEPROM(score);
		
		result = (int) READ_EEPROM();
		char s[2];
		num32asc( s, result );
		
		display_string(0, s );
		display_update();
		
		*/
		
	}
}



void start_game(){
	int i;
	playerShip.arrLength = 19;
	reset_sprite(&playerShip, playerSpriteXs, playerSpriteYs);
	
	clr_display(playerProjectileMap);
	clr_display(enemyProjectileMap);

	for(i = 0; i < MAX_ENEMIES; i++){
	 		enemies[i].arrLength = 32;
	 		reset_sprite(&enemies[i], enemySpriteXs, enemySpriteYs);
	 		activeEnemies[i] = 0;
	 		}

	initialize_player_sprite();	
	T2CONSET = (1 << 15);	//Turning on timer 2
}


void game_over(){

//		time2string( textstring, score );
//		num32asc( textstring, score );
//		num32asc( &textstring[1], score );
		score = 0;
		display_string(0, " GAME OVER");
		display_string(1, " 	");
		display_string(2, "	SW3: main menu");
		display_string(3, "	");
		display_update();
		
	while(gameOver == 1){
		if(getsw()>>2 & 0x1 == 1)
				gameOver = 0;
	}
}


void spawn_enemies(){
		int i;
			for(i = 0; i<MAX_ENEMIES; i++)
					if(activeEnemies[i] == 0){
							activeEnemies[i] = 1;
							break;
							}
}


void move_enemies(){
		int i;
				for(i=0; i<MAX_ENEMIES; i++){
						if(activeEnemies[i] != 0){
								if(enemies[i].x[10] > 100)
										eX[i] = -1;
								if(enemies[i].x[0] < 4)
										eX[i] = 1;
								
								if(enemies[i].y[31] > 30)
										eY[i] = -1;
								if(enemies[i].y[0] < 2)
										eY[i] = 1;	
								enemy_advance(eX[i], eY[i], i);		
						}
				}
			}
			
void check_enemies_hit(){
		int i;
		for(i = 0; i<MAX_ENEMIES; i++){
				int hit = 0;
				hit = projectile_hit(&enemies[i], playerProjectileMap);
				if(hit != 0 ){
						score++;
						activeEnemies[i] = 0;
						reset_sprite(&enemies[i], enemySpriteXs, enemySpriteYs );
					}
				}
}

void check_player_hit(){
		int i;
		if(projectile_hit(&playerShip, enemyProjectileMap)){
				runGame = 0;
				gameOver = 1;
				}
}

