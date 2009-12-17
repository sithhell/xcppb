
#include <xcppb/proto/grammar/field.hpp>

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
field<Iterator>::field
(
	  TokenDef const & tok
)
	: field::base_type( rule, "" )
	, field_attributes( tok )
{
	rule.name( "" );
	rule
		%= tok.field
		>  field_attributes
		>  tok.close_tag
		;
}

template< typename Iterator >
bool field<Iterator>::is_valid()
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
		field<iterator_type> g( t );
	}
}
