
#ifndef XCPPB_PROTO_GRAMMAR_VAR_HPP
#define XCPPB_PROTO_GRAMMAR_VAR_HPP


#include <xcppb/xcbgen/grammar/attribute.hpp>

#include <xcppb/xcbgen/attribute/var.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct var
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	, xcppb::xcbgen::attribute::var()
	  >
{
	template< typename TokenDef >
	var
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		, xcppb::xcbgen::attribute::var()
	> rule;

	attribute<Iterator> name;
	attribute<Iterator> type;
	attribute<Iterator> enum_attr;
	attribute<Iterator> altenum;
	attribute<Iterator> mask;

	bool is_valid();
};

}

}

}

#endif
