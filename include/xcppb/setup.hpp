
#ifndef XCPPB_SETUP_OBJECT_HPP
#define XCPPB_SETUP_OBJECT_HPP

#include <iostream>

#include <xcppb/keycode.hpp>
#include <xcppb/format.hpp>
#include <xcppb/screen.hpp>

#include <xcppb/detail/setup/request.hpp>
#include <xcppb/detail/setup/generic.hpp>
#include <xcppb/detail/setup/setup_data.hpp>

#include <boost/system/error_code.hpp>

#include <string>
#include <vector>

namespace xcppb
{

class setup
{
	public:
		template< typename SocketType >
		explicit setup( SocketType &s );

		size_t maximum_request_length() const
		{ return setup_.maximum_request_length; }

		void print( std::ostream &os ) const;

	private:
		detail::setup::generic generic_setup;
		detail::setup::setup_data setup_;

		std::string vendor;
		std::vector<xcppb::format> formats;
		std::vector<xcppb::screen> screens;
};

std::ostream &operator<< ( std::ostream& os, const xcppb::setup &s );

template< typename SocketType >
setup::setup( SocketType &s )
{
	boost::system::error_code error;
	detail::setup::request request( s );

	s.write_some
		(
			request.buffer(),
			error
		);

	if( error )
	{
		throw std::runtime_error( error.message() );
	}

	s.read_some
		(
			boost::asio::buffer( &generic_setup, sizeof( detail::setup::generic ) ),
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
	size_t index( sizeof( detail::setup::generic ) );

	memcpy( &setup_, current_position, sizeof( detail::setup::setup_data ) );

	index += sizeof( detail::setup::setup_data );
	current_position += sizeof( detail::setup::setup_data );

	vendor = std::string( current_position, current_position + setup_.vendor_len );
	index += setup_.vendor_len;
	current_position += setup_.vendor_len;
	current_position += xcppb::format::padding( index );
	index += xcppb::format::padding( index );


	for( unsigned i( 0 ); i < setup_.pixmap_formats_len; ++i )
	{
		formats.push_back( xcppb::format( current_position, index ) );
	}
	current_position += xcppb::screen::padding( index );

	for( size_t i( 0 ); i < setup_.roots_len; ++i )
	{
		screens.push_back( xcppb::screen( current_position, index ) );
	}
}

} // end namespace xcppb

#endif
