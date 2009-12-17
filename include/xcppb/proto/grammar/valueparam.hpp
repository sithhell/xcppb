
#ifndef XCPPB_PROTO_GRAMMAR_VALUEPARAM_HPP
#define XCPPB_PROTO_GRAMMAR_VALUEPARAM_HPP

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
struct valueparam
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::proto::attribute::valueparam()
	  >
{
	template< typename TokenDef >
	valueparam
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::proto::attribute::valueparam()
	> rule;

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::proto::attribute::valueparam()
	> attributes;

	attribute<Iterator> value_mask_type;
	attribute<Iterator> value_mask_name;
	attribute<Iterator> value_list_name;

	bool is_valid();
};

}

}

}

#endif
