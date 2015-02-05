#include "OneLeggedRobot.h"

void OLR::MakeSring()
{
	SetAngle();

	for(int i=0; i<RANDOM_MAX; i++)
	{
		for(int j=0; j<PARAMETER_NUM; j++)
		{
			str[i] += std::to_string(angle[i][j]);
			str[i] += ",";
			
			if(j == PARAMETER_NUM-1)
			{
				str[i] += "\n";
			}
		}
	}
}

void OLR::RobotMove()
{
	int enc;
	for(int i=0; i<RANDOM_MAX; i++)
	{
		serial.BoostWrite("s");
		for(int j=0; j<5; j++)
		{
			serial.BoostWrite(str[i]);
			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
		}
		std::cout << "str[" << i << "]: " << str[i] << std::endl;
		boost::this_thread::sleep(boost::posix_time::seconds(SLEEP_TIME));
		for(int k=0; k<100; k++)
		{
			serial.BoostRead();
			boost::this_thread::sleep(boost::posix_time::milliseconds(50));
		}
		enc = serial.GetSerialBuf();
		std::cout << "ReadEnc: " << enc << std::endl;
		move_result[i] = enc;
	}
}

void OLR::SetAngle()
{
	for(int i=0; i<RANDOM_MAX; i++)
	{
		for(int j=0; j<RANDOM_MAX; j++)
		{
			angle[i][j] = ga.GetAngle(i, j);
		}
	}
}

int OLR::GetMoveResult(int random_num)
{
	return move_result[random_num];
}