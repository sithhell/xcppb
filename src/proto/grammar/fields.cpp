
#include <xcppb/proto/grammar/fields.hpp>

#include <xcppb/proto/grammar/tokens.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace xcppb
{

namespace proto
{

namespace grammar
{

namespace qi = boost::spirit::qi;
namespace lex = boost::spirit::lex;
namespace phoenix = boost::phoenix;

template< typename Iterator >
template< typename TokenDef >
fields<Iterator>::fields
(
	  TokenDef const & tok
)
	: fields::base_type( rule, "" )
	, pad_             ( tok )
	, field_           ( tok )
	, list_            ( tok )
{
	rule.name( "" );
	rule
		%= pad_
		|  field_
		|  list_
		;
}

template< typename Iterator >
bool fields<Iterator>::is_valid()
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
		fields<iterator_type> g( t );
	}
}
