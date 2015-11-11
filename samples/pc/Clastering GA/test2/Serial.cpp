#include "Serial.h"

const char *PORT = "COM12";
io_service io;
serial_port port(io, PORT);

void Serial::Init()
{	
	port.set_option(serial_port_base::baud_rate(9600));
	port.set_option(serial_port_base::character_size(8));
	port.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
	port.set_option(serial_port_base::parity(serial_port_base::parity::none));
	port.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));

	boost::thread thr_io(boost::bind(&io_service::run, &io));
}

void Serial::close()
{
	port.close();
}

void Serial::ReadCallBack(const boost::system::error_code& e, std::size_t size)
{
	port.async_read_some(buffer(buf), boost::bind(&Serial::ReadCallBack, this, _1, _2));
	io.run();
}

void Serial::WriteCallBack(const boost::system::error_code& e, std::size_t size )
{
	std::cout << "write :" << size << "byte[s]" << std::endl;
}

void Serial::AsyncBoostWrite(std::string buf)
{
	port.async_write_some(buffer(buf), boost::bind(&Serial::WriteCallBack, this, _1, _2));
	io.run();
}

void Serial::BoostWrite(std::string buf)
{
	port.write_some(buffer(buf));
}

void Serial::BoostRead()
{
	port.async_read_some(buffer(buf), boost::bind(&Serial::ReadCallBack, this, _1, _2 ));
	io.run();
}

int Serial::GetSerialBuf()
{
	int buf2i = std::stoi(buf.data());

	return buf2i;
}