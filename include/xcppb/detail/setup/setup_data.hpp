
#ifndef XCPPB_SETUP_DETAIL_SETUP_HPP
#define XCPPB_SETUP_DETAIL_SETUP_HPP

#include <boost/cstdint.hpp>

namespace xcppb
{

namespace detail
{

namespace setup
{

struct setup_data
{
	uint32_t      	release_number; /**<  */
	uint32_t      	resource_id_base; /**<  */
	uint32_t      	resource_id_mask; /**<  */
	uint32_t      	motion_buffer_size; /**<  */
	uint16_t      	vendor_len; /**<  */
	uint16_t      	maximum_request_length; /**<  */
	uint8_t       	roots_len; /**<  */
	uint8_t       	pixmap_formats_len; /**<  */
	uint8_t       	image_byte_order; /**<  */
	uint8_t       	bitmap_format_bit_order; /**<  */
	uint8_t       	bitmap_format_scanline_unit; /**<  */
	uint8_t			bitmap_format_scanline_pad; /**<  */
	xcppb::keycode min_keycode; /**<  */
	xcppb::keycode max_keycode; /**<  */
	uint8_t       	pad[4]; /**<  */
};

} // end namespace setup

} // end namespace detail

} // end namespace xcppb

#endif
