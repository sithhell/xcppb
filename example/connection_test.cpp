
#include <xcppb/connection.hpp>

#include <boost/asio/local/stream_protocol.hpp>

#include <string>
#include <iostream>

namespace asio = boost::asio;

int main()
try
{
	const std::string x_socket_path = "/tmp/.X11-unix/X0";

	asio::io_service io_service;

	asio::local::stream_protocol::socket s( io_service );

	boost::system::error_code error;
	s.connect( asio::local::stream_protocol::endpoint( x_socket_path ), error );
	if( error )
	{
		std::cerr << error.message() << "\n";
		return error.value();
	}

	xcppb::connection
		<
			asio::local::stream_protocol::socket
		> c( s );

	std::cerr << c;
	
	return 0;
}
catch( std::exception &e )
{
	std::cerr << "Exception: " << e.what() << "\n";
}
