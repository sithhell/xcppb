
#ifndef XCPPB_XCBGEN_ATTRIBUTE_ENUM_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_ENUM_HPP

#include <boost/fusion/include/adapt_struct.hpp>

#include <string>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

struct enum_
{
	std::string name;
	std::vector< item > items;
};

}

}

}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::enum_,
	( std::string, name )
	( std::vector< xcppb::xcbgen::attribute::item >, items )
)

#endif
