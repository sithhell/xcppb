
#include <xcppb/proto/grammar/union.hpp>

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
union_<Iterator>::union_
(
	  TokenDef const & tok
)
	: union_::base_type( rule, "" )
	, name              ( tok, tok.name )
	, fields_           ( tok )
{
	rule.name( "" );
	rule
		%= tok.union_begin
		>  name
		>  tok.close_tag
		>  +fields_
		>  tok.union_end
		;
}

template< typename Iterator >
bool union_<Iterator>::is_valid()
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
		union_<iterator_type> g( t );
	}
}
