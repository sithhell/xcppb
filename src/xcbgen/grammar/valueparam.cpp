
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
	: valueparam::base_type( rule, "valueparam" )
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

template valueparam
<
	iterator_type
>
::valueparam
(
	lexer_tokens const &
);

} // end grammar

} // end xcbgen

} // end xcppb
