
#include <xcppb/atom.hpp>
#include <xcppb/connection.hpp>
#include <xcppb/cookie.hpp>

#include <boost/asio/local/stream_protocol.hpp>

#include <string>
#include <iostream>

namespace asio = boost::asio;

int main()
//try
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

	xcppb::atom a( "NAME497" );
	xcppb::atom b( "NAME498" );
	xcppb::atom c_( "NAME499" );
	xcppb::cookie< xcppb::atom > cookie1( c.request( a ) );
	xcppb::cookie< xcppb::atom > cookie2( c.request( b ) );
	xcppb::cookie< xcppb::atom > cookie3( c.request( c_ ) );

	c.reply( cookie2 );
	c.reply( cookie1 );
	c.reply( cookie3 );

	std::cout << "\n";
	std::cout << "atom: " << a.id() << "\n";
	std::cout << "atom: " << b.id() << "\n";
	std::cout << "atom: " << c_.id() << "\n";
	
	return 0;
}
/*catch( std::exception &e )
{
	std::cerr << "Exception: " << e.what() << "\n";
}*/
