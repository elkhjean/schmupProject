
#include <stdio.h>
#include <pic32mx.h>

/* Address of the EEPROM on the I2C bus */
#define EEPROM 0x50;
#define WRITE 0;
#define READ  1;

uint16_t score[5];

typedef enum EEPROM_REG EEPROM_REG;
enum TempSensorReg {
    EEPROM_REG_SCORE,
    EEPROM_REG_CONF,
    EEPROM_REG_HYST,
    EEPROM_REG_LIMIT,
};

void I2C_INIT(){
    I2CBRG = 0x0C2;
    I2C1CON = 0x0;
    I2C1CONSET = 1 << 13;  // Discontinue module operation when the device enters Idle mode
    I2C1CONSET = 1 << 15  //  Enables the I2C module and configures the SDAx and SCLx pins as serial port pins
    I2C1RCV = 0x0;       //   Clear Receive Data Buffer bits
    
}

void I2C_IDLE(){
    while(I2C1CON & 0x1F);
    
    while(I2C1STAT & (1 << 14));
    
}

void I2C_WRITE(uint8_t data){
    I2C_IDLE();
    IN2C1TRN = data;
    I2C_IDLE();
    return !(I2C1STAT & (1 << 15));
    
}
//LÄSER EN BYTE FRÅN I2C BUSSEN
void I2C_READ(){
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
    i2c_idle();
    
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

int *READ_EEPROM(uint16_t score){
    
    I2C_INIT();
    
    do{
        I2C_START();
    } while(!EEPROM << 1);
    
    I2C_WRITE(EEPROM_REG_CONF);
    I2C_WRITE(0x0);
    i2c_stop;
    
    for(int i = 0; i < 5; i++){
        
        do{
            I2C_START();
            
        } while(!EEPROM << 1)
        
        I2C_WRITE(EEPROM_REG_CONF);
        
        do{
            I2C_START();
        } while((!EEPROM << 1) | 1));
        
        score[i] = I2C_READ() << 8;
        I2C_ACK();
        score[i] |= I2C_READ();
        I2C_NACK();
        I2C_STOP();
        
    }
    return score;
}

int *WRITE_EEPROM(uint16_t score){
    
    I2C_INIT();
    
    do{
        I2C_START();
    } while(!EEPROM << 1);
    
    I2C_WRITE(EEPROM_REG_CONF);
    I2C_WRITE(0x0);
    i2c_stop;
    
    for(int i = 0; i < 5; i++){
        
        do{
            I2C_START();
            
        } while(!EEPROM << 1)
        
        I2C_WRITE(EEPROM_REG_CONF);
        
        do{
            I2C_START();
        } while((!EEPROM << 1) | 1));
        
        score[i] = I2C_WRITE() << 8;
        I2C_ACK();
        score[i] |= I2C_WRITES();
        I2C_NACK();
        I2C_STOP();
        
    }
    return score;
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


