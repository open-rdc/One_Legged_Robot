#include <iostream>
#include <time.h>

using namespace std;

#define NUM 10

int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

int main()
{
	srand((unsigned int)time(NULL));
	for(int i=0; i<NUM; i++){
		cout << GetRandom(0,100) << endl;
	}
}