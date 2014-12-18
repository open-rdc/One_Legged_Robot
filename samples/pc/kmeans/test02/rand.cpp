#include<iostream>

using namespace std;

#define NUM 10

int main()
{
	srand(NUM);
	for(int i=0; i<NUM; i++){
		cout<<rand()<<endl;
	}
}