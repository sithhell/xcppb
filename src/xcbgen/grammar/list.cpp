
#include <xcppb/xcbgen/grammar/list.hpp>

#include <xcppb/xcbgen/grammar/tokens.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

namespace qi = boost::spirit::qi;
namespace lex = boost::spirit::lex;
namespace phoenix = boost::phoenix;

template< typename Iterator >
template< typename TokenDef >
list<Iterator>::list
(
	  TokenDef const & tok
)
	: list::base_type( rule, "list" )
	, list_attributes( tok )
	, expression_( tok )
{
	rule.name( "list" );
	rule
		%= tok.list_begin
		>  list_attributes
		>  tok.close_tag
		>
		-(
			  expression_
			> tok.list_end
		 )
		;
}

template< typename Iterator >
bool list<Iterator>::is_valid()
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
		list<iterator_type> g( t );
	}
}
