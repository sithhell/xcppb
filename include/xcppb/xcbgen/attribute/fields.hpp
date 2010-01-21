
#ifndef XCPPB_XCBGEN_ATTRIBUTE_FIELDS_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_FIELDS_HPP

#include <xcppb/xcbgen/attribute/var.hpp>
#include <xcppb/xcbgen/attribute/list.hpp>

#include <boost/variant/recursive_variant.hpp>


namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

typedef boost::variant
<
	boost::uint32_t,
	var,
	list
> fields;

}

}

}

#endif
