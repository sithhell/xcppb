
#ifndef XCPPB_PROTO_GRAMMAR_XIDUNION_HPP
#define XCPPB_PROTO_GRAMMAR_XIDUNION_HPP

#include <xcppb/proto/grammar/attribute.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace proto
{

namespace grammar
{

template< typename Iterator >
struct xidunion
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//,
	  >
{
	template< typename TokenDef >
	xidunion
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, 
	> rule;

	boost::spirit::qi::rule
	<
		  Iterator
		//, 
	> type;

	attribute<Iterator> name;

	       bool is_valid();
};

}

}

}

#endif
