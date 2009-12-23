
#ifndef XCPPB_XCBGEN_ATTRIBUTE_PACKET_STRUCT_COPY_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_PACKET_STRUCT_COPY_HPP

#include <boost/fusion/include/adapt_struct.hpp>

#include <string>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

struct packet_struct_copy
{
	std::string name;
	std::string number;
	std::string ref;
};

}
}
}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::packet_struct_copy,
	( std::string, name  )
	( std::string, number )
	( std::string, ref )
)

#endif
