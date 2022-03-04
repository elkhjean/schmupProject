#include <stdlib.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "game.h"			/* Declaration of functions, arrays etc for this game */


/* Address of the EEPROM on the I2C bus */

#define WRITE 	0xA0
#define READ  	0xA1
#define MEMREG	0x05
#define CONREG	0x00

uint16_t score[5];


void I2C_INIT(){
	  I2C1BRG = 0x0C2;
	  I2C1CON = 0x0;
	  I2C1CONSET = 1 << 13;  // Discontinue module operation when the device enters Idle mode
	  I2C1CONSET = 1 << 15;  //  Enables the I2C module and configures the SDAx and SCLx pins as serial port pins
	  I2C1RCV = 0x0;       	//   Clear Receive Data Buffer bits
		do{
			I2C_START();
			}while(!I2C_WRITE(WRITE));			  
	  I2C_WRITE(CONREG);													
	  I2C_WRITE(0x0);												
	  I2C_IDLE();													
	  I2C_STOP();		
}

void I2C_IDLE(){
    while(I2C1CON & 0x1F);
    
    while(I2C1STAT & (1 << 14));
    
}

uint8_t I2C_WRITE(uint8_t data){
    I2C_IDLE();
    I2C1TRN = data;
    I2C_IDLE();
    return !(I2C1STAT & (1 << 15));
    
}
//LÄSER EN BYTE FRÅN I2C BUSSEN
uint8_t I2C_READ(){
    I2C_IDLE();
    I2C1CONSET = 1 << 3;
    I2C_IDLE();
    I2C1STATCLR = 1 << 6; //I2COV = 0
    return I2C1RCV;
}

void I2C_ACK(){
    I2C_IDLE();
    I2C1CONCLR = 1 << 5; //ACKDT = 0
    I2C1CONSET = 1 << 4; //ACKEN = 1
    I2C_IDLE();
    
}

void I2C_NACK() {
    I2C_IDLE();
    I2C1CONSET = 1 << 5; //ACKDT = 1
    I2C1CONSET = 1 << 4; //ACKEN = 1
}

void I2C_START() {
    I2C_IDLE();
    I2C1CONSET = 1 << 0; //SEN
    I2C_IDLE;
}

/* Send restart conditon on the bus */
void I2C_RESTART() {
    I2C_IDLE();
    I2C1CONSET = 1 << 1; //RSEN
    I2C_IDLE();
}

/* Send stop conditon on the bus */
void I2C_STOP() {
    I2C_IDLE();
    I2C1CONSET = 1 << 2; //PEN
    I2C_IDLE();
}

uint8_t READ_EEPROM(){
 			int i;
 			uint8_t score;
			do{
          I2C_START();  
        }while(!I2C_WRITE(WRITE));
        
      I2C_WRITE(MEMREG);         	      

			do{
					I2C_START();
				}while(!I2C_WRITE(READ));
				
			score = I2C_READ();
    	I2C_NACK();
		  I2C_STOP();
		  
    	return score;
}






void WRITE_EEPROM(uint8_t score){
 			int i;
			do{
         		I2C_START();  
        }while(!I2C_WRITE(WRITE));
        
       I2C_WRITE(MEMREG);      
						  
			do{
						I2C_START();
				}while(!I2C_WRITE(WRITE));
						 
			I2C_WRITE(score);
			I2C_ACK();			 	
    	I2C_NACK();
		  I2C_STOP();

}


//int main(void){
//    uint16_t score[];
//
//    I2C_INIT();
//
//    do{
//        I2C_START();
//    } while(!EEPROM << 1);
//
//    I2C_WRITE(EEPROM_REG_CONF);
//    I2C_WRITE(0x0);
//    i2c_stop;
//
//    for(;;){
//
//        do{
//            I2C_START();
//
//        } while(!EEPROM << 1)
//
//        I2C_WRITE(EEPROM_REG_CONF);
//
//        do{
//            I2C_START();
//        } while((!EEPROM << 1) | 1));
//
//    }
//
//
//
//
//
//}


