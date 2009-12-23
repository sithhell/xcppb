
#include <xcppb/xcbgen/grammar/macro.hpp>

#include <xcppb/xcbgen/grammar/tokens.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace {

void test( std::string const & s )
{
	std::cout << "xidtype: " << s << "\n";
}
#if 0
void test( xcppb::xcbgen::attribute::xidunion const & u )
{
	std::cout << "xidunion: " << u.name << "\n";

	std::copy( u.types.begin(), u.types.end(), std::ostream_iterator<std::string>( std::cout, "\n" ) );
}
#endif


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
macro<Iterator>::macro
(
	  TokenDef const & tok
)
	: macro::base_type( rule, "" )
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
	rule.name( "" );
	rule
		%= request_
		|  event_
		|  eventcopy
		|  error
		|  errorcopy
		|  struct__
		|  union__
		|  xidtype_[ ::test ]
		|  xidunion_
		|  enum__
		|  typedef__
		|  import_
		;

	eventcopy
		%= tok.eventcopy
		>  packet_struct_copy_
		;

	error
		%= tok.error_begin
		>  packet_struct_
		>  -( tok.error_end )
		;

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
