#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <iostream>

using namespace boost::asio;

const char *PORT = "COM3";
io_service io;
serial_port port( io, PORT );
boost::array<char, 64> rbuf;

void read_callback(const boost::system::error_code& e, std::size_t size)
{
	std::cout.write(rbuf.data(), size);
	port.async_read_some(buffer(rbuf), boost::bind(&read_callback, _1, _2 ));
}

void write_callback(const boost::system::error_code& e, std::size_t size )
{
	std::cout << "write :" << size << "byte[s]" << std::endl;
}

int main(int argc, char *argv[])
{
	std::string wbuf_on = "on\n";
	std::string wbuf_off = "off\n";

	port.set_option(serial_port_base::baud_rate(9600));
	port.set_option(serial_port_base::character_size(8));
	port.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
	port.set_option(serial_port_base::parity(serial_port_base::parity::none));
	port.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));

	boost::thread thr_io(boost::bind(&io_service::run, &io));

	while(1){
		port.async_read_some(buffer(rbuf), boost::bind(&read_callback, _1, _2 ));
		port.async_write_some(buffer(wbuf_on), boost::bind(&write_callback, _1, _2));
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
		port.async_read_some(buffer(rbuf), boost::bind(&read_callback, _1, _2 ));
		port.async_write_some(buffer(wbuf_off), boost::bind(&write_callback, _1, _2));
		boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
	}
	return 0;
}