
#ifndef XCPPB_PROTO_GRAMMAR_PAD_HPP
#define XCPPB_PROTO_GRAMMAR_PAD_HPP

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
struct pad
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, boost::uint32_t()
	  >
{
	template< typename TokenDef >
	pad
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
	  	//, boost::uint32_t()
	> rule;

	attribute<Iterator> bytes;

	bool is_valid();
};

}

}

}

#endif
