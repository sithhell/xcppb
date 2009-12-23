
#ifndef XCPPB_XCBGEN_ATTRIBUTE_ITEM_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_ITEM_HPP

#include <xcppb/xcbgen/attribute/expression.hpp>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional.hpp>

#include <string>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

struct item
{
	std::string name;
	boost::optional< expression > expr;
};

}

}

}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::item,
	( std::string, name )
	( boost::optional< xcppb::xcbgen::attribute::expression >, expr )
)

#endif
