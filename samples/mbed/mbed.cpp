/*--------------------------------------------------*/
/* @Program name ; mbed                             */
/* @Author : Kohei Izumi                            */
/* @Comment : One Legged Robot program              */
/*                                                  */
/* Copyright(c) 2014 Kohei Izumi                    */
/*--------------------------------------------------*/

#include "mbed.h"
#include "QEI.h"
Serial device(p9, p10);         // tx = P9, rx = P10
DigitalOut REDE(p11);           // RS485 Transmit Enable
QEI enc(p7, p8, NC, 624);       // encoder pin
Serial pc(USBTX, USBRX);        // USB serial

#define NUM_DATA 4
#define LEN_DATA 20

/*--------------------------------------------------*/
/* Funcyion     : mbed initialize                   */
/* NAME         : Init                              */
/* Argument     : ---                               */
/* Return value : ---                               */
/*--------------------------------------------------*/
void Init(void){
    device.baud(115200);        // baud Rate = 115.2kbps [Futaba default]
    REDE = 0;                   // RS485 Transmit disable
}
/*--------------------------------------------------*/
/* Funcyion     : Servo torque enable               */
/* NAME         : Torque                            */
/* Argument     : ID (Servo ID)                     */
/*              : data (Torque enable)              */
/* Return value : ---                               */
/*--------------------------------------------------*/
void Torque (unsigned char ID, unsigned char data){

    unsigned char TxData[10];    // TransmitByteData [10byte]
    unsigned char CheckSum = 0; // CheckSum calculation
    
    TxData[0] = 0xFA;           // Header
    TxData[1] = 0xAF;           // Header
    TxData[2] = ID;             // ID
    TxData[3] = 0x00;           // Flags
    TxData[4] = 0x24;           // Address
    TxData[5] = 0x01;           // Length
    TxData[6] = 0x01;           // Count
    TxData[7] = data;           // Data
    
    // CheckSum calculation
    CheckSum = TxData[2];
    for(int i=3; i<8; i++){
        CheckSum = CheckSum ^ TxData[i];
    }
    
    TxData[8] = CheckSum;       // Sum
    
    // Send Packet 
    REDE = 1;                   // RS485 Transmit Enable
    for(int i=0; i<9; i++){
        device.putc(TxData[i]);
    }
    wait_us(250);               // Wait for transmission
    REDE = 0;                   // RS485 Transmitt disable
}
/*--------------------------------------------------*/
/* Function     : Servo goal position instruction   */
/*                (Not specify time)                */
/* NAME         : SetPosition                       */
/* Argument     : ID (Servo ID)                     */
/*              : data (Set position)              */
/* Return value : ---                               */
/*--------------------------------------------------*/
void SetPosition (unsigned char ID, short data){

    unsigned char TxData[15];   // TransmitByteData [15byte]
    unsigned char CheckSum = 0; // CheckSum calculation
    
    TxData[0] = 0xFA;           // Header
    TxData[1] = 0xAF;           // Header
    TxData[2] = ID;             // ID
    TxData[3] = 0x00;           // Flags
    TxData[4] = 0x1E;           // Address
    TxData[5] = 0x02;           // Length
    TxData[6] = 0x01;           // Count
                                // Data
    TxData[7] = (unsigned char)0x00FF & data;           // Low byte
    TxData[8] = (unsigned char)0x00FF & (data >> 8);    // Hi  byte
    
    // CheckSum calculation
    CheckSum = TxData[2];
    for(int i=3; i<9; i++){
        CheckSum = CheckSum ^ TxData[i];
    }
    TxData[9] = CheckSum;       // Sum
    // Send Packet
    REDE = 1;                   // RS485 Transmitt Enable
    for(int i=0; i<10; i++){
        device.putc(TxData[i]);
    }
    wait_us(250);               // Wait for transmission
    REDE = 0;                   // RS485 Transmit disable
}

/*--------------------------------------------------*/
/* Function     : Set the time and position         */ 
/* NAME         : SetTimeAndPosition                */
/* Argument     : ID (servo ID)                     */
/*              : data (set position)               */
/*              : time (time to move)               */ 
/* Return value : ---                               */
/*--------------------------------------------------*/
void SetTimeAndPosition(unsigned char ID, short data, unsigned short stime){
    unsigned char TxData[15];   // TransmitByteData [15byte]
    unsigned char CheckSum = 0; // CheckSum calculation
    
    TxData[0] = 0xFA;           // Header
    TxData[1] = 0xAF;           // Header
    TxData[2] = ID;             // ID
    TxData[3] = 0x00;           // Flags
    TxData[4] = 0x1E;           // Address
    TxData[5] = 0x04;           // Length
    TxData[6] = 0x01;           // Count
                                // Data
    TxData[7] = (unsigned char)0x00FF & data;           // Low byte
    TxData[8] = (unsigned char)0xFF00 & (data >> 8);    // Hi  byte
    TxData[9] = (unsigned char)0x00FF & stime;           // Low byte
    TxData[10] = (unsigned char)0xFF00 & (stime >> 8);   // Hi  byte
    
    // CheckSum calculation
    CheckSum = TxData[2];
    for (int i=3; i<11; i++) {
        CheckSum = CheckSum ^ TxData[i];
    }
    TxData[11] = CheckSum;      // Sum

    // Send Packet
    REDE = 1;                   // Transmit Enable
    for(int i=0; i<12; i++){
        device.putc(TxData[i]);
    }
    wait_us(250);               // Wait for transmission
    REDE = 0;                   // Transmitt disable
}

/*--------------------------------------------------*/
/* Function     : Return buffer                     */
/* NAME         : ReturnBuffer                      */
/* Argument     : buffer                            */
/* Return value : buffer                            */
/*--------------------------------------------------*/
char *ReturnBuffer(char buffer[20]){
    return buffer;
}

/*--------------------------------------------------*/
/* Function     : Receive                           */
/* NAME         : Receive                           */
/* Argument     : ---                               */
/* Return value : ReturnBuffer                      */
/*--------------------------------------------------*/
char *Receive(){
    char buffer[20];
    if(pc.readable()){
        pc.scanf("%s", &buffer);
    }
    return ReturnBuffer(buffer);
}

/*--------------------------------------------------*/
/* Function     : main program                      */ 
/* NAME         : main                              */
/* Argument     : ---                               */
/* Return value : ---                               */
/*--------------------------------------------------*/
int main() {
    Init();                     // initialize
    Torque(0x01, 0x01);         // ID = 1(0x01) , torque = OFF (0x00)
                                // torque = OFF(0x00), ON(0x01), BRAKE(0x02)
    char buffer[20];
    char split_data[NUM_DATA][LEN_DATA];
    char *token = ",";                            
    
    wait(1);                    // wait (1sec)
    while(1){
        strcpy(buffer, Receive());
        //split
        strcpy(split_data[0], strtok(buffer, token));
        for (int i = 1;  i < NUM_DATA; i++) {
            strcpy(split_data[i], strtok(NULL, token));
            //pc.printf("%s\n", split_data[i]);
        }
        
        //send servo
        SetPosition(0x01,(short)split_data[0]); // ID = 1(0x01) , GoalPosition = 30.0deg(300)
        wait(1);                // wait (1sec)
        SetPosition(0x01,(short)split_data[2]);// ID = 1(0x01) , GoalPosition = -30.0deg(-300) 
        wait(1);                // wait (1sec)
        
        //get pulses
        pc.printf("%07d\n", enc.getPulses());
    }
}
