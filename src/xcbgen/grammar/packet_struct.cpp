
#include <xcppb/xcbgen/grammar/packet_struct.hpp>

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
packet_struct<Iterator>::packet_struct
(
	  TokenDef const & tok
)
	: packet_struct::base_type( rule, "packet_struct" )
	, name                    ( tok, tok.name )
	, number                  ( tok, tok.number )
	, fields_                 ( tok )
{
	rule.name( "packet_struct" );
	rule
		%= name
		>  number
		>  tok.close_tag
		>  *fields_
		;
}

template< typename Iterator >
bool packet_struct<Iterator>::is_valid()
{
	return true;
}

template packet_struct
<
	iterator_type
>
::packet_struct
(
	lexer_tokens const &
);

} // end grammar

} // end xcbgen

} // end xcppb
