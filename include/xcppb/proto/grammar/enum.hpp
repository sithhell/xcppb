
#ifndef XCPPB_PROTO_GRAMMAR_ENUM_HPP
#define XCPPB_PROTO_GRAMMAR_ENUM_HPP

#include <xcppb/proto/grammar/attribute.hpp>
#include <xcppb/proto/grammar/item.hpp>

#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

namespace xcppb
{

namespace proto
{

namespace grammar
{

template< typename Iterator >
struct enum_
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	//,
	  >
{
	template< typename TokenDef >
	enum_
	(
	 	  TokenDef const & tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		//, 
	> rule;

	attribute<Iterator> name;
	item<Iterator>      item_;

	       bool is_valid();
};

}

}

}

#endif
