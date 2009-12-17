
#include <xcppb/proto/grammar/xidunion.hpp>

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
xidunion<Iterator>::xidunion
(
	  TokenDef const & tok
)
	: xidunion::base_type( rule, "" )
	, name               ( tok, tok.name )
{
	rule.name( "" );
	rule
		%= tok.xidunion_begin
		>  name
		>  tok.close_tag
		>  +type
		>  tok.xidunion_end
		;

	type.name( "xidunion type" );
	type
		%= tok.type_begin
		>  tok.element
		>  '<' > tok.type_end
		;
}

template< typename Iterator >
bool xidunion<Iterator>::is_valid()
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
		xidunion<iterator_type> g( t );
	}
}
