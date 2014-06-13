#include "mbed.h"
#include <stdio.h>
#include <string.h>

#define NUM_DATA 10
#define LEN_DATA 20

char zoo[] = "Cat, Dog, Tiger, Bug, Bird, Fish, Seep, Cow, Pig, Rat";

Serial pc(USBTX, USBRX);

int main()
{
    char animal[NUM_DATA][LEN_DATA];
    char *token = " ,";
    int i;

    pc.printf("original\t");
    pc.printf("%s\n\n", zoo);

    pc.printf("token:\n");

    strcpy(animal[0], strtok(zoo, token));

    pc.printf("%s\t", animal[0]);

    for (i = 1;  i < NUM_DATA; i++) {
        strcpy(animal[i], strtok(NULL, token));
        pc.printf("%s\t", animal[i]);
    }
}
