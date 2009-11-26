
#ifndef XCPPB_PROTO_LEXER_HPP
#define XCPPB_PROTO_LEXER_HPP

#include <boost/spirit/include/lex.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/home/phoenix.hpp>

namespace lex = boost::spirit::lex;
namespace phoenix = boost::phoenix;

namespace xcppb
{

namespace proto
{

template< typename Lexer >
struct tokens
	: lex::lexer<Lexer>
{
	tokens()
	{
		this->self.add_pattern
			( "WS", "[ \t\n]" )
			;

		attribute = "[^o]*?";
		this->self( "ATTRIBUTE_VALUE" ).add( attribute );

		prolog              = "{WS}*<\\?xml.+?\\?>{WS}*";
		xcb_begin           = "{WS}*<xcb{WS}+";
		xcb_end             = "{WS}*<[/]xcb>{WS}*";
		header              = "{WS}*header{WS}*";
		extension_xname     = "{WS}*extension\\-xname{WS}*";
		extension_name      = "{WS}*extension\\-name{WS}*";
		extension_multiword = "{WS}*extension\\-multiword{WS}*";
		major_version       = "{WS}*major\\-version{WS}*";
		minor_version       = "{WS}*minor\\-version{WS}*";
		pad                 = "{WS}*<pad{WS}+";
		bytes               = "{WS}*bytes{WS}*";
		field               = "{WS}*<field{WS}+";
		name                = "{WS}*name{WS}*";
		type                = "{WS}*type{WS}*";
		enum_attr           = "{WS}*enum{WS}*";
		altenum             = "{WS}*altenum{WS}*";
		mask                = "{WS}*mask{WS}*";
		list_begin          = "{WS}*<list{WS}+";
		list_end            = "{WS}*<[/]list>{WS}*";
		op                  = "{WS}*<op{WS}+";
		op_attr             = "{WS}*op{WS}*";
		op_attr_val         = "[+\\-\\*/]|&amp;|&lt;|&lt;";
		fieldref_begin      = "{WS}*<fieldref>{WS}*";
		fieldref_end        = "{WS}*<[/]fieldref>{WS}*";
		value_begin         = "{WS}*<value>{WS}*";
		value_end           = "{WS}*<[/]value>{WS}*";
		bit_begin           = "{WS}*<bit>{WS}*";
		bit_end             = "{WS}*<[/]bit>{WS}*";
		exprfield_begin     = "{WS}*<exprfield{WS}+";
		exprfield_end       = "{WS}*<[/]exprfield>{WS}*";
		valueparam          = "{WS}*<valueparam{WS}+";
		value_mask_type     = "{WS}*value\\-mask\\-type{WS}*";
		value_mask_name     = "{WS}*value\\-mask\\-name{WS}*";
		value_list_name     = "{WS}*value\\-list\\-name{WS}*";
		number              = "{WS}*number{WS}*";
		ref                 = "{WS}*ref{WS}*";
		request_begin       = "{WS}*<request{WS}+";
		request_end         = "{WS}*<[/]request>{WS}*";
		opcode              = "{WS}*opcode{WS}*";
		combine_adjacent    = "{WS}*combine\\-adjacent{WS}*";
		reply_begin         = "{WS}*<reply{WS}+";
		reply_end           = "{WS}*<[/]reply>{WS}*";
		event_begin         = "{WS}*<event{WS}+";
		event_end           = "{WS}*<[/]event>{WS}*";
		no_sequence_number  = "{WS}*no\\-sequence\\-number{WS}*";
		eventcopy           = "{WS}*<eventcopy{WS}+";
		error_begin         = "{WS}*<error{WS}+";
		error_end           = "{WS}*<[/]error>{WS}*";
		errorcopy           = "{WS}*<errorcopy{WS}+";
		struct_begin        = "{WS}*<struct{WS}+";
		struct_end          = "{WS}*<[/]struct>{WS}*";
		union_begin         = "{WS}*<union{WS}+";
		union_end           = "{WS}*<[/]union>{WS}*";
		xidtype             = "{WS}*<xidtype{WS}+";
		xidunion_begin      = "{WS}*<xidunion{WS}+";
		xidunion_end        = "{WS}*<[/]xidunion>{WS}*";
		type_begin          = "{WS}*<type>{WS}*";
		type_end            = "{WS}*<[/]type>{WS}*";
		enum_begin          = "{WS}*<enum{WS}+";
		enum_end            = "{WS}*<[/]enum>{WS}*";
		item_begin          = "{WS}*<item{WS}+";
		item_end            = "{WS}*<[/]item>{WS}*";
		typedef_            = "{WS}*<typedef{WS}+";
		oldname             = "{WS}*oldname{WS}*";
		newname             = "{WS}*newname{WS}*";
		import_begin        = "{WS}*<import{WS}+";
		import_end          = "{WS}*<[/]import>{WS}*";

		close_tag = "{WS}*>|{WS}*[/]>";
		ws        = "{WS}";
		any       = ".";

		this->self
			= prolog
			| xcb_begin
			| xcb_end
			| header
			| extension_xname
			| extension_name
			| extension_multiword
			| major_version
			| minor_version
			| pad
			| bytes
			| field
			| name
			| type
			| enum_attr
			| altenum
			| mask
			| list_begin
			| list_end
			| op
			| op_attr
			| op_attr_val
			| fieldref_begin
			| fieldref_end
			| value_begin
			| value_end
			| bit_begin
			| bit_end
			| exprfield_begin
			| exprfield_end
			| valueparam
			| value_mask_type
			| value_mask_name
			| value_list_name
			| number
			| ref
			| request_begin
			| request_end
			| opcode
			| combine_adjacent
			| reply_begin
			| reply_end
			| event_begin
			| event_end
			| no_sequence_number
			| eventcopy
			| error_begin
			| error_end
			| errorcopy
			| struct_begin
			| struct_end
			| union_begin
			| union_end
			| xidtype
			| xidunion_begin
			| xidunion_end
			| type_begin
			| type_end
			| enum_begin
			| enum_end
			| item_begin
			| item_end
			| typedef_
			| oldname
			| newname
			| import_begin
			| import_end
			| close_tag
			| '='
			| '"'
			/*| "[/]"
			| '>'*/
			| ws
			| any
			;
	}
	lex::token_def<>
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
		op,
		op_attr,
		op_attr_val,
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
		ws
		;
	lex::token_def<char> any, attribute;
};

} // end namespace proto

} // end namespace lexer

#endif
