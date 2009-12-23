
#ifndef XCPPB_XCBGEN_ATTRIBUTE_TYPEDEF_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_TYPEDEF_HPP

#include <boost/fusion/include/adapt_struct.hpp>

#include <string>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

struct typedef_
{
	std::string oldname;
	std::string newname;
};

}
}
}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::typedef_,
	( std::string, newname )
	( std::string, oldname )
)

#endif
