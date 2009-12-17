
#ifndef XCPPB_PROTO_GRAMMAR_EVENT_HPP
#define XCPPB_PROTO_GRAMMAR_EVENT_HPP

#include <xcppb/proto/grammar/attribute.hpp>
#include <xcppb/proto/grammar/fields.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace proto
{

namespace grammar
{

template< typename Iterator >
struct event
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//,
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
		//, 
	> rule;

	boost::spirit::qi::rule
	<
		  Iterator
		//, 
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
