
#ifndef XCPPB_PROTO_GRAMMAR_FIELDS_HPP
#define XCPPB_PROTO_GRAMMAR_FIELDS_HPP

#include <xcppb/proto/grammar/pad.hpp>
#include <xcppb/proto/grammar/field.hpp>
#include <xcppb/proto/grammar/list.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace proto
{

namespace grammar
{

template< typename Iterator >
struct fields
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::proto::attribute::fields()
	  >
{
	template< typename TokenDef >
	fields
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::proto::attribute::fields()
	> rule;

	pad<Iterator>   pad_;
	field<Iterator> field_;
	list<Iterator>  list_;

	bool is_valid();
};

}

}

}

#endif
