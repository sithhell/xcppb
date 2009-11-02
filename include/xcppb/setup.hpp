
#ifndef XCPPB_SETUP_OBJECT_HPP
#define XCPPB_SETUP_OBJECT_HPP

#include <iostream>

#include <xcppb/data/object.hpp>
#include <xcppb/data/pad.hpp>

#include <xcppb/keycode.hpp>
#include <xcppb/format.hpp>
#include <xcppb/screen.hpp>

//#include <xcppb/detail/setup/request.hpp>
#include <xcppb/auth_info.hpp>
#include <xcppb/padding.hpp>

#include <boost/cstdint.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/system/error_code.hpp>

#include <string>
#include <vector>

namespace xcppb
{

class setup
{
	// encapsulate the data type definitions
	struct data
	{
		MAKE_ELEMENT( byte_order                     , uint8_t );
		MAKE_ELEMENT( protocol_major_version         , uint16_t );
		MAKE_ELEMENT( protocol_minor_version         , uint16_t );
		MAKE_ELEMENT( authorization_protocol_name_len, uint16_t );
		MAKE_ELEMENT( authorization_protocol_data_len, uint16_t );

		typedef xcppb::data::object
		<
			boost::mpl::vector
			<
				byte_order,
				xcppb::data::pad< uint8_t, 1 >,
				protocol_major_version,
				protocol_minor_version,
				authorization_protocol_name_len,
				authorization_protocol_data_len,
				xcppb::data::pad< uint8_t, 2 >
			>
		> request;

		MAKE_ELEMENT( status                , uint8_t  );
		MAKE_ELEMENT( length                , uint16_t );
		typedef xcppb::data::object
		<
			boost::mpl::vector
			<
				status,
				xcppb::data::pad< uint8_t, 1 >,
				protocol_major_version,
				protocol_minor_version,
				length
			>
		> generic;
		
		MAKE_ELEMENT( release_number					, uint32_t );
		MAKE_ELEMENT( resource_id_base				, uint32_t );
		MAKE_ELEMENT( resource_id_mask				, uint32_t );
		MAKE_ELEMENT( motion_buffer_size				, uint32_t );
		MAKE_ELEMENT( vendor_len						, uint16_t );
		MAKE_ELEMENT( maximum_request_length		, uint16_t );
		MAKE_ELEMENT( roots_len							, uint8_t );
		MAKE_ELEMENT( pixmap_formats_len				, uint8_t );
		MAKE_ELEMENT( image_byte_order				, uint8_t );
		MAKE_ELEMENT( bitmap_format_bit_order		, uint8_t );
		MAKE_ELEMENT( bitmap_format_scanline_unit	, uint8_t );
		MAKE_ELEMENT( bitmap_format_scanline_pad	, uint8_t );
		MAKE_ELEMENT( min_keycode						, xcppb::keycode );
		MAKE_ELEMENT( max_keycode						, xcppb::keycode );
		typedef xcppb::data::object
		<
			boost::mpl::vector
			<
				release_number,
				resource_id_base,
				resource_id_mask,
				motion_buffer_size,
				vendor_len,
				maximum_request_length,
				roots_len,
				pixmap_formats_len,
				image_byte_order,
				bitmap_format_bit_order,
				bitmap_format_scanline_unit,
				bitmap_format_scanline_pad,
				min_keycode,
				max_keycode,
				xcppb::data::pad<uint8_t, 4>
			>
		> setup;
	};

	public:
		template< typename SocketType >
		explicit setup( SocketType &s );

		size_t maximum_request_length() const
		{ return setup_.get< data::maximum_request_length >(); }

		uint32_t resource_id_base() const
		{
			return setup_.get< data::resource_id_base >();
		}
		
		uint32_t resource_id_mask() const
		{
			return setup_.get< data::resource_id_mask >();
		}

		void print( std::ostream &os ) const;

	private:

