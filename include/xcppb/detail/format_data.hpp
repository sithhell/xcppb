
#ifndef XCPPB_DETAIL_FORMAT_DATA_HPP
#define XCPPB_DETAIL_FORMAT_DATA_HPP

#include <boost/cstdint.hpp>

namespace xcppb
{

namespace detail
{

struct format_data
{
	uint8_t depth; /**<  */
	uint8_t bits_per_pixel; /**<  */
	uint8_t scanline_pad; /**<  */
	uint8_t pad0[5]; /**<  */
};

}

}

#endif
