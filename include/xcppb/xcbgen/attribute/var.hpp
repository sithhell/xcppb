
#ifndef XCPPB_XCBGEN_ATTRIBUTE_VAR_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_VAR_HPP

#include <boost/fusion/include/adapt_struct.hpp>

#include <string>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

struct var
{
	std::string name;
	std::string type;
	std::string enum_attr;
	std::string altenum;
	std::string mask;
};

}
}
}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::var,
	( std::string, name )
	( std::string, type )
	( std::string, enum_attr )
	( std::string, altenum )
	( std::string, mask )
)

#endif
