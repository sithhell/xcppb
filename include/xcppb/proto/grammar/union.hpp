
#ifndef XCPPB_PROTO_GRAMMAR_UNION_HPP
#define XCPPB_PROTO_GRAMMAR_UNION_HPP

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
struct union_
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::proto::attribute::union_()
	  >
{
	template< typename TokenDef >
	union_
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::proto::attribute::union_()
	> rule;

	attribute<Iterator> name;
	fields<Iterator>    fields_;

	bool is_valid();
};

}

}

}

#endif
