
#ifndef XCPPB_XCBGEN_ATTRIBUTE_EVENT_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_EVENT_HPP

#include <xcppb/xcbgen/attribute/fields.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <vector>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

struct event
{
	struct attributes
	{
		std::string name;
		std::string number;
		std::string no_sequence_number;
	};
	attributes event_attributes;
	/*std::string name;
	std::string number;
	std::string no_sequence_number;*/
	std::vector< fields > fields_;
};

}

}

}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::event::attributes,
	//xcppb::xcbgen::attribute::event,
	( std::string, name )
	( std::string, number )
	( std::string, no_sequence_number )
	//( std::vector< xcppb::xcbgen::attribute::fields >, fields_ )
)


BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::event,
	( xcppb::xcbgen::attribute::event::attributes,     event_attributes )
	( std::vector< xcppb::xcbgen::attribute::fields >, fields_ )
)

#endif
