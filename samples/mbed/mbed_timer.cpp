#include "mbed.h"

Serial pc(USBTX, USBRX);

int main() {
    Timer t;
    t.start();
    printf("Start timer\n");
    
    while(1)
    {
        float now_time = t.read();
        printf("time %f seconds \n", now_time);
        
        if(now_time > 30)
        {
            t.stop();
            printf("End\n");
            break;
        }
    }       
}
