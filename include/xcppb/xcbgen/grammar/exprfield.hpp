
#ifndef XCPPB_PROTO_GRAMMAR_EXPRFIELD_HPP
#define XCPPB_PROTO_GRAMMAR_EXPRFIELD_HPP

#include <xcppb/xcbgen/grammar/var.hpp>
#include <xcppb/xcbgen/grammar/expression.hpp>

#include <xcppb/xcbgen/attribute/exprfield.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct exprfield
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	, xcppb::xcbgen::attribute::exprfield()
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
		, xcppb::xcbgen::attribute::exprfield()
	> rule;

	var<Iterator>        var_;
	expression<Iterator> expression_;

	bool is_valid();
};

}

}

}

#endif
