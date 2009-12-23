
#ifndef XCPPB_PROTO_GRAMMAR_LIST_HPP
#define XCPPB_PROTO_GRAMMAR_LIST_HPP

#include <xcppb/xcbgen/grammar/var.hpp>
#include <xcppb/xcbgen/grammar/expression.hpp>

#include <xcppb/xcbgen/attribute/list.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct list
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	, xcppb::xcbgen::attribute::list()
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
	  	, xcppb::xcbgen::attribute::list()
	> rule;

	var<Iterator> list_attributes;
	expression<Iterator> expression_;

	bool is_valid();
};

}

}

}

#endif
