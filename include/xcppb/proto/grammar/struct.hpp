
#ifndef XCPPB_PROTO_GRAMMAR_STRUCT_HPP
#define XCPPB_PROTO_GRAMMAR_STRUCT_HPP

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
struct struct_
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::proto::attribute::struct_()
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
		//, xcppb::proto::attribute::struct_()
	> rule;

	attribute<Iterator> name;
	fields<Iterator>    fields_;

	       bool is_valid();
};

}

}

}

#endif
