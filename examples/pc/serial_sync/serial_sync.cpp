#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <iostream>

using namespace boost::asio;

int main(int argc, char *argv[])
{
	std::string wbuf_on = "on\n";
	std::string wbuf_off = "off\n";
	char rbuf[32];
	std::size_t length;

	const char *PORT = "COM3";
	io_service io;
	serial_port port( io, PORT );
	port.set_option(serial_port_base::baud_rate(9600));
	port.set_option(serial_port_base::character_size(8));
	port.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
	port.set_option(serial_port_base::parity(serial_port_base::parity::none));
	port.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));

	while(1){
		//on
		port.write_some(buffer(wbuf_on));
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		length = port.read_some(buffer(rbuf));
		std::cout.write(rbuf, length);
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));

		//off
		port.write_some(buffer(wbuf_off));
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		length = port.read_some(buffer(rbuf));
		std::cout.write(rbuf, length);
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	}
	return 0;
}