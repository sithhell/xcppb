
#ifndef XCPPB_XCBGEN_ATTRIBUTE_REQUEST_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_REQUEST_HPP

#include <xcppb/xcbgen/attribute/fields.hpp>
#include <xcppb/xcbgen/attribute/valueparam.hpp>

#include <boost/variant/recursive_variant.hpp>
#include <boost/optional.hpp>

#include <string>
#include <vector>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

struct request
{
	struct attributes_t
	{
		std::string name;
		std::string opcode;
		boost::optional< std::string > combine_adjacent;
	} attributes;

	typedef boost::variant
	<
		  fields
		, exprfield
		, valueparam
	> element;

	std::vector< element > elements;

	boost::optional< reply > reply_;
};

}

}

}


BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::request::attributes_t,
	( std::string, name )
	( std::string, opcode )
	( boost::optional< std::string >, combine_adjacent )
)


BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::request,
	( xcppb::xcbgen::attribute::request::attributes_t,     attributes )
	( std::vector< xcppb::xcbgen::attribute::request::element >, elements )
	( boost::optional< xcppb::xcbgen::attribute::reply >, reply_ )
)

#endif
