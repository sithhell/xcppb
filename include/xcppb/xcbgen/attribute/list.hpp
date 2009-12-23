
#ifndef XCPPB_XCBGEN_ATTRIBUTE_LIST_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_LIST_HPP

#include <xcppb/xcbgen/attribute/expression.hpp>
#include <xcppb/xcbgen/attribute/var.hpp>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional.hpp>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

struct list
{
	var attributes;
	boost::optional< expression > expr;
};

}

}

}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::list,
	( xcppb::xcbgen::attribute::var, attributes )
	( boost::optional< xcppb::xcbgen::attribute::expression >, expr )
)

#endif
