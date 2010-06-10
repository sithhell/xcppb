
#include <xcppb/xcbgen/grammar/value.hpp>

#include <xcppb/xcbgen/grammar/tokens.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace
{

xcppb::xcbgen::attribute::value convert( std::string const & s )
{
	std::istringstream ss( s );
	unsigned ret( 0 );

	if( s[0] == '0' && s[1] == 'x' )
	{
		ss >> std::hex >> ret;
	}
	else
	{
		ss >> ret;
	}

	xcppb::xcbgen::attribute::value v;
	v.value = ret;

	return v;
}

}

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
value<Iterator>::value
(
	  TokenDef const & tok
)
	: value::base_type( rule, "value" )
{
	rule.name( "value" );
	rule
		= tok.value_begin
		>  tok.element[ qi::_val = phoenix::bind( ::convert, qi::_1 ) ]
		>  '<' >  tok.value_end
		;
}

template< typename Iterator >
bool value<Iterator>::is_valid()
{
	return true;
}

template value
<
	iterator_type
>
::value
(
	lexer_tokens const &
);


} // end grammar

} // end xcbgen

} // end xcppb
