
#include <xcppb/xcbgen/grammar/bit.hpp>

#include <xcppb/xcbgen/grammar/tokens.hpp>

#include <boost/spirit/home/qi.hpp>
#include <boost/spirit/home/phoenix.hpp>
#include <boost/lexical_cast.hpp>

namespace
{
xcppb::xcbgen::attribute::bit convert( std::string const & s )
{
	xcppb::xcbgen::attribute::bit b;
	b.value = boost::lexical_cast<int>( s );

	return b;
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
bit<Iterator>::bit
(
	  TokenDef const & tok
)
	: bit::base_type( rule, "bit" )
{
	rule.name( "bit" );
	rule
		= tok.bit_begin
		>  tok.element[ qi::_val = phoenix::bind( ::convert,  qi::_1 ) ]
		>  '<' > tok.bit_end
		;
}

template< typename Iterator >
bool bit<Iterator>::is_valid()
{
	return true;
}

template
bit
<
	iterator_type
>::bit
(
	lexer_tokens const &
);

} // end grammar

} // end xcbgen

} // end xcppb
