
#include <xcppb/xcbgen/grammar/typedef.hpp>

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
typedef_<Iterator>::typedef_
(
	  TokenDef const & tok
)
	: typedef_::base_type( rule, "typedef" )
	, oldname            ( tok, tok.oldname )
	, newname            ( tok, tok.newname )
{
	rule.name( "typedef" );
	rule
		%= tok.typedef_
		>  attributes
		>  tok.close_tag
		;

	attributes.name( "typedef attributes" );
	attributes
		%= 
		 (
			  oldname
			^ newname
		 )
		;
}

template< typename Iterator >
bool typedef_<Iterator>::is_valid()
{
	return true;
}

template typedef_
<
	iterator_type
>
::typedef_
(
	lexer_tokens const &
);

} // end grammar

} // end xcbgen

} // end xcppb
