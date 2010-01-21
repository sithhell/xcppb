
#ifndef XCPPB_PROTO_GRAMMAR_STRUCT_HPP
#define XCPPB_PROTO_GRAMMAR_STRUCT_HPP

#include <xcppb/xcbgen/grammar/attribute.hpp>
#include <xcppb/xcbgen/grammar/fields.hpp>

#include <xcppb/xcbgen/attribute/struct.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct struct_
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	, xcppb::xcbgen::attribute::struct_()
	  >
{
	template< typename TokenDef >
	struct_
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		, xcppb::xcbgen::attribute::struct_()
	> rule;

	attribute<Iterator> name;
	fields<Iterator>    fields_;

	       bool is_valid();
};

}

}

}

#endif
