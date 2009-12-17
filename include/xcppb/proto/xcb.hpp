
#ifndef XCPPB_PROTO_XCB_HPP
#define XCPPB_PROTO_XCB_HPP

#include <string>
#include <vector>

#include <boost/array.hpp>
#include <boost/fusion/include/array.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace xcppb
{

namespace proto
{

struct xcb
{
	typedef boost::array<std::string, 6> xcb_attributes;
	xcb_attributes attributes;

	std::string const &header()
	{
		return attributes[0];
	}
	
	std::string const &extension_xname()
	{
		return attributes[1];
	}
	
	std::string const &extension_name()
	{
		return attributes[2];
	}
	
	std::string const &extension_multiword()
	{
		return attributes[3];
	}
	
	std::string const &major_version()
	{
		return attributes[4];
	}
	
	std::string const &minor_version()
	{
		return attributes[5];
	}
	
	//std::vector<macro> macros;
	std::vector<std::string> macros;
};

}

}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::proto::xcb,
	(xcppb::proto::xcb::xcb_attributes, attributes)
	//(std::vector<xcppb::proto::macro>, macros )
	(std::vector<std::string>, macros )
)

#endif
