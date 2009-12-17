
#include <xcppb/proto/grammar/xidtype.hpp>

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
xidtype<Iterator>::xidtype
(
	  TokenDef const & tok
)
	: xidtype::base_type( rule, "" )
	, name              ( tok, tok.name )
{
	rule.name( "" );
	rule
		%= tok.xidtype
		>  name
		>  tok.close_tag
		;
}

template< typename Iterator >
bool xidtype<Iterator>::is_valid()
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
		xidtype<iterator_type> g( t );
	}
}
