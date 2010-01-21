
#ifndef XCPPB_PROTO_GRAMMAR_EVENT_HPP
#define XCPPB_PROTO_GRAMMAR_EVENT_HPP

#include <xcppb/xcbgen/grammar/attribute.hpp>
#include <xcppb/xcbgen/grammar/fields.hpp>

#include <xcppb/xcbgen/attribute/event.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

#include <boost/fusion/include/vector30.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct event
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	, xcppb::xcbgen::attribute::event()
	  >
{
	template< typename TokenDef >
	event
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
	  	, xcppb::xcbgen::attribute::event()
	> rule;

	boost::spirit::qi::rule
	<
		  Iterator
		, xcppb::xcbgen::attribute::event::attributes()
		//, boost::fusion::vector3< std::string, std::string, std::string >()
	> attributes;

	attribute<Iterator> name;
	attribute<Iterator> number;
	attribute<Iterator> no_sequence_number;
	fields<Iterator>    fields_;

	       bool is_valid();
};

}

}

}

#endif
