
#include <xcppb/proto/grammar/bit.hpp>

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
bit<Iterator>::bit
(
	  TokenDef const & tok
)
	: bit::base_type( rule, "" )
{
	rule.name( "" );
	rule
		%= tok.bit_begin
		>  tok.element
		>  '<' > tok.bit_end
		;
}

template< typename Iterator >
bool bit<Iterator>::is_valid()
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
		bit<iterator_type> g( t );
	}
}
