
#include <xcppb/proto/grammar/pad.hpp>

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
pad<Iterator>::pad
(
	  TokenDef const & tok
)
	: pad::base_type( rule, "pad" )
	, bytes         ( tok, tok.bytes )
{
	rule.name( "pad" );
	rule
		%= tok.pad
		>  bytes
		>  tok.close_tag
		;
}

template< typename Iterator >
bool pad<Iterator>::is_valid()
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
		pad<iterator_type> g( t );
	}
}
