
#include <xcppb/xcbgen/grammar/event.hpp>

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
event<Iterator>::event
(
	  TokenDef const & tok
)
	: event::base_type  ( rule, "" )
	, name              ( tok, tok.name )
	, number            ( tok, tok.number )
	, no_sequence_number( tok, tok.no_sequence_number )
	, fields_           ( tok )
{
	rule.name( "" );
	rule
		%= tok.event_begin
		>  attributes
		>  tok.close_tag
		>  +fields_
		>  tok.event_end
		;

	attributes.name( "event attributes" );
	attributes
		%=
		 (
			  name
			^ number
			^ no_sequence_number
		 )
		;

}

template< typename Iterator >
bool event<Iterator>::is_valid()
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
		event<iterator_type> g( t );
	}
}
