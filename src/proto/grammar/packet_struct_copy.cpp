
#include <xcppb/proto/grammar/packet_struct_copy.hpp>

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
packet_struct_copy<Iterator>::packet_struct_copy
(
	  TokenDef const & tok
)
	: packet_struct_copy::base_type( rule, "" )
	, name                         ( tok, tok.name )
	, number                       ( tok, tok.number )
	, ref                          ( tok, tok.ref )
{
	rule.name( "" );
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

} // end proto

} // end xcppb

namespace
{
	void instantiate()
	{
		using namespace xcppb::proto::grammar;
		lexer_tokens t;
		packet_struct_copy<iterator_type> g( t );
	}
}
