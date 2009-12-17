
#ifndef XCPPB_PROTO_GRAMMAR_PACKET_STRUCT_COPY_HPP
#define XCPPB_PROTO_GRAMMAR_PACKET_STRUCT_COPY_HPP

#include <xcppb/proto/grammar/attribute.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace proto
{

namespace grammar
{

template< typename Iterator >
struct packet_struct_copy
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::proto::attribute::packet_struct_copy()
	  >
{
	template< typename TokenDef >
	packet_struct_copy
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::proto::attribute::packet_struct_copy()
	> rule;

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::proto::attribute::packet_struct_copy()
	> attributes;

	attribute<Iterator> name;
	attribute<Iterator> number;
	attribute<Iterator> ref;

	       bool is_valid();
};

}

}

}

#endif
