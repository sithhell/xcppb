
#include <xcppb/xcbgen/grammar/union.hpp>

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
union_<Iterator>::union_
(
	  TokenDef const & tok
)
	: union_::base_type( rule, "union" )
	, name              ( tok, tok.name )
	, fields_           ( tok )
{
	rule.name( "union" );
	rule
		%= tok.union_begin
		>  name
		>  tok.close_tag
		>  +fields_
		>  tok.union_end
		;
}

template< typename Iterator >
bool union_<Iterator>::is_valid()
{
	return true;
}

template union_
<
	iterator_type
>
::union_
(
	lexer_tokens const &
);

} // end grammar

} // end xcbgen

} // end xcppb
