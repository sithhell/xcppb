
#include <xcppb/xcbgen/grammar/pad.hpp>

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
pad<Iterator>::pad
(
	  TokenDef const & tok
)
	: pad::base_type( rule, "pad" )
	//, bytes         ( tok, tok.bytes )
{
	rule.name( "pad" );
	rule
		%= tok.pad
		>  tok.bytes 
		>  '='
		>  tok.attribute_begin
		>  tok.attribute
		>  tok.attribute_end
		//>  bytes
		>  tok.close_tag
		;
}

template< typename Iterator >
bool pad<Iterator>::is_valid()
{
	return true;
}

template pad
<
	iterator_type
>
::pad
(
	lexer_tokens const &
);

} // end grammar

} // end xcbgen

} // end xcppb
