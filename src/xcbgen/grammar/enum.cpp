
#include <xcppb/xcbgen/grammar/enum.hpp>

#include <xcppb/xcbgen/grammar/tokens.hpp>

#include <boost/spirit/home/qi.hpp>

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
enum_<Iterator>::enum_
(
	  TokenDef const & tok
)
	: enum_::base_type( rule, "enum" )
	, name            ( tok, tok.name )
	, item_           ( tok )
{
	rule.name( "enum" );
	rule
		%= tok.enum_begin
		>  name
		>  tok.close_tag
		>  *item_
		>  tok.enum_end
		;
}

template< typename Iterator >
bool enum_<Iterator>::is_valid()
{
	return true;
}

template enum_
<
	iterator_type
>
::enum_
(
	lexer_tokens const &
);

} // end grammar

} // end xcbgen

} // end xcppb
