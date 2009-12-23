
#ifndef XCPPB_XCBGEN_ATTRIBUTE_VALUEPARAM_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_VALUEPARAM_HPP

#include <boost/fusion/include/adapt_struct.hpp>

#include <string>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

struct valueparam
{
	std::string value_mask_type;
	std::string value_mask_name;
	std::string value_list_name;
};

}
}
}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::valueparam,
	( std::string, value_mask_type )
	( std::string, value_mask_name )
	( std::string, value_list_name )
)

#endif
