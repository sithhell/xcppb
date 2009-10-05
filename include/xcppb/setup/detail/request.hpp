
#ifndef XCPPB_SETUP_DETAIL_REQUEST_HPP
#define XCPPB_SETUP_DETAIL_REQUEST_HPP

#include <xcppb/auth/info.hpp>
#include <xcppb/padding.hpp>

#include <boost/asio/buffer.hpp>

#include <arpa/inet.h>

// TODO: express this with traits ...
#define XCB_PAD(i) (-(i) & 3)

namespace xcppb
{

namespace setup
{

namespace detail
{

class request
{
	public:
		template< typename SocketType >
		request( SocketType &s )
			: info( s )
		{}

		std::vector< boost::asio::const_buffer > buffer()
		{
			std::vector< boost::asio::const_buffer > buf( 6 );
			static char pad[] = {0, 0, 0};

			if( htonl( ENDIAN ) == ENDIAN )
			{
				protocol.byte_order = 0x42;
			}
			else
			{
				protocol.byte_order = 0x6c;
			}
			//pod[0].byte_order = detail::endianess< 0x42, 0x6c>::value;
			protocol.protocol_major_version = X_PROTOCOL;
			protocol.protocol_minor_version = X_PROTOCOL_REVISION;
			protocol.authorization_protocol_name_len = info.name().length();
			protocol.authorization_protocol_data_len = info.data().size();

			buf.push_back( boost::asio::buffer( &protocol, sizeof( request_protocol ) ) );
			buf.push_back( boost::asio::buffer( &pad, xcppb::padding<char[3]>( sizeof( request_protocol ) ) ) );
			buf.push_back( boost::asio::buffer( auth_info().name() ) );
			buf.push_back( boost::asio::buffer( &pad, xcppb::padding<char[3]>( auth_info().name().length() ) ) );
			buf.push_back( boost::asio::buffer( auth_info().data() ) );
			buf.push_back( boost::asio::buffer( &pad, xcppb::padding<char[3]>( auth_info().data().size() ) ) );

			return buf;
		}

		
		const xcppb::auth::info &auth_info() const
		{
			return info;
		}

	private:
		xcppb::auth::info info;

		struct request_protocol
		{
			uint8_t  byte_order;
			uint8_t  pad0;
			uint16_t protocol_major_version;
			uint16_t protocol_minor_version;
			uint16_t authorization_protocol_name_len;
			uint16_t authorization_protocol_data_len;
			uint8_t  pad1[2];
		} protocol;

		enum { ENDIAN = 0x01020304 };
		enum { X_PROTOCOL = 11 };
		enum { X_PROTOCOL_REVISION = 0 };
};

} // end namespace detail

} // end namespace setup

} // end namespace xcppb
#endif
