
#include <xcppb/xcbgen/grammar/exprfield.hpp>

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
exprfield<Iterator>::exprfield
(
	  TokenDef const & tok
)
	: exprfield::base_type( rule, "expression field" )
	, var_                 ( tok )
	, expression_          ( tok )
{
	rule.name( "expression field" );
	rule
		%= tok.exprfield_begin
		>  var_
		>  tok.close_tag
		>  expression_
		>  tok.exprfield_end
		;
}

template< typename Iterator >
bool exprfield<Iterator>::is_valid()
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
		exprfield<iterator_type> g( t );
	}
}
