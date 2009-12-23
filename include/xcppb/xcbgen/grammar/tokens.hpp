
#ifndef XCPPB_PROTO_LEXER_HPP
#define XCPPB_PROTO_LEXER_HPP

#include <string>

#include <boost/spirit/include/lex.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>


namespace lex = boost::spirit::lex;
namespace phoenix = boost::phoenix;

namespace xcppb
{

namespace xcbgen
{

namespace grammar
{

template< typename Lexer >
struct tokens
	: lex::lexer<Lexer>
{
	tokens();

	lex::token_def<std::string>
		attribute,
		element
		;

	lex::token_def<lex::omit>
		attribute_begin,
		attribute_end,
		prolog,
		xcb_begin,
		xcb_end,
		header,
		extension_xname,
		extension_name,
		extension_multiword,
		major_version,
		minor_version,
		pad,
		bytes,
		field,
		name,
		type,
		enum_attr,
		altenum,
		mask,
		list_begin,
		list_end,
		op_begin,
		op_end,
		op_attr,
		fieldref_begin,
		fieldref_end,
		value_begin,
		value_end,
		bit_begin,
		bit_end,
		exprfield_begin,
		exprfield_end,
		valueparam,
		value_mask_type,
		value_mask_name,
		value_list_name,
		number,
		ref,
		request_begin,
		request_end,
		opcode,
		combine_adjacent,
		reply_begin,
		reply_end,
		event_begin,
		event_end,
		no_sequence_number,
		eventcopy,
		error_begin,
		error_end,
		errorcopy,
		struct_begin,
		struct_end,
		union_begin,
		union_end,
		xidtype,
		xidunion_begin,
		xidunion_end,
		type_begin,
		type_end,
		enum_begin,
		enum_end,
		item_begin,
		item_end,
		typedef_,
		oldname,
		newname,
		import_begin,
		import_end,
		close_tag,
		;
	lex::token_def<char> any;
};

typedef std::string::const_iterator base_iterator_type;

typedef boost::spirit::lex::lexertl::token
<
	base_iterator_type,
	boost::mpl::vector
	<
		boost::spirit::lex::omit,
		std::string,
		char
	>
> token_type;

typedef boost::spirit::lex::lexertl::actor_lexer
<
	token_type
> lexer_type;

typedef tokens< lexer_type > lexer_tokens;

typedef lexer_tokens::iterator_type iterator_type;

} // end namespace grammar

} // end namespace xcbgen

} // end namespace lexer

#endif
