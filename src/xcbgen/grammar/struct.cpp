
#include <xcppb/xcbgen/grammar/struct.hpp>

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
struct_<Iterator>::struct_
(
	  TokenDef const & tok
)
	: struct_::base_type( rule, "struct" )
	, name              ( tok, tok.name )
	, fields_            ( tok )
{
	rule.name( "struct" );
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

template struct_
<
	iterator_type
>
::struct_
(
	lexer_tokens const &
);

} // end grammar

} // end xcbgen

} // end xcppb
