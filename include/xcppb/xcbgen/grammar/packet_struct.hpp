
#ifndef XCPPB_PROTO_GRAMMAR_PACKET_STRUCT_HPP
#define XCPPB_PROTO_GRAMMAR_PACKET_STRUCT_HPP

#include <xcppb/xcbgen/grammar/attribute.hpp>
#include <xcppb/xcbgen/grammar/fields.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct packet_struct
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::xcbgen::attribute::packet_struct()
	  >
{
	template< typename TokenDef >
	packet_struct
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::xcbgen::attribute::packet_struct()
	> rule;

	attribute<Iterator> name;
	attribute<Iterator> number;
	fields<Iterator>    fields_;

	       bool is_valid();
};

}

}

}

#endif
