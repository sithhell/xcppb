
#include <xcppb/proto/grammar/var.hpp>

#include <xcppb/proto/grammar/tokens.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace xcppb
{

namespace proto
{

namespace grammar
{

namespace qi = boost::spirit::qi;
namespace lex = boost::spirit::lex;
namespace phoenix = boost::phoenix;

template< typename Iterator >
template< typename TokenDef >
var<Iterator>::var
(
	  TokenDef const & tok
)
	: var::base_type( rule, "var" )
	, name          ( tok, tok.name )
	, type          ( tok, tok.type )
	, enum_attr     ( tok, tok.enum_attr )
	, altenum       ( tok, tok.altenum )
	, mask          ( tok, tok.mask )
{
	rule.name( "var" );
	rule
		%=
		 (
			  name
			^ type
			^ enum_attr
			^ altenum
			^ mask
		 )
		;
}

template< typename Iterator >
bool var<Iterator>::is_valid()
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
		var<iterator_type> g( t );
	}
}
