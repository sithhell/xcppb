
#ifndef XCPPB_PROTO_GRAMMAR_TYPEDEF_HPP
#define XCPPB_PROTO_GRAMMAR_TYPEDEF_HPP

#include <xcppb/xcbgen/grammar/attribute.hpp>

#include <xcppb/xcbgen/attribute/typedef.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct typedef_
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	, xcppb::xcbgen::attribute::typedef_
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
	  	, xcppb::xcbgen::attribute::typedef_
	> rule;

	boost::spirit::qi::rule
	<
		  Iterator
	  	, xcppb::xcbgen::attribute::typedef_
	> attributes;

	attribute<Iterator> oldname;
	attribute<Iterator> newname;

	       bool is_valid();
};

}

}

}

#endif
