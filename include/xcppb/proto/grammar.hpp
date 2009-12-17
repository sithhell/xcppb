
#ifndef XCPPB_PROTO_PARSER_HPP
#define XCPPB_PROTO_PARSER_HPP

#include <xcppb/proto/tokens.hpp>

#include <xcppb/proto/xcb.hpp>
#include <xcppb/proto/var.hpp>

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/make_map.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace spirit = boost::spirit;
namespace phoenix = boost::phoenix;
namespace ascii = boost::spirit::ascii;
namespace qi = boost::spirit::qi;

/*namespace xcppb
{

namespace proto
{

struct request
{
};

struct typedef_
{
	typedef boost::array<std::string, 2> types_type;

	types_type types;

	std::string const &oldname() const
	{
		return types[0];
	}

	std::string const &newname() const
	{
		return types[1];
	}
};

typedef boost::variant
			<
				typedef_,
				std::string
			> macro;

}

}

BOOST_FUSION_ADAPT_STRUCT(
	xcppb::proto::typedef_,
	(xcppb::proto::typedef_::types_type, types)
)*/

namespace xcppb
{

namespace proto
{

template< typename Iterator >
struct grammar
	: qi::grammar
		<
			  Iterator
			, xcppb::proto::xcb()
		>
{
	template< typename TokenDef >
	grammar( TokenDef const & tok )
	:	grammar::base_type( xcb, "xcb" )
	{
		attribute.name( "attribute" );
		attribute
			%= qi::lazy( qi::_r1 )
			> '='
			> tok.attribute_begin
			> tok.attribute
			> tok.attribute_end
			;

		xcb.name( "xcb" );
		xcb
			%= -( tok.prolog )
			> tok.xcb_begin
			> 
			(
				  attribute( phoenix::ref( tok.header              ) )  
				^ attribute( phoenix::ref( tok.extension_xname     ) )
				^ attribute( phoenix::ref( tok.extension_name      ) )
				^ attribute( phoenix::ref( tok.extension_multiword ) )
				^ attribute( phoenix::ref( tok.major_version       ) )
				^ attribute( phoenix::ref( tok.minor_version       ) )
			)
			> tok.close_tag
			> *macro
			> tok.xcb_end
			;

		pad.name( "pad" );
		pad
			%= tok.pad
			> attribute( phoenix::ref( tok.bytes ) )
			> tok.close_tag
			;

		var.name( "var" );
		var
			%= 
			( attribute( phoenix::ref( tok.name      ) )
			  ^
			  ( attribute( phoenix::ref( tok.type      ) )
				 ^
				 ( attribute( phoenix::ref( tok.enum_attr ) )
					^
					( attribute( phoenix::ref( tok.altenum   ) )
					  ^ attribute( phoenix::ref( tok.mask      ) )
					)
				 )
			  )
			)//[ qi::_val = qi::_1 ]
			;

		field.name( "field" );
		field
			= tok.field
			> qi::omit[ var ]
			> tok.close_tag;
			;

		list.name( "list" );
		list
			= tok.list_begin
			> qi::omit[ var ]
			> tok.close_tag
			> -( expression > tok.list_end )
			;

		op.name( "op" );
		op
			= tok.op_begin
			> attribute( phoenix::ref( tok.op_attr ) )
			> tok.close_tag
			> expression > expression
			> tok.op_end
			;

		fieldref.name( "fieldref" );
		fieldref
			= tok.fieldref_begin
			> tok.element
			> qi::lit( '<' ) > tok.fieldref_end
			;

		value.name( "value" );
		value
			= tok.value_begin
			> *tok.element
			> qi::lit( '<' ) > tok.value_end
			;

		bit.name( "bit" );
		bit
			= tok.bit_begin
			> tok.element
			> qi::lit( '<' ) > tok.bit_end
			;

		expression.name( "expression" );
		expression
			= op
			| fieldref
			| value
			| bit
			;

		exprfield.name( "exprfield" );
		exprfield
			= tok.exprfield_begin
			> qi::omit[ var ]
			> tok.close_tag
			> expression
			> tok.exprfield_end
			;

		valueparam.name( "valueparam" );
		valueparam
			=  tok.valueparam
			> attribute( phoenix::ref( tok.value_mask_type ) )
			> attribute( phoenix::ref( tok.value_mask_name ) )
			> attribute( phoenix::ref( tok.value_list_name ) )
			> tok.close_tag
			;

		fields.name( "fields" );
		fields
			= pad
			| field
			| list
			;

		struct_.name( "struct" );
		struct_
			=  attribute( phoenix::ref( tok.name ) )
			> tok.close_tag
			> +fields
			;

		packet_struct.name( "packet-struct" );
		packet_struct
			= attribute( phoenix::ref( tok.name   ) )
			> attribute( phoenix::ref( tok.number ) )
			> tok.close_tag
			> *fields
			;

		packet_struct_copy.name( "packet-struct-copy" );
		packet_struct_copy
			=
			(
				  attribute( phoenix::ref( tok.name   ) )
				^ attribute( phoenix::ref( tok.number ) )
				^ attribute( phoenix::ref( tok.ref    ) )
			)
			> tok.close_tag
			;

		reply.name( "reply" );
		reply
			= tok.reply_begin
			> +(
					  fields
					| valueparam
				)
			> tok.reply_end
			;

		request.name( "request" );
		request
			= tok.request_begin
			> 
			(
				  attribute( phoenix::ref( tok.name             ) )
				^ attribute( phoenix::ref( tok.opcode           ) )
				^ attribute( phoenix::ref( tok.combine_adjacent ) )
			)
			> tok.close_tag
			> *(
					  fields
					| exprfield
					| valueparam
				)
			> -( reply )
			> -( tok.request_end )
			;

		event.name( "event" );
		event
			= tok.event_begin
			> 
			(
				  attribute( phoenix::ref( tok.name               ) )
				^ attribute( phoenix::ref( tok.number             ) )
				^ attribute( phoenix::ref( tok.no_sequence_number ) )
			)
			> tok.close_tag
			> +fields
			> tok.event_end
			;

		xidtype.name( "xidtype" );
		xidtype
			= tok.xidtype
			> attribute( phoenix::ref( tok.name ) )
			> tok.close_tag
			;

		xidunion.name( "xidunion" );
		xidunion
			= tok.xidunion_begin
			> attribute( phoenix::ref( tok.name ) )
			> tok.close_tag
			> 
			+(
				  tok.type_begin
				> tok.element
				> qi::lit( '<' ) > tok.type_end
			)
			> tok.xidunion_end
			;

		item.name( "item" );
		item
			= tok.item_begin
			> attribute( phoenix::ref( tok.name ) )
			> tok.close_tag
			> 
			-(
				  expression
				> tok.item_end
			)
			;

		enum_.name( "enum" );
		enum_
			= tok.enum_begin
			> attribute( phoenix::ref( tok.name ) )
			> tok.close_tag
			> *item
			> tok.enum_end
			;

		typedef_.name( "typedef" );
		typedef_
			%= tok.typedef_
			> 
			(
				  attribute( phoenix::ref( tok.oldname ) )
				^ attribute( phoenix::ref( tok.newname ) )
			)
			> tok.close_tag
			;

		import.name( "import" );
		import
			= tok.import_begin
			> tok.element
			> '<'
			> tok.import_end
			;

		macro.name( "macro" );
		macro
			= request[ qi::_val = "macro" ]
			| event[ qi::_val = "macro" ]
			| 
			(
				  tok.eventcopy
				> packet_struct_copy
			)[ qi::_val = "macro" ]
			|
			(
				  tok.error_begin
				> packet_struct
				> -( tok.error_end ) )[ qi::_val = "macro" ]
			|
			(
				  tok.errorcopy
				> packet_struct_copy
			)[ qi::_val = "macro" ]
			|
			(
				  tok.struct_begin
				> struct_
				> tok.struct_end
			)[ qi::_val = "macro" ]
			|
			(
				  tok.union_begin
				> struct_
				> tok.union_end
			)[ qi::_val = "macro" ]
			|  xidtype[ qi::_val = "macro" ]
			|  xidunion[ qi::_val = "macro" ]
			|  enum_[ qi::_val = "macro" ]
			|  typedef_[ qi::_val = "macro" ]
			|  import[ qi::_val = "macro" ]
			;

		qi::on_error<qi::fail>
		(
			xcb,
			// TODO: display token values in error message
			std::cout
				<< phoenix::val("Error! Expecting ")
				<< qi::_4                               // what failed?
				<< phoenix::val(" here: \"")
				<< phoenix::construct<std::string>( qi::_3, qi::_2)   // iterators to error-pos, end
				<< phoenix::val("\"")
				<< std::endl
		);
	}

	qi::rule
	<
		  Iterator
		, std::string( lex::token_def<lex::omit> )
	> attribute;

	qi::rule
	<
		  Iterator
		, xcppb::proto::xcb()
	> xcb;

	qi::rule
	<
		  Iterator
		, std::string()
	> pad;
	
	qi::rule
	<
		  Iterator
		, xcppb::proto::var()
	> var;
	
	qi::rule
	<
		Iterator
	> field;
	
	qi::rule
	<
		Iterator
	> list;

	qi::rule
	<
		Iterator
	> expression;

	qi::rule
	<
		Iterator
	> op;

	qi::rule
	<
		Iterator
	> fieldref;

	qi::rule
	<
		Iterator
	> value;

	qi::rule
	<
		Iterator
	> bit;

	qi::rule
	<
		Iterator
	> exprfield;

	qi::rule
	<
		Iterator
	> valueparam;
	
	qi::rule
	<
		Iterator
	> fields;
	
	qi::rule
	<
		Iterator
	> packet_struct;
	
	qi::rule
	<
		Iterator
	> packet_struct_copy;

	qi::rule
	<
		Iterator
	> item;

	qi::rule
	<
		Iterator
	> reply;

	qi::rule
	<
		Iterator
	> request;

	qi::rule
	<
		Iterator
	> event;

	qi::rule
	<
		Iterator
	> eventcopy;

	qi::rule
	<
		Iterator
	> error;

	qi::rule
	<
		Iterator
	> errorcopy;

	qi::rule
	<
		Iterator
	> struct_;

	qi::rule
	<
		Iterator
	> union_;

	qi::rule
	<
		Iterator
	> xidtype;

	qi::rule
	<
		Iterator
	> xidunion;

	qi::rule
	<
		Iterator
	> enum_;

	qi::rule
	<
		  Iterator
		//, xcppb::proto::typedef_()
	> typedef_;

	qi::rule
	<
		Iterator
	> import;

	qi::rule
	<
		  Iterator
		, std::string()
	> macro;

};

} // end namespace proto

} // end namespace lexer

#endif
