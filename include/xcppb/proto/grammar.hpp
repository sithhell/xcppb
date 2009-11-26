
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
/*
    struct mini_xml;

    typedef
        boost::variant<
            boost::recursive_wrapper<mini_xml>
          , std::string
        >
    mini_xml_node;

    struct mini_xml
    {
        std::string name;                           // tag name
        std::vector<mini_xml_node> children;        // children
    };

	 // We need to tell fusion about our mini_xml struct
// to make it a first-class fusion citizen
BOOST_FUSION_ADAPT_STRUCT(
    xcppb::proto::mini_xml,
    (std::string, name)
    (std::vector<xcpbb::proto::mini_xml_node>, children)
)*/

template< typename Iterator/*, typename Lexer*/ >
struct grammar
	: qi::grammar< Iterator/*, qi::locals<std::string>, ascii::space_type*/ >
{
	template< typename TokenDef >
	grammar( TokenDef const & tok )
	//grammar( )
	:	grammar::base_type( xml )
	{
#if 0
		/*
		text %= +( tok.tag | tok.ws );
		node %= xml | text;

		attribute
			= qi::lexeme[ +( qi::char_ - '=' ) ]
			> '='
			>  qi::lexeme[ +( qi::char_ - '>' ) ]
			;

		start_tag
			%= qi::lit( '<' )
			>> qi::in_state( "TAG" )
				[
						tok.tag
					>	qi::omit
						[
							*tok.ws_tag
						]
					>	qi::lit( '>' )
				]
			;

		end_tag
			=	qi::lit( '<' )
			>>	qi::in_state( "TAG" )
				[
						qi::lit( '/' )
					>	tok.tag
						[
							phoenix::if_( qi::_r1 != qi::_1 )
							[
								qi::_pass = false
							]
						]
					>	qi::omit
						[
							*tok.ws_tag
						]
					> qi::lit( '>' )
				]
			;*/
		element = *tok.ws;

		comment
			=	tok.comment_begin[ std::cout << phoenix::val( "comment:\n" ) ]
			> 	qi::in_state( "COMMENT" )
				[
					*tok.any[ std::cout << qi::_1 << "\n" ]
				]
			>	tok.comment_end
			;

		misc
			=	comment
			//|	processing_instructions
			|	+tok.ws
			;

		xml
			= 	//prolog[ std::cout << phoenix::val( "parsed prolog ... " ) ]
			//>> element
			 *misc
			;

		prolog
			=	-xml_decl
			>>	*misc
			>>	-(
						doc_type_decl
					>>	*misc
				)
			;

		xml_decl
			=	tok.prolog_begin
			>	version_info
			>	qi::omit
				[
					-( +tok.ws )
				]
			> tok.prolog_end
			;

		version_info
			=	+tok.ws
			>	tok.version
			> 	-( +tok.ws ) > qi::lit( '=' ) > -( +tok.ws )
			>	(
						( qi::lit( '\'' ) >> tok.version_num >> qi::lit( '\'' ) )
					|	( qi::lit( '"' ) >> tok.version_num >> qi::lit( '"' ) )
				)
			;

		xml
			%= prolog
			>> qi::omit
            [
            	*tok.ws
            ]
			>>	start_tag
				[
					qi::_a = qi::_1,
				]
			>  *node
			>> qi::omit
				[
					*tok.ws
				]
			>  end_tag( qi::_a )
			>> qi::omit
				[
					*tok.ws
				]
			;
#endif
		any = *tok.any;
		ws  = tok.ws;

		close_tag
			= qi::lit( '>' )
			|
				(
					qi::lit( '/' ) > qi::lit( '>' )
				)
			;

		xml
			=  *tok.ws
			>  tok.prolog[ std::cout << phoenix::val( "prolog... " ) ]
			>  *tok.ws
			>  xcb
			>  *tok.ws
			;

		attribute
			=  *ws
			>  qi::lit( '=' )
			>  *ws
			>  qi::lit( '"' )
			>  any
			>  qi::lit( '"' )
			>  *ws
			;

		xcb
			=  tok.xcb_begin
			>>  +ws
			>     tok.header              > attribute
			>  -( tok.extension_xname     > attribute )
			>  -( tok.extension_name      > attribute )
			>  -( tok.extension_multiword > attribute )
			>  -( tok.major_version       > attribute )
			>  -( tok.minor_version       > attribute )
			>  close_tag
			>>  *tok.ws
			>>  *macro
			>>  *tok.ws
			>  tok.xcb_end
			;

		pad
			=  tok.pad
			>  +ws
			>  tok.bytes                  > attribute
			>  close_tag
			;

		var
			=    tok.name      > attribute
			>    tok.type      > attribute
			> -( tok.enum_attr > attribute )
			> -( tok.altenum   > attribute )
			> -( tok.mask      > attribute )
			;

		field
			=  tok.field
			>  +ws
			>  var
			>  close_tag
			;

		list
			= tok.list_begin
			> var
			> close_tag
			> *ws
			> repeat( 0, 1 )[ expression ]
			> *ws
			> tok.list_end
			;

		op
			= tok.op
			> tok.op_attr > *ws > qi::lit( '=' ) > *ws > qi::lit( '"' ) > tok.op_attr_val > qi::lit( '"' ) > *ws
			> expression > expression
			;

		expression
			= op
			| fieldref
			| value
			| bit
			;

		exprfield
			= tok.exprfield_begin
			> var
			> close_tag
			> *ws
			> expression
			> *ws
			> tok.exprfield_end
			;

		valueparam
			= tok

		request
			=  tok.request_begin
			>  +ws
			>     tok.name                > attribute
			>     tok.opcode              > attribute
			>  -( tok.combine_adjacent    > attribute )
			>  close_tag
			>> *ws
			>  *(
						fields
					|  exprfield
					|  valueparam
				)
			>  qi::repeat( 0, 1 )[ reply ]
			>> *ws
			>  tok.request_end
			;

		macro
			=  request
			|  event
			|  eventcopy
			|  error
			|  errorcopy
			|  struct_
			|  union_
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
		Iterator//,
		//qi::locals<std::string>//,
		//ascii::space_type
		//qi::in_state_skipper< Lexer >
	> xml;

	qi::rule
	<
		Iterator//,
		//qi::locals<std::string>//,
		//ascii::space_type
		//qi::in_state_skipper< Lexer >
	> attribute;

	qi::rule
	<
		Iterator//,
		//qi::locals<std::string>//,
		//ascii::space_type
		//qi::in_state_skipper< Lexer >
	> xcb;
	
	qi::rule
	<
		Iterator//,
		//qi::locals<std::string>//,
		//ascii::space_type
		//qi::in_state_skipper< Lexer >
	> macro;

	qi::rule
	<
		Iterator//,
		//qi::locals<std::string>//,
		//ascii::space_type
		//qi::in_state_skipper< Lexer >
	> any;
	
	qi::rule
	<
		Iterator//,
		//qi::locals<std::string>//,
		//ascii::space_type
		//qi::in_state_skipper< Lexer >
	> ws;

	qi::rule
	<
		Iterator//,
		//qi::locals<std::string>//,
		//ascii::space_type
		//qi::in_state_skipper< Lexer >
	> close_tag;

#if 0
	qi::rule
	<
		Iterator//,
		//ascii::space_type
		//qi::in_state_skipper< Lexer >
	> prolog;

	qi::rule
	<
		Iterator//,
		//ascii::space_type
		//qi::in_state_skipper< Lexer >
	> xml_decl;

	qi::rule
	<
		Iterator//,
		//ascii::space_type
		//qi::in_state_skipper< Lexer >
	> element;

	qi::rule
	<
		Iterator//,
		//ascii::space_type
		//qi::in_state_skipper< Lexer >
	> misc;

	qi::rule
	<
		Iterator
	> version_info;

	qi::rule
	<
		Iterator
	> doc_type_decl;

	qi::rule
	<
		Iterator
	> comment;
	qi::rule
	<
		Iterator//,
		//ascii::space_type
		//qi::in_state_skipper< Lexer >
	> node;

	qi::rule
	<
		Iterator//,
		//std::string(),
		//ascii::space_type
		//qi::in_state_skipper< Lexer >
	> text;

	qi::rule
	<
		Iterator,
		std::string()//,
		//ascii::space_type
		//qi::in_state_skipper< Lexer >
	> start_tag;

	qi::rule
	<
		Iterator,
		void( std::string )//,
		//ascii::space_type
		//qi::in_state_skipper< Lexer >
	> end_tag;

	qi::rule
	<
		Iterator//,
		//ascii::space_type
		//qi::in_state_skipper< Lexer >
	> attribute;
#endif
};

} // end namespace proto

} // end namespace lexer

#endif
