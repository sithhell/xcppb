
#ifndef XCPPB_PROTO_GRAMMAR_XIDTYPE_HPP
#define XCPPB_PROTO_GRAMMAR_XIDTYPE_HPP

#include <xcppb/xcbgen/grammar/attribute.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct xidtype
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	, std::string()
	  >
{
	template< typename TokenDef >
	xidtype
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		, std::string()
	> rule;

	attribute<Iterator> name;

	bool is_valid();
};

}

}

}

#endif
