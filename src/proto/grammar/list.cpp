
#include <xcppb/proto/grammar/list.hpp>

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

} // end proto

} // end xcppb

namespace
{
	void instantiate()
	{
		using namespace xcppb::proto::grammar;
		lexer_tokens t;
		list<iterator_type> g( t );
	}
}
