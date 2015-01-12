#include "Serial.h"

int main()
{
	Serial serial;
	//std::string wbuf = "137,1,1,94,801,\n";
	//std::string wbuf = "153,36,129,55,771,\n";
	std::string wbuf = "203,1,129,54,803,\n";
	int i=0;
	serial.Init();

	std::cout << "StartSerial" << std::endl;
	while(1)
	{
		serial.BoostWrite("s");
		for(int i=0; i<5; i++)
		{
			serial.BoostWrite(wbuf);
			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
		}
		boost::this_thread::sleep(boost::posix_time::seconds(11));
		serial.BoostRead();
	}
	
	return 0;
}