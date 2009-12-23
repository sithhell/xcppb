
#ifndef XCPPB_PROTO_GRAMMAR_FIELD_HPP
#define XCPPB_PROTO_GRAMMAR_FIELD_HPP

#include <xcppb/xcbgen/grammar/var.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct field
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	, xcppb::xcbgen::attribute::var()
	  >
{
	template< typename TokenDef >
	field
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		, xcppb::xcbgen::attribute::var()
	> rule;

	var<Iterator> field_attributes;

	bool is_valid();
};

}

}

}

#endif
