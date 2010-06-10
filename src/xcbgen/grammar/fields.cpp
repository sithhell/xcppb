
#include <xcppb/xcbgen/grammar/fields.hpp>

#include <xcppb/xcbgen/grammar/tokens.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace xcppb
{

namespace xcbgen
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
	: fields::base_type( rule, "fields" )
	, pad_             ( tok )
	, field_           ( tok )
	, list_            ( tok )
{
	rule.name( "fields" );
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

template fields
<
	iterator_type
>
::fields
(
	lexer_tokens const &
);

} // end grammar

} // end xcbgen

} // end xcppb
