
#include <xcppb/proto/grammar/expression.hpp>

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
expression<Iterator>::expression
(
	  TokenDef const & tok
)
	: expression::base_type( rule, "" )
	, fieldref_             ( tok )
	, value_                ( tok )
	, bit_                  ( tok )
	, op_attribute ( tok, tok.op_attr )
{
	rule.name( "" );
	rule
		%= op
		|  fieldref_
		|  value_
		|  bit_
		;
	
	op
		%= tok.op_begin
		>  op_attribute
		>  tok.close_tag
		>  rule
		>  rule
		>  tok.op_end
		;
}

template< typename Iterator >
bool expression<Iterator>::is_valid()
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
		expression<iterator_type> g( t );
	}
}