		template< typename SocketType >
		void send_request( SocketType& s );

		data::generic generic_setup;
		data::setup   setup_;

		std::string vendor;
		std::vector<xcppb::format> formats;
		std::vector<xcppb::screen> screens;
};

std::ostream &operator<< ( std::ostream& os, const xcppb::setup &s );

template< typename SocketType >
setup::setup( SocketType &s )
{
	boost::system::error_code error;

	send_request( s );

	s.read_some
		(
			boost::asio::buffer( generic_setup.begin(), generic_setup.size() ),
			error
		);
	
	if( error )
	{
		throw std::runtime_error( error.message() );
	}

	std::vector<char> setup_data_buffer( generic_setup.get< data::length >() * 4 );
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
	switch( generic_setup.get< data::status >() )
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
	size_t index( generic_setup.size() );

	std::copy( current_position, current_position + setup_.size(), setup_.begin() );

	index += setup_.size();
	current_position += setup_.size();

	vendor = std::string( current_position, current_position + setup_.get< data::vendor_len >() );
	index += setup_.get< data::vendor_len >();
	current_position += setup_.get< data::vendor_len >();

	format::data::format format_data;
	
	current_position += xcppb::padding< char[ format::data::format::size_::value ] >( index );
	
	index += xcppb::padding< char[ format::data::format::size_::value ] >( index );

	for( unsigned i( 0 ); i < setup_.get< data::pixmap_formats_len >(); ++i )
	{
		std::copy( current_position, current_position + format_data.size(), format_data.begin() );

		formats.push_back( xcppb::format( format_data ) );

		current_position += format_data.size();
		index += format_data.size();
	}

	screen::data::screen screen_data;
	current_position += xcppb::padding< char[screen::data::screen::size_::value] >( index );
	index += xcppb::padding< char[screen::data::screen::size_::value] >( index );

	for( size_t i( 0 ); i < setup_.get< data::roots_len >(); ++i )
	{
		std::copy( current_position, current_position + screen_data.size(), screen_data.begin() );
		screens.push_back( xcppb::screen( screen_data ) );

		current_position += screen_data.size();
		index += screen_data.size();
	}
}

template< typename SocketType >
void setup::send_request( SocketType &s )
{
	const unsigned ENDIAN = 0x01020304;
	const unsigned X_PROTOCOL = 11;
	const unsigned X_PROTOCOL_REVISION = 0;
	static char pad[] = {0, 0, 0};

	boost::system::error_code error;
	data::request request;
	std::vector< boost::asio::const_buffer > buf( 6 );
	auth_info info( s );
	
	if( htonl( ENDIAN ) == ENDIAN )
	{
		request.set< data::byte_order >( 0x42 );
	}
	else
	{
		request.set< data::byte_order >( 0x6c );
	}
	request.set< data::protocol_major_version >( X_PROTOCOL );
	request.set< data::protocol_minor_version >( X_PROTOCOL_REVISION );
	request.set< data::authorization_protocol_name_len >( static_cast<uint16_t>( info.name().length() ) );
	request.set< data::authorization_protocol_data_len >( static_cast<uint16_t>( info.data().size() ) );

	buf.push_back( boost::asio::buffer( request.begin(), request.size() ) );
	buf.push_back( boost::asio::buffer( &pad, xcppb::padding<char[3]>( request.size() ) ) );
	buf.push_back( boost::asio::buffer( info.name() ) );
	buf.push_back( boost::asio::buffer( &pad, xcppb::padding<char[3]>( info.name().length() ) ) );
	buf.push_back( boost::asio::buffer( info.data() ) );
	buf.push_back( boost::asio::buffer( &pad, xcppb::padding<char[3]>( info.data().size() ) ) );
	s.write_some
	(
		buf,
		error
	);
	
	if( error )
	{
		throw std::runtime_error( error.message() );
	}
}

} // end namespace xcppb

#endif
