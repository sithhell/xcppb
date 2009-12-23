
#include <xcppb/xcbgen/grammar/field.hpp>

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
field<Iterator>::field
(
	  TokenDef const & tok
)
	: field::base_type( rule, "field" )
	, field_attributes( tok )
{
	rule.name( "field" );
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

} // end xcbgen

} // end xcppb

namespace
{
	void instantiate()
	{
		using namespace xcppb::xcbgen::grammar;
		lexer_tokens t;
		field<iterator_type> g( t );
	}
}
