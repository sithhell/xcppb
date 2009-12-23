
#ifndef XCPPB_PROTO_GRAMMAR_EXPRESSION_HPP
#define XCPPB_PROTO_GRAMMAR_EXPRESSION_HPP

#include <xcppb/xcbgen/grammar/fieldref.hpp>
#include <xcppb/xcbgen/grammar/value.hpp>
#include <xcppb/xcbgen/grammar/bit.hpp>
#include <xcppb/xcbgen/grammar/attribute.hpp>

#include <xcppb/xcbgen/attribute/expression.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct expression
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	, xcppb::xcbgen::attribute::expression()
	  >
{
	template< typename TokenDef >
	expression
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		, xcppb::xcbgen::attribute::expression()
	> rule;

	boost::spirit::qi::rule
	<
		  Iterator
		, xcppb::xcbgen::attribute::op()
	> op;

	fieldref<Iterator> fieldref_;
	value<Iterator>    value_;
	bit<Iterator>      bit_;
	attribute< Iterator > op_attribute;

	bool is_valid();

};

}

}

}

#endif
