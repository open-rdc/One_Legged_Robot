#include <iostream>
#include <time.h>
#include <windows.h>

using namespace std;

#define NUM 10
#define cNUM 3

int GetRandom(int min,int max)
{
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

int main()
{
	int num[10];
	srand((unsigned int)time(NULL));

	cout << "No.1" << endl;
	for(int i=0; i<NUM; i++){
		num[i] = GetRandom(0, 100);
		cout << "num[" << i << "]: " << num[i] << endl;
	}

	Sleep(2);

	cout << "No,2" << endl;

	for(int i=0; i<NUM; i++){
		cout << "num[" << i << "]: " << num[i] << endl;
	}
}
