
#include <xcppb/proto/grammar/fieldref.hpp>

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

template< typename Iterator >
template< typename TokenDef >
fieldref<Iterator>::fieldref
(
	  TokenDef const & tok
)
	: fieldref::base_type( rule, "" )
{
	rule.name( "" );
	rule
		%= tok.fieldref_begin
		>  tok.element
		>  '<' >  tok.fieldref_end
		;
}

template< typename Iterator >
bool fieldref<Iterator>::is_valid()
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
		fieldref<iterator_type> g( t );
	}
}
