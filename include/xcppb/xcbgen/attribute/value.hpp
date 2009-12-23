
#ifndef XCPPB_XCBGEN_ATTRIBUTE_VALUE_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_VALUE_HPP

#include <boost/fusion/include/adapt_struct.hpp>

#include <string>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

struct value
{
	int value;
};

}

}

}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::value,
	( int, value )
)

#endif
