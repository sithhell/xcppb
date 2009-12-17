
#ifndef XCPPB_PROTO_GRAMMAR_ITEM_HPP
#define XCPPB_PROTO_GRAMMAR_ITEM_HPP

#include <xcppb/proto/grammar/attribute.hpp>
#include <xcppb/proto/grammar/expression.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace proto
{

namespace grammar
{

template< typename Iterator >
struct item
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//,
	  >
{
	template< typename TokenDef >
	item
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, 
	> rule;

	attribute<Iterator>  name;
	expression<Iterator> expression_;

	       bool is_valid();
};

}

}

}

#endif
