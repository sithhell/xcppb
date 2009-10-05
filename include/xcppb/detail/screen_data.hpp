
#ifndef XCPPB_DETAIL_SCREEN_DATA
#define XCPPB_DETAIL_SCREEN_DATA

#include <xcppb/window.hpp>
#include <xcppb/colormap.hpp>
#include <xcppb/visualid.hpp>

#include <boost/cstdint.hpp>

namespace xcppb
{

namespace detail
{

struct screen_data
{
	xcppb::window		root; /**<  */
	xcppb::colormap	default_colormap; /**<  */
	uint32_t       	white_pixel; /**<  */
	uint32_t       	black_pixel; /**<  */
	uint32_t       	current_input_masks; /**<  */
	uint16_t      		width_in_pixels; /**<  */
	uint16_t       	height_in_pixels; /**<  */
	uint16_t       	width_in_millimeters; /**<  */
	uint16_t       	height_in_millimeters; /**<  */
	uint16_t       	min_installed_maps; /**<  */
	uint16_t       	max_installed_maps; /**<  */
	xcppb::visualid	root_visual; /**<  */
	uint8_t        	backing_stores; /**<  */
	uint8_t        	save_unders; /**<  */
	uint8_t        	root_depth; /**<  */
	uint8_t        	allowed_depths_len; /**<  */
};

}

}

#endif
