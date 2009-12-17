
#ifndef XCPPB_PROTO_GRAMMAR_REQUEST_HPP
#define XCPPB_PROTO_GRAMMAR_REQUEST_HPP

#include <xcppb/proto/grammar/attribute.hpp>
#include <xcppb/proto/grammar/fields.hpp>
#include <xcppb/proto/grammar/exprfield.hpp>
#include <xcppb/proto/grammar/valueparam.hpp>
#include <xcppb/proto/grammar/reply.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace proto
{

namespace grammar
{

template< typename Iterator >
struct request
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::proto::attribute::request()
	  >
{
	template< typename TokenDef >
	request
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::proto::attribute::request()
	> rule;

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::proto::attribute::request()
	> attributes;

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::proto::attribute::request()
	> elements;

	attribute<Iterator> name;
	attribute<Iterator> opcode;
	attribute<Iterator> combine_adjacent;

	fields<Iterator>     fields_;
	exprfield<Iterator>  exprfield_;
	valueparam<Iterator> valueparam_;
	reply<Iterator>      reply_;

	bool is_valid();
};

}

}

}

#endif
