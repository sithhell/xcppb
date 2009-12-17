
#ifndef XCPPB_PROTO_GRAMMAR_REPLY_HPP
#define XCPPB_PROTO_GRAMMAR_REPLY_HPP

#include <xcppb/proto/grammar/fields.hpp>
#include <xcppb/proto/grammar/valueparam.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace proto
{

namespace grammar
{

template< typename Iterator >
struct reply
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::proto::attribute::reply()
	  >
{
	template< typename TokenDef >
	reply
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::proto::attribute::reply()
	> rule;

	fields<Iterator>     fields_;
	valueparam<Iterator> valueparam_;

	       bool is_valid();
};

}

}

}

#endif
