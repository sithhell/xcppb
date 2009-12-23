
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
	: reply::base_type( rule, "" )
	, fields_         ( tok )
	, valueparam_     ( tok )
{
	rule.name( "" );
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

} // end grammar

} // end xcbgen

} // end xcppb

namespace
{
	void instantiate()
	{
		using namespace xcppb::xcbgen::grammar;
		lexer_tokens t;
		reply<iterator_type> g( t );
	}
}
