
#ifndef XCPPB_XCBGEN_ATTRIBUTE_REPLY_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_REPLY_HPP

#include <xcppb/xcbgen/attribute/fields.hpp>
#include <xcppb/xcbgen/attribute/valueparam.hpp>

#include <boost/variant/recursive_variant.hpp>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

typedef std::vector
<
	boost::variant
	<
		  fields
		, valueparam
	>
> reply;

}

}

}

#endif
