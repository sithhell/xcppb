
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
		prolog              = "<\\?xml.+?\\?>";
		xcb_begin           = "<xcb";
		xcb_end             = "<[/]xcb>";
		header              = "header";
		extension_xname     = "extension\\-xname";
		extension_name      = "extension\\-name";
		extension_multiword = "extension\\-multiword";
		major_version       = "major\\-version";
		minor_version       = "minor\\-version";
		pad                 = "<pad";
		bytes               = "bytes";
		field		           = "<field";
		name                = "name";
		type                = "type";
		enum_attr           = "enum";
		altenum             = "altenum";
		mask                = "mask";
		list_begin          = "<list";
		list_end            = "<[/]list>";
		op                  = "<op";
		op_attr             = "op";
		op_attr_val			  = "[+\\-\\*/]|&amp;|&lt;|&lt;";
		fieldref_begin      = "<fieldref";
		fieldref_end        = "<[/]fieldref>";
		value_begin         = "<value";
		value_end           = "<[/]value>";
		bit_begin           = "<bit";
		bit_end             = "<[/]bit>";
		exprfield_begin     = "<exprfield";
		exprfield_end       = "<[/]exprfield>";
		valueparam          = "<valueparam";
		value_mask_type     = "value\\-mask\\-type";
		value_mask_name     = "value\\-mask\\-name";
		value_list_name     = "value\\-list\\-name";
		number              = "number";
		ref                 = "ref";
		request_begin       = "<request";
		request_end         = "<[/]request>";
		opcode              = "opcode";
		combine_adjacent    = "combine\\-adjacent";
		reply_begin         = "<reply";
		reply_end           = "<[/]reply>";
		event_begin         = "<event";
		event_end           = "<[/]event>";
		no_sequence_number  = "no\\-sequence\\-number";
		eventcopy_begin     = "<eventcopy";
		eventcopy_end       = "<[/]eventcopy>";
		error_begin     	  = "<error";
		error_end           = "<[/]error>";
		errorcopy_begin     = "<errorcopy";
		errorcopy_end       = "<[/]errorcopy>";
		struct_begin        = "<struct";
		struct_end          = "<[/]struct>";
		union_begin         = "<union";
		union_end           = "<[/]union>";
		xidtype             = "<xidtype";
		xidunion_begin      = "<xidunion";
		xidunion_end        = "<[/]xidunion>";
		type_begin          = "<type";
		type_end            = "<[/]type>";
		enum_begin          = "<enum";
		enum_end            = "<[/]enum>";
		item_begin          = "<item";
		item_end            = "<[/]item>";
		typedef_begin       = "<typedef";
		typedef_end         = "<[/]typedef>";
		oldname             = "oldname";
		newname             = "newname";

		ws        = "[ \t\n]";
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
			| list
			| op
			| op_attr
			| op_attr_val
			| fieldref
			| value
			| bit
			| exprfield
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
			| eventcopy_begin
			| eventcopy_end
			| error_begin
			| error_end
			| errorcopy_begin
			| errorcopy_end
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
			| typedef_begin
			| typedef_end
			| oldname
			| newname
			| '='
			| '"'
			| '/'
			| '>'
			| ws
			| any
			;
	}
	lex::token_def<char>
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
		list,
		op,
		op_attr,
		op_attr_val,
		fieldref,
		value,
		bit,
		exprfield,
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
		eventcopy_begin,
		eventcopy_end,
		error_begin,
		error_end,
		errorcopy_begin,
		errorcopy_end,
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
		typedef_begin,
		typedef_end,
		oldname,
		newname,
		ws
		;
	lex::token_def<char> any;
};

} // end namespace proto

} // end namespace lexer

#endif
