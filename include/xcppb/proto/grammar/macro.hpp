
#ifndef XCPPB_PROTO_GRAMMAR_MACRO_HPP
#define XCPPB_PROTO_GRAMMAR_MACRO_HPP

#include <xcppb/proto/grammar/request.hpp>
#include <xcppb/proto/grammar/event.hpp>
#include <xcppb/proto/grammar/struct.hpp>
#include <xcppb/proto/grammar/union.hpp>
#include <xcppb/proto/grammar/xidtype.hpp>
#include <xcppb/proto/grammar/xidunion.hpp>
#include <xcppb/proto/grammar/enum.hpp>
#include <xcppb/proto/grammar/typedef.hpp>
#include <xcppb/proto/grammar/import.hpp>
#include <xcppb/proto/grammar/packet_struct.hpp>
#include <xcppb/proto/grammar/packet_struct_copy.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace proto
{

namespace grammar
{

template< typename Iterator >
struct macro
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//,
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
		//, 
	> rule;

	boost::spirit::qi::rule
	<
		  Iterator
		//, 
	> eventcopy;

	boost::spirit::qi::rule
	<
		  Iterator
		//, 
	> error;

	boost::spirit::qi::rule
	<
		  Iterator
		//, 
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
