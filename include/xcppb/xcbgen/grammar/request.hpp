
#ifndef XCPPB_PROTO_GRAMMAR_REQUEST_HPP
#define XCPPB_PROTO_GRAMMAR_REQUEST_HPP

#include <xcppb/xcbgen/grammar/attribute.hpp>
#include <xcppb/xcbgen/grammar/fields.hpp>
#include <xcppb/xcbgen/grammar/exprfield.hpp>
#include <xcppb/xcbgen/grammar/valueparam.hpp>
#include <xcppb/xcbgen/grammar/reply.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct request
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::xcbgen::attribute::request()
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
		//, xcppb::xcbgen::attribute::request()
	> rule;

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::xcbgen::attribute::request()
	> attributes;

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::xcbgen::attribute::request()
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
