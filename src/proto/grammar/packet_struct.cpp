
#include <xcppb/proto/grammar/packet_struct.hpp>

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
packet_struct<Iterator>::packet_struct
(
	  TokenDef const & tok
)
	: packet_struct::base_type( rule, "" )
	, name                    ( tok, tok.name )
	, number                  ( tok, tok.number )
	, fields_                 ( tok )
{
	rule.name( "" );
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

} // end grammar

} // end proto

} // end xcppb

namespace
{
	void instantiate()
	{
		using namespace xcppb::proto::grammar;
		lexer_tokens t;
		packet_struct<iterator_type> g( t );
	}
}
