
#include <xcppb/proto/grammar/item.hpp>

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
item<Iterator>::item
(
	  TokenDef const & tok
)
	: item::base_type( rule, "" )
	, name           ( tok, tok.name )
	, expression_     ( tok )
{
	rule.name( "" );
	rule
		%= tok.item_begin
		>  name
		>  tok.close_tag
		>
		-(
			  expression_
			> tok.item_end
		 )
		;
}

template< typename Iterator >
bool item<Iterator>::is_valid()
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
		item<iterator_type> g( t );
	}
}
