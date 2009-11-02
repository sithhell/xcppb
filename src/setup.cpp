
#include <xcppb/setup.hpp>

namespace xcppb
{

void setup::print( std::ostream &os ) const
{
	os << " Protocol major version: " << +generic_setup.get< data::protocol_major_version >() << "\n"
		<< " Protocol minor version: " << +generic_setup.get< data::protocol_minor_version >() << "\n"
		<< " Release number        : " << +setup_.get< data::release_number >() << "\n"
		<< " resource id base      : " << +setup_.get< data::resource_id_base >() << "\n"
		<< " resource id mask      : " << +setup_.get< data::resource_id_mask >() << "\n"
		<< " Motion buffer size    : " << +setup_.get< data::motion_buffer_size >() << "\n"
		<< " Vendor length         : " << +setup_.get< data::vendor_len >() << "\n"
		<< " Maximum request       : " << +setup_.get< data::maximum_request_length >() << "\n"
		<< " Image byte order      : " << +setup_.get< data::image_byte_order >() << "\n"
		<< " Bitmap bit order      : " << +setup_.get< data::bitmap_format_bit_order >() << "\n"
		<< " Bitmap unit           : " << +setup_.get< data::bitmap_format_scanline_unit >() << "\n"
		<< " Bitmap padding        : " << +setup_.get< data::bitmap_format_scanline_pad >() << "\n"
		<< " Keycode range         : " << +setup_.get< data::min_keycode >() << " " << +setup_.get< data::max_keycode >() << "\n"
		<< " Vendor                : " << vendor << "\n";
		//<< " Number of formats     : " << formats.size() << "\n"
		//<< " Number of screens     : " << screens.size() << "\n";

	os << "\n Formats:\n";

	unsigned i( 0 );
	for( std::vector<format>::const_iterator itr( formats.begin() ); itr != formats.end(); ++itr, ++i )
	{
		os << "\t" << i+1 << ": " << *itr << "\n";
	}
	
	os << "\n Screens:\n";

	i = 0;
	for( std::vector<screen>::const_iterator itr( screens.begin() ); itr != screens.end(); ++itr, ++i )
	{
		os << "\t" << i+1 << ": "<< *itr << "\n";
	}

	//std::copy( formats.begin(), formats.end(), std::ostream_iterator<char>( os, " " ) );
}

std::ostream &operator<< ( std::ostream& os, const xcppb::setup &s )
{
	s.print( os );
	return os;
}

} // end namespace xcppb
