
#include <xcppb/setup/object.hpp>

namespace xcppb
{

namespace setup
{

void object::print( std::ostream &os ) const
{
	os << " Protocol major version: " << +generic_setup.protocol_major_version << "\n"
		<< " Protocol minor version: " << +generic_setup.protocol_minor_version << "\n"
		<< " Release number        : " << +setup.release_number << "\n"
		<< " resource id base      : " << +setup.resource_id_base << "\n"
		<< " resource id mask      : " << +setup.resource_id_mask << "\n"
		<< " Motion buffer size    : " << +setup.motion_buffer_size << "\n"
		<< " Vendor length         : " << +setup.vendor_len << "\n"
		<< " Maximum request       : " << +setup.maximum_request_length << "\n"
		<< " Image byte order      : " << +setup.image_byte_order << "\n"
		<< " Bitmap bit order      : " << +setup.bitmap_format_bit_order << "\n"
		<< " Bitmap unit           : " << +setup.bitmap_format_scanline_unit << "\n"
		<< " Bitmap padding        : " << +setup.bitmap_format_scanline_pad << "\n"
		<< " Keycode range         : " << +setup.min_keycode << " " << +setup.max_keycode << "\n"
		<< " Vendor                : " << vendor << "\n"
		<< " Number of formats     : " << formats.size() << "\n"
		<< " Number of screens     : " << screens.size() << "\n";
}

std::ostream &operator<< ( std::ostream& os, const xcppb::setup::object &s )
{
	s.print( os );
	return os;
}

} // end namespace setup

} // end namespace xcppb
