
#include <xcppb/proto/grammar/attribute.hpp>

#include <xcppb/proto/grammar/tokens.hpp>

#include <boost/spirit/home/qi.hpp>

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

} // end proto

} // end xcppb

namespace
{
	void instantiate()
	{
		using namespace xcppb::proto::grammar;
		lexer_tokens t;
		attribute<iterator_type> g( t, t.name );
	}
}
