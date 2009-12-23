
#ifndef XCPPB_PROTO_GRAMMAR_ITEM_HPP
#define XCPPB_PROTO_GRAMMAR_ITEM_HPP

#include <xcppb/xcbgen/grammar/attribute.hpp>
#include <xcppb/xcbgen/grammar/expression.hpp>

#include <xcppb/xcbgen/attribute/item.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct item
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	, xcppb::xcbgen::attribute::item()
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
	  	, xcppb::xcbgen::attribute::item()
	> rule;

	attribute<Iterator>  name;
	expression<Iterator> expression_;

	       bool is_valid();
};

}

}

}

#endif
