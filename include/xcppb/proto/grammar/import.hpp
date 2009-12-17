
#ifndef XCPPB_PROTO_GRAMMAR_IMPORT_HPP
#define XCPPB_PROTO_GRAMMAR_IMPORT_HPP

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace proto
{

namespace grammar
{

template< typename Iterator >
struct import
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//,
	  >
{
	template< typename TokenDef >
	import
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, 
	> rule;

	       bool is_valid();
};

}

}

}

#endif
