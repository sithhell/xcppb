
#ifndef XCPPB_PROTO_GRAMMAR_MACRO_HPP
#define XCPPB_PROTO_GRAMMAR_MACRO_HPP

#include <xcppb/xcbgen/grammar/request.hpp>
#include <xcppb/xcbgen/grammar/event.hpp>
#include <xcppb/xcbgen/grammar/struct.hpp>
#include <xcppb/xcbgen/grammar/union.hpp>
#include <xcppb/xcbgen/grammar/xidtype.hpp>
#include <xcppb/xcbgen/grammar/xidunion.hpp>
#include <xcppb/xcbgen/grammar/enum.hpp>
#include <xcppb/xcbgen/grammar/typedef.hpp>
#include <xcppb/xcbgen/grammar/import.hpp>
#include <xcppb/xcbgen/grammar/packet_struct.hpp>
#include <xcppb/xcbgen/grammar/packet_struct_copy.hpp>

#include <xcppb/xcbgen/attribute/macro.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct macro
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	, xcppb::xcbgen::attribute::macro()
	  >
{
	template< typename TokenDef >
	macro
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
	  	, xcppb::xcbgen::attribute::macro()
	> rule;

	boost::spirit::qi::rule
	<
		  Iterator
	  	, xcppb::xcbgen::attribute::packet_struct_copy()
	> eventcopy;

	boost::spirit::qi::rule
	<
		  Iterator
	  	, xcppb::xcbgen::attribute::packet_struct()
	> error;

	boost::spirit::qi::rule
	<
		  Iterator
	  	, xcppb::xcbgen::attribute::packet_struct_copy()
	> errorcopy;

	request<Iterator>  request_;
	event<Iterator>    event_;
	struct_<Iterator>  struct__;
	union_<Iterator>   union__;
	xidtype<Iterator>  xidtype_;
	xidunion<Iterator> xidunion_;
	enum_<Iterator>    enum__;
	typedef_<Iterator> typedef__;
	import<Iterator>   import_;
	packet_struct<Iterator> packet_struct_;
	packet_struct_copy<Iterator> packet_struct_copy_;

	       bool is_valid();
};

}

}

}

#endif
