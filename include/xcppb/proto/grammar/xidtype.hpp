
#ifndef XCPPB_PROTO_GRAMMAR_XIDTYPE_HPP
#define XCPPB_PROTO_GRAMMAR_XIDTYPE_HPP

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
struct xidtype
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//,
	  >
{
	template< typename TokenDef >
	xidtype
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, 
	> rule;

	attribute<Iterator> name;

	       bool is_valid();
};

}

}

}

#endif
