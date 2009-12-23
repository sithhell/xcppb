
#ifndef XCPPB_XCBGEN_ATTRIBUTE_EXPRESSION_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_EXPRESSION_HPP

#include <xcppb/xcbgen/attribute/fieldref.hpp>
#include <xcppb/xcbgen/attribute/value.hpp>
#include <xcppb/xcbgen/attribute/bit.hpp>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant.hpp>

#include <string>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

struct op;

typedef boost::variant
<
	boost::recursive_wrapper< op >,
	fieldref,
	value,
	bit
> expression;
	
struct op
{
	enum type
	{
		plus,
		minus,
		mult,
		div,
		and_,
		right_shift,
		undefined
	};

	type operation;

	expression left;
	expression right;
};


}
}
}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::op,
	( xcppb::xcbgen::attribute::op::type, operation )
	( xcppb::xcbgen::attribute::expression, left )
	( xcppb::xcbgen::attribute::expression, right )
)

#endif
