
#include <xcppb/xcbgen/grammar/import.hpp>

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
import<Iterator>::import
(
	  TokenDef const & tok
)
	: import::base_type( rule, "import" )
{
	rule.name( "import" );
	rule
		%= tok.import_begin
		>  tok.element
		>  '<' > tok.import_end
		;
}

template< typename Iterator >
bool import<Iterator>::is_valid()
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
		import<iterator_type> g( t );
	}
}
