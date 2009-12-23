
#ifndef XCPPB_PROTO_GRAMMAR_ENUM_HPP
#define XCPPB_PROTO_GRAMMAR_ENUM_HPP

#include <xcppb/xcbgen/grammar/attribute.hpp>
#include <xcppb/xcbgen/grammar/item.hpp>

#include <xcppb/xcbgen/attribute/enum.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct enum_
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	, xcppb::xcbgen::attribute::enum_()
	  >
{
	template< typename TokenDef >
	enum_
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
	  	, xcppb::xcbgen::attribute::enum_()
	> rule;

	attribute<Iterator> name;
	item<Iterator>      item_;

	bool is_valid();
};

}

}

}

#endif
