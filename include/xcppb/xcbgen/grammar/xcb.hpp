
#ifndef XCPPB_PROTO_GRAMMAR_XCB_HPP
#define XCPPB_PROTO_GRAMMAR_XCB_HPP

#include <xcppb/xcbgen/grammar/attribute.hpp>
#include <xcppb/xcbgen/grammar/macro.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct xcb
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//, xcb::xcbgen::attribute::xcb()
	  >
{
	template< typename TokenDef >
	xcb
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, xcppb::xcbgen::attribute::xcb()
	> rule;

	boost::spirit::qi::rule
	<
		  Iterator
		//,
	> attributes;

	attribute<Iterator> header;
	attribute<Iterator> extension_xname;
	attribute<Iterator> extension_name;
	attribute<Iterator> extension_multiword;
	attribute<Iterator> major_version;
	attribute<Iterator> minor_version;
	macro<Iterator>     macros;

	       bool is_valid();
};

}

}

}

#endif
