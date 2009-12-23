
#ifndef XCPPB_XCBGEN_ATTRIBUTE_EXPRFIELD_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_EXPRFIELD_HPP

#include <xcppb/xcbgen/attribute/var.hpp>
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

struct exprfield
{
	var attributes;
	expression expr;
};

}

}

}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::exprfield,
	( xcppb::xcbgen::attribute::var       , attributes )
	( xcppb::xcbgen::attribute::expression, expr )
)

#endif
