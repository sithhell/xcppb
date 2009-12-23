
#ifndef XCPPB_PROTO_GRAMMAR_BIT_HPP
#define XCPPB_PROTO_GRAMMAR_BIT_HPP

#include <xcppb/xcbgen/attribute/bit.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct bit
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, int()
	  	, xcppb::xcbgen::attribute::bit()
	  >
{
	template< typename TokenDef >
	bit
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, int()
	  	, xcppb::xcbgen::attribute::bit()
	> rule;
	
	bool is_valid();
};

}

}

}

#endif
