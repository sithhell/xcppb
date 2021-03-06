
#include <xcppb/xcbgen/grammar/reply.hpp>

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
reply<Iterator>::reply
(
	  TokenDef const & tok
)
	: reply::base_type( rule, "reply" )
	, fields_         ( tok )
	, valueparam_     ( tok )
{
	rule.name( "reply" );
	rule
		%= tok.reply_begin
		>
		+(
			  fields_
			| valueparam_
		 )
		>  tok.reply_end
		;
}

template< typename Iterator >
bool reply<Iterator>::is_valid()
{
	return true;
}

template reply
<
	iterator_type
>
::reply
(
	lexer_tokens const &
);

} // end grammar

} // end xcbgen

} // end xcppb
