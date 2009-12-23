
#ifndef XCPPB_PROTO_GRAMMAR_VALUE_HPP
#define XCPPB_PROTO_GRAMMAR_VALUE_HPP

#include <xcppb/xcbgen/attribute/value.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct value
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	, xcppb::xcbgen::attribute::value()
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
	  	, xcppb::xcbgen::attribute::value()
	> rule;

	bool is_valid();
};

}

}

}

#endif
