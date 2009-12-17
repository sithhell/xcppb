
#include <xcppb/proto/grammar/enum.hpp>

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
enum_<Iterator>::enum_
(
	  TokenDef const & tok
)
	: enum_::base_type( rule, "enum" )
	, name            ( tok, tok.name )
	, item_           ( tok )
{
	rule.name( "enum" );
	rule
		%= tok.enum_begin
		>  name
		>  tok.close_tag
		>  *item_
		>  tok.enum_end
		;
}

template< typename Iterator >
bool enum_<Iterator>::is_valid()
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
		enum_<iterator_type> g( t );
	}
}
