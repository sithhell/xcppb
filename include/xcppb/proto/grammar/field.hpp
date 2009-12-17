
#ifndef XCPPB_PROTO_GRAMMAR_FIELD_HPP
#define XCPPB_PROTO_GRAMMAR_FIELD_HPP

#include <xcppb/proto/grammar/var.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace proto
{

namespace grammar
{

template< typename Iterator >
struct field
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::proto::attribute::var()
	  >
{
	template< typename TokenDef >
	field
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::proto::attribute::var()
	> rule;

	var<Iterator> field_attributes;

	       bool is_valid();
	static void instantiate();
};

}

}

}

#endif
