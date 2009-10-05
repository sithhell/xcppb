
#include <xcppb/auth/detail/get_addr.hpp>

#include <boost/asio/ip/host_name.hpp>
#include <boost/cstdint.hpp>

namespace xcppb
{

namespace auth
{

namespace detail
{

std::string get_addr( const boost::asio::ip::tcp::endpoint &endpoint )
{
	return endpoint.address().to_string();
}

std::string get_addr( const boost::asio::local::stream_protocol::endpoint &/*endpoint*/ )
{
	boost::system::error_code error;
	std::string ret( boost::asio::ip::host_name( error ) );
	if( error )
	{
		throw std::runtime_error( error.message() );
	}

	return ret;
}

} // end namespace detail
	
} // end namespace auth

} // end namespace xcppb
