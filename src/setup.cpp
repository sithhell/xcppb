
#include <xcppb/setup.hpp>

namespace xcppb
{

void setup::print( std::ostream &os ) const
{
	os << " Protocol major version: " << +generic_setup.protocol_major_version << "\n"
		<< " Protocol minor version: " << +generic_setup.protocol_minor_version << "\n"
		<< " Release number        : " << +setup_.release_number << "\n"
		<< " resource id base      : " << +setup_.resource_id_base << "\n"
		<< " resource id mask      : " << +setup_.resource_id_mask << "\n"
		<< " Motion buffer size    : " << +setup_.motion_buffer_size << "\n"
		<< " Vendor length         : " << +setup_.vendor_len << "\n"
		<< " Maximum request       : " << +setup_.maximum_request_length << "\n"
		<< " Image byte order      : " << +setup_.image_byte_order << "\n"
		<< " Bitmap bit order      : " << +setup_.bitmap_format_bit_order << "\n"
		<< " Bitmap unit           : " << +setup_.bitmap_format_scanline_unit << "\n"
		<< " Bitmap padding        : " << +setup_.bitmap_format_scanline_pad << "\n"
		<< " Keycode range         : " << +setup_.min_keycode << " " << +setup_.max_keycode << "\n"
		<< " Vendor                : " << vendor << "\n"
		<< " Number of formats     : " << formats.size() << "\n"
		<< " Number of screens     : " << screens.size() << "\n";
}

std::ostream &operator<< ( std::ostream& os, const xcppb::setup &s )
{
	s.print( os );
	return os;
}

} // end namespace xcppb
