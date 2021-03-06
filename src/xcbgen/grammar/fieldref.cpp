
#include <xcppb/xcbgen/grammar/fieldref.hpp>

#include <xcppb/xcbgen/grammar/tokens.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace
{
xcppb::xcbgen::attribute::fieldref convert( std::string const & s )
{
	xcppb::xcbgen::attribute::fieldref b;
	b.ref = s ;

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

template< typename Iterator >
template< typename TokenDef >
fieldref<Iterator>::fieldref
(
	  TokenDef const & tok
)
	: fieldref::base_type( rule, "field reference" )
{
	rule.name( "field reference" );
	rule
		= tok.fieldref_begin
		>  tok.element[ qi::_val = phoenix::bind( ::convert, qi::_1 ) ]
		>  '<' >  tok.fieldref_end
		;
}

template< typename Iterator >
bool fieldref<Iterator>::is_valid()
{
	return true;
}

template fieldref
<
	iterator_type
>
::fieldref
(
	lexer_tokens const &
);

} // end grammar

} // end xcbgen

} // end xcppb
