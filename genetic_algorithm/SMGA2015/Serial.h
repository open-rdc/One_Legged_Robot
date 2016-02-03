#ifndef SERIAL_H_
#define SERIAL_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>

using namespace boost::asio;

class Serial
{
public:
	Serial();
	void Init();
	void close();
	void AsyncBoostWrite(std::string buf);
	void BoostWrite(std::string buf);
	void BoostRead();
	int GetSerialBuf();

private:
	boost::array<char,64> buf;
	void ReadCallBack(const boost::system::error_code& e, std::size_t size);
	void WriteCallBack(const boost::system::error_code& e, std::size_t size);

	io_service io;
	serial_port port;
};
#endif