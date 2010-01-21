
#ifndef XCPPB_XCBGEN_ATTRIBUTE_UNION_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_UNION_HPP

#include <xcppb/xcbgen/attribute/fields.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

struct union_
{
	std::string name;
	std::vector< fields > fields_;
};

}

}

}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::union_,
	( std::string, name )
	( std::vector< xcppb::xcbgen::attribute::fields >, fields_ )
)

#endif
