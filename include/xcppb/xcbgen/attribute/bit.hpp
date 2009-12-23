
#ifndef XCPPB_XCBGEN_ATTRIBUTE_BIT_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_BIT_HPP

#include <boost/fusion/include/adapt_struct.hpp>

#include <string>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

struct bit
{
	int value;
};

}

}

}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::bit,
	( int, value )
)

#endif
