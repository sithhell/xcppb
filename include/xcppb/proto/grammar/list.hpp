
#ifndef XCPPB_PROTO_GRAMMAR_LIST_HPP
#define XCPPB_PROTO_GRAMMAR_LIST_HPP

#include <xcppb/proto/grammar/var.hpp>
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
struct list
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::proto::attribute::name()
	  >
{
	template< typename TokenDef >
	list
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::proto::attribute::name()
	> rule;

	var<Iterator> list_attributes;
	expression<Iterator> expression_;

	bool is_valid();
};

}

}

}

#endif
