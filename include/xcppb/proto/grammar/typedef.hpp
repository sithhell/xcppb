
#ifndef XCPPB_PROTO_GRAMMAR_TYPEDEF_HPP
#define XCPPB_PROTO_GRAMMAR_TYPEDEF_HPP

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
struct typedef_
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//,
	  >
{
	template< typename TokenDef >
	typedef_
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
	> attributes;

	attribute<Iterator> oldname;
	attribute<Iterator> newname;

	       bool is_valid();
};

}

}

}

#endif
