
#include <xcppb/xcbgen/grammar/valueparam.hpp>

#include <xcppb/xcbgen/grammar/tokens.hpp>

#include <boost/spirit/include/qi.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

namespace qi = boost::spirit::qi;
namespace lex = boost::spirit::lex;

template< typename Iterator >
template< typename TokenDef >
valueparam<Iterator>::valueparam
(
	  TokenDef const & tok
)
	: valueparam::base_type( rule, "" )
	, value_mask_type      ( tok, tok.value_mask_type )
	, value_mask_name      ( tok, tok.value_mask_name )
	, value_list_name      ( tok, tok.value_list_name )
{
	rule.name( "valueparam" );
	rule
		%= tok.valueparam
		>  attributes
		>  tok.close_tag
		;

	attributes.name( "valueparam attributes" );
	attributes
		%=
		 (
			  value_mask_type
			^ value_mask_name
			^ value_list_name
		 )
		;
}

template< typename Iterator >
bool valueparam<Iterator>::is_valid()
{
	return true;
}

} // end grammar

} // end xcbgen

} // end xcppb

namespace
{
	void instantiate()
	{
		using namespace xcppb::xcbgen::grammar;
		lexer_tokens t;
		valueparam<iterator_type> g( t );
	}
}
