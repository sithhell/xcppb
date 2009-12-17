
#ifndef XCPPB_PROTO_VAR_HPP
#define XCPPB_PROTO_VAR_HPP

#include <string>

#include <boost/array.hpp>
#include <boost/fusion/include/array.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace xcppb
{

namespace proto
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

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::proto::var,
	(std::string, name )
	(std::string, type )
	(std::string, enum_attr )
	(std::string, altenum )
	(std::string, mask )
)

#endif
