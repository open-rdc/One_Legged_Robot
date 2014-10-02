#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <iostream>

using namespace boost::asio;

const char *PORT = "COM3";
io_service io;
serial_port port(io, PORT);

class Serial
{
	boost::array<char, 64> buf;
	boost::system::error_code err;
public:
	Serial();
	void close();
	void BoostWrite(std::string buf);
	void BoostRead();
	void ReadCallBack(const boost::system::error_code& e, std::size_t size);
	void WriteCallBack(const boost::system::error_code& e, std::size_t size);
};