/*--------------------------------------------------*/
/* @Program name : mbed                             */
/* @Author : Kohei Izumi                            */
/* @Comment : One Legged Robot program              */
/*                                                  */
/* Copyright(c) 2014 Kohei Izumi                    */
/*--------------------------------------------------*/

#include <iostream>
#include "mbed.h"
#include "QEI.h"

Serial device(p13, p14);        // tx = P9, rx = P10
DigitalOut REDE(p11);           // RS485 Transmit Enable
QEI enc(p7, p8, NC, 624);       // encoder pin
Serial pc(USBTX, USBRX);        // USB port

#define TIME 10
//#define DEBUG                   // Debug symbol

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
    unsigned char TxData[9];    // TransmitByteData [9byte]
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
    for(int i=2; i<=7; i++){
        CheckSum = CheckSum ^ TxData[i];                // XOR from ID to Data
    }
    
    TxData[8] = CheckSum;       // Sum
    
    // Send Packet 
    REDE = 1;                   // RS485 Transmit Enable
    for(int i=0; i<=8; i++){
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
    unsigned char TxData[10];   // TransmitByteData [10byte]
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
    for(int i=2; i<=8; i++){
        CheckSum = CheckSum ^ TxData[i];                // XOR from ID to Data
    }
    TxData[9] = CheckSum;       // Sum
    // Send Packet
    REDE = 1;                   // RS485 Transmitt Enable
    for(int i=0; i<=9; i++){
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
void SetTimeAndPosition(unsigned char ID, short data){
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
    TxData[8] = (unsigned char)0x00FF & (data >> 8);    // Hi  byte
    
    // CheckSum calculation
    for(int i=2; i<=8; i++){
        CheckSum = CheckSum ^ TxData[i];                // XOR from ID to Data
    }
    TxData[9] = CheckSum;       // Sum
    // Send Packet
    REDE = 1;                   // RS485 Transmitt Enable
    for(int i=0; i<=9; i++){
        device.putc(TxData[i]);
    }
    wait_us(250);               // Wait for transmission
    REDE = 0;                   // RS485 Transmit disable
}                

/*--------------------------------------------------*/
/* Function     : Read serial port character        */ 
/* NAME         : ReadSerial                        */
/* Argument     : ---                               */ 
/* Return value : send(servo angle or servo time)   */
/*--------------------------------------------------*/
int ReadSerial()
{
    char buffer[40];
    int i=0;
    while(1)
    {
        buffer[i] = pc.getc();
        if(buffer[i] == ',')
        {
            buffer[i] = NULL;
            break;
        }

        i++;
    }
    
    char *send_char = NULL;
    send_char = &(buffer[0]);
    int send = atoi(send_char);
    
    return send;
}

/*--------------------------------------------------*/
/* Function     : Check serial character            */
/* NAME         : SerialErrorCheck                  */
/* Argument     : ---                               */
/* Return value : true                              */
/*--------------------------------------------------*/
bool SerialErrorCheck()
{
    char buffer[100];
    int i=0;
    while(1)
    {
        buffer[i] = pc.getc();
        if(buffer[i] == '\n')
        {
            return true;
        }
        i++;
    }
}

int main() {
    Timer t;
    Init();                     // initialize
    Torque(0x01, 0x01);         // ID = 1(0x01) , torque = OFF (0x00)
    Torque(0x02, 0x01);
 
    while(1)
    {
        char ready = pc.getc();
        if(ready != 's')
        {
            continue;
        }
        
        SerialErrorCheck();
        int servo1_angle = ReadSerial(); // get character(servo1 angle)
        int servo2_angle = ReadSerial(); // get character(servo2 angle)
        int sleep = ReadSerial();        // get character(sleep time)
        
        t.start();
        while(1)
        {
#ifdef DEBUG
            pc.printf("servo1_angle: %d\n", servo1_angle);
            pc.printf("servo2_angle: %d\n", servo2_angle);
            pc.printf("sleep: %d\n", sleep);
            pc.printf("time %f seconds\n", t.read());
#endif
        
            SetPosition(0x01, servo1_angle);
            SetPosition(0x02, servo2_angle);

			wait_ms(sleep);

            SetPosition(0x01, 0);
            SetPosition(0x02, 0);

			wait_ms(sleep);
            
            if(t.read() > TIME)
            {
                t.stop();
                t.reset();
                break;
            }
        }

        pc.printf("%d\n", enc.getPulses()); // send to pc of encoder pulse
        enc.reset();
    }
}
