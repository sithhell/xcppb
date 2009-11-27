
#ifndef XCPPB_PROTO_PARSER_HPP
#define XCPPB_PROTO_PARSER_HPP

#include <xcppb/proto/tokens.hpp>

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>

namespace spirit = boost::spirit;
namespace phoenix = boost::phoenix;
namespace ascii = boost::spirit::ascii;
namespace qi = boost::spirit::qi;

namespace xcppb
{

namespace proto
{

template< typename Iterator >
struct grammar
	: qi::grammar< Iterator/*, qi::locals<std::string>, ascii::space_type*/ >
{
	template< typename TokenDef >
	grammar( TokenDef const & tok )
	:	grammar::base_type( xml, "xml" )
	{
		xml.name( "xml" );
		xml
			= -( tok.prolog )
			> xcb
			;

		attribute.name( "attribute" );
		attribute
			=  qi::lit( "=" )
			>  tok.attribute_begin
			>  tok.attribute
			>  tok.attribute_end
			;

		xcb.name( "xcb" );
		xcb
			=  tok.xcb_begin
			>  (
					  ( tok.header              > attribute )
					^ ( tok.extension_xname     > attribute )
					^ ( tok.extension_name      > attribute )
					^ ( tok.extension_multiword > attribute )
					^ ( tok.major_version       > attribute )
					^ ( tok.minor_version       > attribute )
			   )
			>  tok.close_tag
			>> *macro
			>  tok.xcb_end
			;

		pad.name( "pad" );
		pad
			= tok.pad
			> tok.bytes > attribute
			> tok.close_tag
			;

		var.name( "var" );
		var
			= ( tok.name      > attribute )
			^ ( tok.type      > attribute )
			^ ( tok.enum_attr > attribute )
			^ ( tok.altenum   > attribute )
			^ ( tok.mask      > attribute )
			;

		field.name( "field" );
		field
			= tok.field
			> var
			> tok.close_tag;
			;

		list.name( "name" );
		list
			= tok.list_begin
			> var
			> tok.close_tag
			> -( expression > tok.list_end )
			;

		op.name( "op" );
		op
			= tok.op_begin
			> tok.op_attr > attribute
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
			> var
			> tok.close_tag
			> expression
			> tok.exprfield_end
			;

		valueparam.name( "valueparam" );
		valueparam
			=  tok.valueparam
			> tok.value_mask_type > attribute
			> tok.value_mask_name > attribute
			> tok.value_list_name > attribute
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
			=  tok.name > attribute
			> tok.close_tag
			> +fields
			;

		packet_struct.name( "packet-struct" );
		packet_struct
			= tok.name   > attribute
			> tok.number > attribute
			> tok.close_tag
			> *fields
			;

		packet_struct_copy.name( "packet-struct-copy" );
		packet_struct_copy
			=
			(
				  ( tok.name   > attribute )
				^ ( tok.number > attribute )
				^ ( tok.ref    > attribute )
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
				  ( tok.name             > attribute )
				^ ( tok.opcode           > attribute )
				^ ( tok.combine_adjacent > attribute )
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
				  ( tok.name               > attribute )
				^ ( tok.number             > attribute )
				^ ( tok.no_sequence_number > attribute )
			)
			> tok.close_tag
			> +fields
			> tok.event_end
			;

		xidtype.name( "xidtype" );
		xidtype
			= tok.xidtype
			> tok.name > attribute
			> tok.close_tag
			;

		xidunion.name( "xidunion" );
		xidunion
			= tok.xidunion_begin
			> tok.name > attribute
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
			> tok.name > attribute
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
			> tok.name > attribute
			> tok.close_tag
			> *item
			> tok.enum_end
			;

		typedef_.name( "typedef" );
		typedef_
			= tok.typedef_
			> tok.oldname > attribute
			> tok.newname > attribute
			> tok.close_tag
			;

		import.name( "import" );
		import
			= tok.import_begin
			> tok.element
			> qi::lit( '<' ) > tok.import_end
			;

		macro.name( "macro" );
		macro
			= request
			| event
			| 
			(
				  tok.eventcopy
				> packet_struct_copy
			)
			|
			(
				  tok.error_begin
				> packet_struct
				> -( tok.error_end ) )
			|
			(
				  tok.errorcopy
				> packet_struct_copy
			)
			|
			(
				  tok.struct_begin
				> struct_
				> tok.struct_end
			)
			|
			(
				  tok.union_begin
				> struct_
				> tok.union_end
			)
			|  xidtype
			|  xidunion
			|  enum_
			|  typedef_
			|  import
			;

		qi::on_error<qi::fail>
		(
			xml,
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
	> xml;

	qi::rule
	<
		Iterator,
		std::string()
	> attribute;

	qi::rule
	<
		Iterator
	> xcb;

	qi::rule
	<
		Iterator
	> pad;
	
	qi::rule
	<
		Iterator
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
	> typedef_;

	qi::rule
	<
		Iterator
	> import;

	qi::rule
	<
		Iterator
	> macro;

};

} // end namespace proto

} // end namespace lexer

#endif
