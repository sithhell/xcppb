
#ifndef XCPPB_PROTO_GRAMMAR_VAR_HPP
#define XCPPB_PROTO_GRAMMAR_VAR_HPP


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
struct var
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::proto::attribute::var()
	  >
{
	template< typename TokenDef >
	var
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::proto::attribute::var()
	> rule;

	attribute<Iterator> name;
	attribute<Iterator> type;
	attribute<Iterator> enum_attr;
	attribute<Iterator> altenum;
	attribute<Iterator> mask;

	bool is_valid();
};

}

}

}

#endif
