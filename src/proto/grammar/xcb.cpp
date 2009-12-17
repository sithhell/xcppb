
#include <xcppb/proto/grammar/xcb.hpp>

#include <xcppb/proto/grammar/tokens.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace xcppb
{

namespace proto
{

namespace grammar
{

namespace qi = boost::spirit::qi;
namespace lex = boost::spirit::lex;
namespace phoenix = boost::phoenix;

template< typename Iterator >
template< typename TokenDef >
xcb<Iterator>::xcb
(
	  TokenDef const & tok
)
	: xcb::base_type     ( rule, "xcb" )
	, header             ( tok, tok.header )
	, extension_xname    ( tok, tok.extension_xname )
	, extension_name     ( tok, tok.extension_name )
	, extension_multiword( tok, tok.extension_multiword )
	, major_version      ( tok, tok.major_version )
	, minor_version      ( tok, tok.minor_version )
	, macros             ( tok )
{
	rule.name( "xcb" );
	rule
		%= -( tok.prolog )
		>  tok.xcb_begin
		>  attributes
		>  tok.close_tag
		>  *macros
		>  tok.xcb_end
		;

	attributes.name( "xcb attributes" );
	attributes
		%=
		 (
			  header
			^ extension_xname
			^ extension_name
			^ extension_multiword
			^ major_version
			^ minor_version
		 )
		;

	qi::on_error<qi::fail>
	(
		rule,
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

template< typename Iterator >
bool xcb<Iterator>::is_valid()
{
	return true;
}

} // end grammar

} // end proto

} // end xcppb

namespace
{
	void instantiate()
	{
		using namespace xcppb::proto::grammar;
		lexer_tokens t;
		xcb<iterator_type> g( t );
	}
}
