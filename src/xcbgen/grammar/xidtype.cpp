
#include <xcppb/xcbgen/grammar/xidtype.hpp>

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
xidtype<Iterator>::xidtype
(
	  TokenDef const & tok
)
	: xidtype::base_type( rule, "xidtype" )
	, name              ( tok, tok.name )
{
	rule.name( "xidtype" );
	rule
		%= tok.xidtype
		>  name
		>  tok.close_tag
		;
}

template< typename Iterator >
bool xidtype<Iterator>::is_valid()
{
	return true;
}

template xidtype
<
	iterator_type
>
::xidtype
(
	lexer_tokens const &
);

} // end grammar

} // end xcbgen

} // end xcppb
