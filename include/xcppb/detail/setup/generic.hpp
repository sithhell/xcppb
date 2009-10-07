
#ifndef XCPPB_SETUP_DETAIL_GENERIC_HPP
#define XCPPB_SETUP_DETAIL_GENERIC_HPP

#include <boost/cstdint.hpp>

namespace xcppb
{

namespace detail
{

namespace setup
{

struct generic
{
	uint8_t 	status;
	uint8_t	pad0;
	uint16_t protocol_major_version;
	uint16_t protocol_minor_version;
	uint16_t	length;
};

} // end namespace setup

} // end namespace detail

} // end namespace xcppb

#endif
