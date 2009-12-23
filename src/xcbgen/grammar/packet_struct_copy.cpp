
#include <xcppb/xcbgen/grammar/packet_struct_copy.hpp>

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
packet_struct_copy<Iterator>::packet_struct_copy
(
	  TokenDef const & tok
)
	: packet_struct_copy::base_type( rule, "packet-struct" )
	, name                         ( tok, tok.name )
	, number                       ( tok, tok.number )
	, ref                          ( tok, tok.ref )
{
	rule.name( "packet-struct" );
	rule
		%= attributes
		>  tok.close_tag
		;

	attributes.name( "packet-struct-copy attributes" );
	attributes
		%=
		 (
			  name
			^ number
			^ ref
		 )
		;
}

template< typename Iterator >
bool packet_struct_copy<Iterator>::is_valid()
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
		packet_struct_copy<iterator_type> g( t );
	}
}
