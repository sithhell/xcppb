
#ifndef XCPPB_PROTO_GRAMMAR_EXPRFIELD_HPP
#define XCPPB_PROTO_GRAMMAR_EXPRFIELD_HPP

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
struct exprfield
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::proto::attribute::exprfield()
	  >
{
	template< typename TokenDef >
	exprfield
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::proto::attribute::exprfield()
	> rule;

	var<Iterator>        var_;
	expression<Iterator> expression_;

	bool is_valid();
};

}

}

}

#endif
