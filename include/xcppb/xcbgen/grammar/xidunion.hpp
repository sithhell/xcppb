
#ifndef XCPPB_PROTO_GRAMMAR_XIDUNION_HPP
#define XCPPB_PROTO_GRAMMAR_XIDUNION_HPP

#include <xcppb/xcbgen/grammar/attribute.hpp>

#include <xcppb/xcbgen/attribute/xidunion.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct xidunion
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
		//, std::vector< std::string >
	  	, xcppb::xcbgen::attribute::xidunion()
	  >
{
	template< typename TokenDef >
	xidunion
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, std::vector< std::string >
	  	, xcppb::xcbgen::attribute::xidunion()
	> rule;

	boost::spirit::qi::rule
	<
		  Iterator
		, std::string()
	> type;

	attribute<Iterator> name;

	       bool is_valid();
};

}

}

}

#endif
