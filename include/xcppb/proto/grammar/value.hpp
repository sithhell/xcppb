
#ifndef XCPPB_PROTO_GRAMMAR_VALUE_HPP
#define XCPPB_PROTO_GRAMMAR_VALUE_HPP

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace proto
{

namespace grammar
{

template< typename Iterator >
struct value
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, std::string()
	  >
{
	template< typename TokenDef >
	value
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, std::string()
	> rule;

	bool is_valid();
};

}

}

}

#endif
