
#ifndef XCPPB_XCBGEN_ATTRIBUTE_IMPORT_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_IMPORT_HPP

#include <boost/fusion/include/adapt_struct.hpp>

#include <string>


namespace xcppb
{

namespace xcbgen
{

namespace attribute
{

struct import
{
	std::string value;
};

}

}

}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::import,
	( std::string, value )
)

#endif
