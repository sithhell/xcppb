
#ifndef XCPPB_PROTO_GRAMMAR_EXPRESSION_HPP
#define XCPPB_PROTO_GRAMMAR_EXPRESSION_HPP

#include <xcppb/proto/grammar/fieldref.hpp>
#include <xcppb/proto/grammar/value.hpp>
#include <xcppb/proto/grammar/bit.hpp>
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
struct expression
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::proto::attribute::expression()
	  >
{
	template< typename TokenDef >
	expression
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::proto::attribute::expression()
	> rule;

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::proto::attribute::expression()
	> op;

	fieldref<Iterator> fieldref_;
	value<Iterator>    value_;
	bit<Iterator>      bit_;
	attribute< Iterator > op_attribute;

	bool is_valid();
};

}

}

}

#endif
