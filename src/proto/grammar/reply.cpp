
#include <xcppb/proto/grammar/reply.hpp>

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

} // end proto

} // end xcppb

namespace
{
	void instantiate()
	{
		using namespace xcppb::proto::grammar;
		lexer_tokens t;
		reply<iterator_type> g( t );
	}
}
