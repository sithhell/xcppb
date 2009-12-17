
#include <xcppb/proto/grammar/request.hpp>

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
request<Iterator>::request
(
	  TokenDef const & tok
)
	: request::base_type( rule, "" )
	, name              ( tok, tok.name )
	, opcode            ( tok, tok.opcode )
	, combine_adjacent  ( tok, tok.combine_adjacent )
	, fields_           ( tok )
	, exprfield_        ( tok )
	, valueparam_       ( tok )
	, reply_            ( tok )
{
	rule.name( "" );
	rule
		%= tok.request_begin
		>  attributes
		>  tok.close_tag
		>  elements
		> 	-( reply_ )
		>  -( tok.request_end )
		;

	attributes.name( "request attributes" );
	attributes
		%=
		 (
			  name
			^ opcode
			^ combine_adjacent
		 )
		;

	elements.name( "request elements" );
	elements
		%=
		*(
			  fields_
			| exprfield_
			| valueparam_
		 )
		;
}

template< typename Iterator >
bool request<Iterator>::is_valid()
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
		request<iterator_type> g( t );
	}
}
