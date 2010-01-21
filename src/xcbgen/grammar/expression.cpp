
#include <xcppb/xcbgen/grammar/expression.hpp>

#include <xcppb/xcbgen/grammar/tokens.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/bind.hpp>

namespace
{

xcppb::xcbgen::attribute::op
make_op
(
	  std::string const & op_str
	, xcppb::xcbgen::attribute::expression const & left
	, xcppb::xcbgen::attribute::expression const & right
)
{
	xcppb::xcbgen::attribute::op o;

	o.left = left;
	o.right = right;

	
	if( op_str == "+" )
	{
		o.operation = xcppb::xcbgen::attribute::op::plus;
	}
	else if( op_str == "-" )
	{
		o.operation = xcppb::xcbgen::attribute::op::minus;
	}
	else if( op_str == "*" )
	{
		o.operation = xcppb::xcbgen::attribute::op::mult;
	}
	else if( op_str == "/" )
	{
		o.operation = xcppb::xcbgen::attribute::op::div;
	}
	else if( op_str == "&amp" )
	{
		o.operation = xcppb::xcbgen::attribute::op::and_;
	}
	else if( op_str == "&lt;&lt;" )
	{
		o.operation = xcppb::xcbgen::attribute::op::right_shift;
	}
	else
	{
		o.operation = xcppb::xcbgen::attribute::op::undefined;
	}

	return o;
}

}

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

namespace qi = boost::spirit::qi;
namespace lex = boost::spirit::lex;
namespace phoenix = boost::phoenix;


template< typename Iterator >
template< typename TokenDef >
expression<Iterator>::expression
(
	  TokenDef const & tok
)
	: expression::base_type( rule, "expression" )
	, fieldref_             ( tok )
	, value_                ( tok )
	, bit_                  ( tok )
	, op_attribute ( tok, tok.op_attr )
{
	rule.name( "expression" );
	rule
		%= fieldref_
		|  value_
		|  bit_
		|  op
		;
	
	op.name( "operation" );
	op
		=
		(
			tok.op_begin
			>  op_attribute
			> tok.close_tag
			>  rule
			>  rule
			> tok.op_end
		)[ qi::_val = phoenix::bind( ::make_op, qi::_1, qi::_2, qi::_3 ) ]
		;
}

template< typename Iterator >
bool expression<Iterator>::is_valid()
{
	return true;
}

} // end grammar

} // end xcbgen

} // end xcppb

namespace
{
	void instantiate()
	{
		using namespace xcppb::xcbgen::grammar;
		lexer_tokens t;
		expression<iterator_type> g( t );
	}
}
