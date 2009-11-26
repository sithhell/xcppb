
#ifndef XCPPB_PROTO_PARSER_HPP
#define XCPPB_PROTO_PARSER_HPP

#include <xcppb/proto/tokens.hpp>

#include <boost/config/warning_disable.hpp>
//#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/home/qi/action.hpp>
#include <boost/spirit/home/qi/auxiliary.hpp>
#include <boost/spirit/home/qi/char.hpp>
#include <boost/spirit/home/qi/binary.hpp>
#include <boost/spirit/home/qi/directive.hpp>
#include <boost/spirit/home/qi/nonterminal.hpp>
#include <boost/spirit/home/qi/numeric.hpp>
#include <boost/spirit/home/qi/operator.hpp>
#include <boost/spirit/home/qi/parse.hpp>
#include <boost/spirit/home/qi/parse_attr.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/skip_over.hpp>
#include <boost/spirit/home/qi/string.hpp>
#include <boost/spirit/home/qi/what.hpp>
#include <boost/spirit/home/phoenix.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant/recursive_variant.hpp>

namespace spirit = boost::spirit;
namespace phoenix = boost::phoenix;
namespace ascii = boost::spirit::ascii;
namespace qi = boost::spirit::qi;

namespace xcppb
{

namespace proto
{

template< typename Iterator/*, typename Lexer*/ >
struct grammar
	: qi::grammar< Iterator/*, qi::locals<std::string>, ascii::space_type*/ >
{
	template< typename TokenDef >
	grammar( TokenDef const & tok )
	//grammar( )
	:	grammar::base_type( xml )
	{
		any = *tok.any;

		/*close_tag
			= *tok.ws
			>> (
					  qi::lit( '>' )
					| (
						qi::lit( '/' ) >> qi::lit( '>' )
					  )
			   )
			;*/

		xml
			=  tok.prolog[ std::cout << phoenix::val( "prolog... \n" ) ]
			>  xcb
			;

		attribute
			=  qi::lit( '=' )
			>> *tok.ws
			>>  qi::lit( '"' ) //>> any
			>>  qi::in_state("ATTRIBUTE_VALUE")
				[
					tok.attribute[ std::cout << qi::_1 << "attribute ..." ]
				]
			>>  qi::lit( '"' )
			;

		xcb
			=  tok.xcb_begin
			>>     tok.header              >> attribute
			>>  -( tok.extension_xname     >> attribute )
			>>  -( tok.extension_name      >> attribute )
			>>  -( tok.extension_multiword >> attribute )
			>>  -( tok.major_version       >> attribute )
			>>  -( tok.minor_version       >> attribute )
			>>  tok.close_tag
			>>  *macro
			>>  tok.xcb_end
			;

		pad
			=  tok.pad
			>>  tok.bytes >> attribute
			>>  tok.close_tag
			;

		var
			= ( tok.name      > attribute[ std::cout << qi::_1 << " (name)... " ] )
			^ ( tok.type      > attribute[ std::cout << qi::_1 << " (type)... " ] )
			^ ( tok.enum_attr > attribute )
			^ ( tok.altenum   > attribute )
			^ ( tok.mask      > attribute )
			  
			;

		field
			=  tok.field
			>>  var
			>> tok.close_tag;
			;

		list
			= tok.list_begin
			>> var
			>> tok.close_tag
			>> qi::repeat( 0, 1 )[ expression ]
			>> tok.list_end
			;

		op
			= tok.op
			>> tok.op_attr 
			>> qi::lit( '=' ) 
			>> qi::lit( '"' ) 
			>> tok.op_attr_val
			>> qi::lit( '"' )
			>> expression >> expression
			;

		fieldref
			= tok.fieldref_begin
			>> any
			>> tok.fieldref_end
			;

		value
			= tok.value_begin
			>> any
			>> tok.value_end
			;

		bit
			= tok.bit_begin
			>> any
			>> tok.bit_end
			;

		expression
			= op
			| fieldref
			| value
			| bit
			;

		exprfield
			= tok.exprfield_begin
			>> var
			>> tok.close_tag
			>> expression
			>> tok.exprfield_end
			;

		valueparam
			=  tok.valueparam
			>> tok.value_mask_type >> attribute
			>> tok.value_mask_name >> attribute
			>> tok.value_list_name >> attribute
			>> tok.close_tag
			;

		fields
			= pad
			| field[ std::cout << phoenix::val( "found field ...\n" ) ]
			| list
			;

		struct_
			=  tok.name >> attribute
			>> tok.close_tag
			>> +fields
			;

		packet_struct
			=  tok.name >> attribute
			>> tok.number >> attribute
			>> tok.close_tag
			>> +fields
			;

		packet_struct_copy
			=  tok.name >> attribute
			>> tok.number >> attribute
			>> tok.ref >> attribute
			>> tok.close_tag
			;

		reply
			= tok.reply_begin
			>> +(
					  fields
					| valueparam
				)
			;

		request
			=  tok.request_begin
			>>     tok.name             >> attribute
			>>     tok.opcode           >> attribute
			>>  -( tok.combine_adjacent > attribute )
			>>  tok.close_tag
			>>  *(
						fields
					|  exprfield
					|  valueparam
				)
			>  qi::repeat( 0, 1 )[ reply ]
			>>  tok.request_end
			;

		xidtype
			= tok.xidtype
			>> tok.name
			>> attribute
			>> tok.close_tag
			;

		xidunion
			= tok.xidunion_begin
			>> tok.name >> attribute
			>> tok.close_tag
			>> +(
					   tok.type_begin
					>> any
					>> tok.type_end
			   )
			>> tok.xidunion_end
			;

		item
			= tok.item_begin
			>> tok.name >> attribute
			>> tok.close_tag
			>> qi::repeat( 0, 1 )[ expression ]
			>> tok.item_end
			;

		enum_
			=  tok.enum_begin
			>> tok.name >> attribute
			>> tok.close_tag
			>> *item
			>> tok.enum_end
			;

		typedef_
			=  tok.typedef_
			>> tok.oldname >> attribute
			>> tok.newname >> attribute
			>> tok.close_tag
			;

		import
			=  tok.import_begin
			>> any
			>> tok.import_end
			;

		macro
			=  request[ std::cout << phoenix::val( "found request ...\n" ) ]
			|  event[ std::cout << phoenix::val( "found event ...\n" ) ]
			|  ( tok.eventcopy >> packet_struct_copy )[ std::cout << phoenix::val( "found error ...\n" ) ]
			|  ( tok.error_begin >> packet_struct >> tok.error_end )[ std::cout << phoenix::val( "found error ...\n" ) ]
			|  ( tok.errorcopy >> packet_struct_copy )[ std::cout << phoenix::val( "found errorcopy ...\n" ) ]
			|  ( tok.struct_begin >> struct_ >> tok.struct_end )[ std::cout << phoenix::val( "found struct ...\n" ) ]
			|  ( tok.union_begin >> struct_ >> tok.union_end )[ std::cout << phoenix::val( "found union ...\n" ) ]
			|  xidtype[ std::cout << phoenix::val( "found xidtype ...\n" ) ]
			|  xidunion[ std::cout << phoenix::val( "found xidunion ...\n" ) ]
			|  enum_[ std::cout << phoenix::val( "found enum ...\n" ) ]
			|  typedef_[ std::cout << phoenix::val( "found typedef ...\n" ) ]
			|  import[ std::cout << phoenix::val( "found import ...\n" ) ]
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
		Iterator,
		std::string()
	> any;

	/*qi::rule
	<
		Iterator
	> close_tag;*/

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
