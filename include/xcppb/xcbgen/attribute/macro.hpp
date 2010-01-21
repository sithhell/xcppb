
#ifndef XCPPB_XCBGEN_ATTRIBUTE_MACRO_HPP
#define XCPPB_XCBGEN_ATTRIBUTE_MACRO_HPP

#include <xcppb/xcbgen/attribute/request.hpp>
#include <xcppb/xcbgen/attribute/event.hpp>
#include <xcppb/xcbgen/attribute/struct.hpp>
#include <xcppb/xcbgen/attribute/union.hpp>
//#include <xcppb/xcbgen/attribute/xidtype.hpp>
#include <xcppb/xcbgen/attribute/xidunion.hpp>
#include <xcppb/xcbgen/attribute/enum.hpp>
#include <xcppb/xcbgen/attribute/typedef.hpp>
#include <xcppb/xcbgen/attribute/import.hpp>
#include <xcppb/xcbgen/attribute/packet_struct_copy.hpp>
#include <xcppb/xcbgen/attribute/packet_struct.hpp>

#include <boost/variant/recursive_variant.hpp>

#include <string>

namespace xcppb
{
namespace xcbgen
{
namespace attribute
{

typedef boost::variant
<
	  request 
	, event   
	, struct_ 
	, union_  
	, std::string
	, xidunion
	, enum_   
	, typedef_
	, import  
	, packet_struct_copy
	, packet_struct
> macro;

}

}

}

#endif
