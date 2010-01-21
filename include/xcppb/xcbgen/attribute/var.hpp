
#ifndef XCPPB_XCBGEN_ATTRIBUTE_VAR_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_VAR_HPP

#include <boost/fusion/include/adapt_struct.hpp>

#include <boost/optional.hpp>

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
	boost::optional< std::string > enum_attr;
	boost::optional< std::string > altenum;
	boost::optional< std::string > mask;
};

}
}
}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::var,
	( std::string, name )
	( std::string, type )
	( boost::optional< std::string >, enum_attr )
	( boost::optional< std::string >, altenum )
	( boost::optional< std::string >, mask )
)

#endif
