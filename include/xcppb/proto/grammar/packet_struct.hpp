
#ifndef XCPPB_PROTO_GRAMMAR_PACKET_STRUCT_HPP
#define XCPPB_PROTO_GRAMMAR_PACKET_STRUCT_HPP

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
struct packet_struct
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::proto::attribute::packet_struct()
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
		//, xcppb::proto::attribute::packet_struct()
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
