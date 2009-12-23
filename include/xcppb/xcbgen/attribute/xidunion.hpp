
#ifndef XCPPB_XCBGEN_ATTRIBUTE_XIDUNION_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_XIDUNION_HPP

#include <boost/fusion/include/adapt_struct.hpp>

#include <string>
#include <vector>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

struct xidunion
{
	std::string              name;
	std::vector<std::string> types;
};

}
}
}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::xidunion,
	( std::string               , name  )
	( std::vector< std::string >, types )
)

#endif
