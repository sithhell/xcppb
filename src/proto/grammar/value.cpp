
#include <xcppb/proto/grammar/value.hpp>

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
value<Iterator>::value
(
	  TokenDef const & tok
)
	: value::base_type( rule, "" )
{
	rule.name( "" );
	rule
		%= tok.value_begin
		>  tok.element
		>  '<' >  tok.value_end
		;
}

template< typename Iterator >
bool value<Iterator>::is_valid()
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
		value<iterator_type> g( t );
	}
}
