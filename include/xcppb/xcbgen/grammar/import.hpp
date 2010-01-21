
#ifndef XCPPB_PROTO_GRAMMAR_IMPORT_HPP
#define XCPPB_PROTO_GRAMMAR_IMPORT_HPP

#include <xcppb/xcbgen/attribute/import.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct import
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	, xcppb::xcbgen::attribute::import()
	  >
{
	template< typename TokenDef >
	import
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
	  	, xcppb::xcbgen::attribute::import()
	> rule;

	bool is_valid();
};

}

}

}

#endif
