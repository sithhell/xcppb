
#ifndef XCPPB_AUTH_GET_ADDR_HPP
#define XCPPB_AUTH_GET_ADDR_HPP

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/local/stream_protocol.hpp>

#include <string>


namespace xcppb
{

namespace auth
{

namespace detail
{

std::string get_addr( const boost::asio::ip::tcp::endpoint &endpoint );

std::string get_addr( const boost::asio::local::stream_protocol::endpoint &endpoint );

} // end namespace detail
	
} // end namespace auth

} // end namespace xcppb

#endif
