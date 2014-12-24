#include <iostream>
#include <string>
#include <sstream>

int main()
{
	std::string str;
	int servo_angle = 10;
	int servo_time = 1000;

	str = std::to_string(servo_angle);

	std::cout << "First insert: " << str << std::endl;

	str += ",";

	str += std::to_string(servo_time);

	std::cout << "Second insert: " << str << std::endl;
}

