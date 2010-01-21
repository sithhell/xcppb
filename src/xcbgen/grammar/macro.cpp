
#include <xcppb/xcbgen/grammar/macro.hpp>

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
macro<Iterator>::macro
(
	  TokenDef const & tok
)
	: macro::base_type( rule, "macro" )
	, request_        ( tok )
	, event_          ( tok )
	, struct__        ( tok )
	, union__         ( tok )
	, xidtype_        ( tok )
	, xidunion_       ( tok )
	, enum__          ( tok )
	, typedef__       ( tok )
	, import_         ( tok )
	, packet_struct_     ( tok )
	, packet_struct_copy_( tok )
{
	rule.name( "macro" );
	rule
		%= request_
		|  event_
		|  eventcopy
		|  error
		|  errorcopy
		|  struct__
		|  union__
		|  xidtype_
		|  xidunion_
		|  enum__
		|  typedef__
		|  import_
		;

	eventcopy.name( "eventcopy" );
	eventcopy
		%= tok.eventcopy
		>  packet_struct_copy_
		;

	error.name( "error" );
	error
		%= tok.error_begin
		>  packet_struct_
		>  -( tok.error_end )
		;

	errorcopy.name( "errorcopy" );
	errorcopy
		%= tok.errorcopy
		>  packet_struct_copy_
		;
}

template< typename Iterator >
bool macro<Iterator>::is_valid()
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
		macro<iterator_type> g( t );
	}
}
