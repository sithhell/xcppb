
#ifndef XCPPB_SETUP_OBJECT_HPP
#define XCPPB_SETUP_OBJECT_HPP

#include <iostream>

#include <xcppb/keycode.hpp>
#include <xcppb/format.hpp>
#include <xcppb/screen.hpp>

#include <xcppb/setup/detail/request.hpp>
#include <xcppb/setup/detail/generic.hpp>
#include <xcppb/setup/detail/setup_data.hpp>

#include <boost/system/error_code.hpp>

#include <string>
#include <vector>

namespace xcppb
{

namespace setup
{

class object
{
	public:
		template< typename SocketType >
		inline explicit object( SocketType &s );

		void print( std::ostream &os ) const;

	private:
		detail::generic generic_setup;
		detail::setup_data setup;

		std::string vendor;
		std::vector<xcppb::format> formats;
		std::vector<xcppb::screen> screens;
};

std::ostream &operator<< ( std::ostream& os, const xcppb::setup::object &s );

template< typename SocketType >
object::object( SocketType &s )
{
	boost::system::error_code error;
	detail::request request( s );

	s.write_some
		(
			request.buffer(),
			error
		);

	if( error )
	{
		throw std::runtime_error( error.message() );
	}

	detail::generic generic_setup;
	s.read_some
		(
			boost::asio::buffer( &generic_setup, sizeof( detail::generic ) ),
			error
		);
	
	if( error )
	{
		throw std::runtime_error( error.message() );
	}

	std::vector<char> setup_data_buffer( generic_setup.length * 4 );
	s.read_some
		(
			boost::asio::buffer( setup_data_buffer ),
			error
		);
	
	if( error )
	{
		throw std::runtime_error( error.message() );
	}

	// check if setup was retrieved successfully
	switch( generic_setup.status )
	{
		case 0: // failed
			{
				throw std::runtime_error( std::string( setup_data_buffer.begin(), setup_data_buffer.end() ) );
			}
			break;
		case 2: // authenticate
			{
				throw std::runtime_error( std::string( setup_data_buffer.begin(), setup_data_buffer.end() ) );
			}
		default:
			break;
	}

	// construct setup data ...
	char *current_position( &setup_data_buffer[0] );
	size_t index( sizeof( detail::generic ) );

	memcpy( &setup, current_position, sizeof( detail::setup_data ) );

	index += sizeof( detail::setup_data );
	current_position += sizeof( detail::setup_data );

	vendor = std::string( current_position, current_position + setup.vendor_len );
	index += setup.vendor_len;
	current_position += setup.vendor_len;
	current_position += xcppb::format::padding( index );
	index += xcppb::format::padding( index );


	for( unsigned i( 0 ); i < setup.pixmap_formats_len; ++i )
	{
		formats.push_back( xcppb::format( current_position, index ) );
	}
	current_position += xcppb::screen::padding( index );

	for( size_t i( 0 ); i < setup.roots_len; ++i )
	{
		screens.push_back( xcppb::screen( current_position, index ) );
	}
}

} // end namespace setup

} // end namespace xcppb

#endif
