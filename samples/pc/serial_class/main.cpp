#include "Serial.h"

int main()
{
	Serial serial;
	std::string wbuf = "100,0,200,0,1000\n";
	serial.Init();

	while(1)
	{
		serial.BoostRead();
		serial.BoostWrite(wbuf);
	}
	
	return 0;
}