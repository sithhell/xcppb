
#include <xcppb/xcbgen/grammar/attribute.hpp>

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
attribute<Iterator>::attribute
(
	  TokenDef const & tok
	, lex::token_def<lex::omit> const & attribute_tok
)
	: attribute::base_type( rule, "attribute" )
{
	rule.name( "attribute" );
	rule
		%= attribute_tok
		>  '='
		>  tok.attribute_begin
		>  tok.attribute
		>  tok.attribute_end
		;
}

template< typename Iterator >
bool attribute<Iterator>::is_valid()
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
		attribute<iterator_type> g( t, t.name );
	}
}
