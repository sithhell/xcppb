
#ifndef XCPPB_XCBGEN_ATTRIBUTE_PACKET_STRUCT_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_PACKET_STRUCT_HPP

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

struct packet_struct
{
	std::string name;
	std::string number;
	std::vector< fields > fields_;
};

}

}

}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::packet_struct,
	( std::string, name )
	( std::string, number )
	( std::vector< xcppb::xcbgen::attribute::fields >, fields_ )
)

#endif
