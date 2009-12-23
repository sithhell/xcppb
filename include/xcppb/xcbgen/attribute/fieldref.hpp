
#ifndef XCPPB_XCBGEN_ATTRIBUTE_FIELDREF_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_FIELDREF_HPP

#include <boost/fusion/include/adapt_struct.hpp>

#include <string>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

struct fieldref
{
	std::string ref;
};

}

}

}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::fieldref,
	( std::string, ref )
)

#endif
