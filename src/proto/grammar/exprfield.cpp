
#include <xcppb/proto/grammar/exprfield.hpp>

#include <xcppb/proto/grammar/tokens.hpp>

#include <boost/spirit/include/qi.hpp>

namespace xcppb
{

namespace proto
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
	: exprfield::base_type( rule, "" )
	, var_                 ( tok )
	, expression_          ( tok )
{
	rule.name( "" );
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

} // end proto

} // end xcppb

namespace
{
	void instantiate()
	{
		using namespace xcppb::proto::grammar;
		lexer_tokens t;
		exprfield<iterator_type> g( t );
	}
}
