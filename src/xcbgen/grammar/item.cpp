
#include <xcppb/xcbgen/grammar/item.hpp>

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
item<Iterator>::item
(
	  TokenDef const & tok
)
	: item::base_type( rule, "item" )
	, name           ( tok, tok.name )
	, expression_     ( tok )
{
	rule.name( "item" );
	rule
		%= tok.item_begin
		>  name
		>  tok.close_tag
		>
		-(
			  expression_
			> tok.item_end
		 )
		;
}

template< typename Iterator >
bool item<Iterator>::is_valid()
{
	return true;
}

template item
<
	iterator_type
>
::item
(
	lexer_tokens const &
);

} // end grammar

} // end xcbgen

} // end xcppb
