
#ifndef XCPPB_PROTO_GRAMMAR_FIELDREF_HPP
#define XCPPB_PROTO_GRAMMAR_FIELDREF_HPP

#include <xcppb/xcbgen/attribute/fieldref.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct fieldref
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	, xcppb::xcbgen::attribute::fieldref()
	  >
{
	template< typename TokenDef >
	fieldref
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
	  	, xcppb::xcbgen::attribute::fieldref()
	> rule;

	bool is_valid();
};

}

}

}

#endif
