
#ifndef XCPPB_XCBGEN_ATTRIBUTE_XCB_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_XCB_HPP

#include <xcppb/xcbgen/attribute/macro.hpp>

#include <boost/fusion/include/adapt_struct.hpp>

#include <boost/optional.hpp>

#include <string>
#include <vector>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

struct xcb
{
	struct attributes_t
	{
		std::string header;
		boost::optional< std::string > extension_xname;
		boost::optional< std::string > extension_name;
		boost::optional< std::string > extension_multiword;
		boost::optional< std::string > major_version;
		boost::optional< std::string > minor_version;
	} attributes;

	std::vector< macro > macros;
};

}

}

}


BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::xcb::attributes_t,
	( std::string, header              )
	( boost::optional< std::string >, extension_xname     )
	( boost::optional< std::string >, extension_name      )
	( boost::optional< std::string >, extension_multiword )
	( boost::optional< std::string >, major_version       )
	( boost::optional< std::string >, minor_version       )
)


BOOST_FUSION_ADAPT_STRUCT(
	xcppb::xcbgen::attribute::xcb,
	( xcppb::xcbgen::attribute::xcb::attributes_t,     attributes )
	( std::vector< xcppb::xcbgen::attribute::macro >, macros )
)

#endif
