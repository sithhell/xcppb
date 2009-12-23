
#ifndef XCPPB_PROTO_GRAMMAR_ATTRIBUTE_HPP
#define XCPPB_PROTO_GRAMMAR_ATTRIBUTE_HPP


#include <boost/spirit/home/lex/lexer/token_def.hpp>
#include <boost/spirit/home/qi/nonterminal/grammar.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

#include <string>

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Iterator >
struct attribute
	: boost::spirit::qi::grammar
	  <
	  	  Iterator
	  	, std::string()
	  >
{
	template< typename TokenDef >
	attribute
	(
	 	  TokenDef const & tok
		, boost::spirit::lex::token_def
		<
		  	boost::spirit::lex::omit
		> const & attribute_tok
	);

	boost::spirit::qi::rule
	<
		  Iterator
		, std::string()
	> rule;

	       bool is_valid();
};

}

}

}

#endif
