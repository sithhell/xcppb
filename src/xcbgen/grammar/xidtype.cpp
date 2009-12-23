
#include <xcppb/xcbgen/grammar/xidtype.hpp>

#include <xcppb/xcbgen/grammar/tokens.hpp>

#include <boost/spirit/include/qi.hpp>

namespace xcppb
{

namespace xcbgen
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

} // end xcbgen

} // end xcppb

namespace
{
	void instantiate()
	{
		using namespace xcppb::xcbgen::grammar;
		lexer_tokens t;
		xidtype<iterator_type> g( t );
	}
}
