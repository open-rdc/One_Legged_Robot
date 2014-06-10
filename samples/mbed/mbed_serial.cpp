#include "mbed.h"

Serial pc(USBTX, USBRX);
DigitalOut led1(LED1);

int main()
{
    char buffer[20];
    while(1){
        if (pc.readable()){
            pc.scanf("%s", &buffer);
        }
        pc.printf("%s\n", buffer);
        if(!strcmp(buffer, "on")){
            led1 = 1;
        }
        if(!strcmp(buffer, "off")){
            led1 = 0;
        }
    }
}