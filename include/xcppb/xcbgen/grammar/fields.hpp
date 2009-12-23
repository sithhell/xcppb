
#ifndef XCPPB_PROTO_GRAMMAR_FIELDS_HPP
#define XCPPB_PROTO_GRAMMAR_FIELDS_HPP

#include <xcppb/xcbgen/grammar/pad.hpp>
#include <xcppb/xcbgen/grammar/field.hpp>
#include <xcppb/xcbgen/grammar/list.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct fields
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::xcbgen::attribute::fields()
	  >
{
	template< typename TokenDef >
	fields
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::xcbgen::attribute::fields()
	> rule;

	pad<Iterator>   pad_;
	field<Iterator> field_;
	list<Iterator>  list_;

	bool is_valid();
};

}

}

}

#endif
