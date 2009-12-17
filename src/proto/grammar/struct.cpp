
#include <xcppb/proto/grammar/struct.hpp>

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
struct_<Iterator>::struct_
(
	  TokenDef const & tok
)
	: struct_::base_type( rule, "" )
	, name              ( tok, tok.name )
	, fields_            ( tok )
{
	rule.name( "" );
	rule
		%= tok.struct_begin
		>  name
		>  tok.close_tag
		>  +fields_
		>  tok.struct_end
		;
}

template< typename Iterator >
bool struct_<Iterator>::is_valid()
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
		struct_<iterator_type> g( t );
	}
}
