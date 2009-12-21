
#include <xcppb/proto/tokens.hpp>

namespace lex = boost::spirit::lex;
namespace phoenix = boost::phoenix;

namespace xcppb
{

namespace proto
{

template< typename Lexer >
tokens<Lexer>::tokens()
{
	this->self.add_pattern
		( "COMMENT", "\"<!--\"[^-]*\"-\"([^-]+\"-\")*\"->\"" )
		( "WS"     , "[ \t\n]|{COMMENT}")
		;
		

	this->self( "ATTRIBUTE_VALUE" )
		= ( attribute     = "[^\\\"']+" )
		| ( attribute_end = "(\\\"|'){WS}*" ) 
			[
				lex::_state = "INITIAL"
			]
		;

	element        = "([^<]|{COMMENT})+";
	this->self( "ELEMENT_VALUE" )
		= ( element = "([^<]|{COMMENT})+" )
		|   lex::token_def<>( '<' )
			[
				lex::_state = "INITIAL"
			]
		;

	this->self
		= ( prolog              = "{WS}*<\\?xml.+?\\?>{WS}*" )
		| ( xcb_begin           = "{WS}*<xcb{WS}+" )
		| ( xcb_end             = "{WS}*<[/]xcb>{WS}*" )
		| ( header              = "{WS}*header{WS}*" )
		| ( extension_xname     = "{WS}*extension\\-xname{WS}*" )
		| ( extension_name      = "{WS}*extension\\-name{WS}*" )
		| ( extension_multiword = "{WS}*extension\\-multiword{WS}*" )
		| ( major_version       = "{WS}*major\\-version{WS}*" )
		| ( minor_version       = "{WS}*minor\\-version{WS}*" )
		| ( pad                 = "{WS}*<pad{WS}+" )
		| ( bytes               = "{WS}*bytes{WS}*" )
		| ( field               = "{WS}*<field{WS}+" )
		| ( name                = "{WS}*name{WS}*" )
		| ( type                = "{WS}*type{WS}*" )
		| ( enum_attr           = "{WS}*enum{WS}*" )
		| ( altenum             = "{WS}*altenum{WS}*" )
		| ( mask                = "{WS}*mask{WS}*" )
		| ( list_begin          = "{WS}*<list{WS}+" )
		| ( list_end            = "{WS}*<[/]list>{WS}*" )
		| ( op_begin            = "{WS}*<op{WS}+" )
		| ( op_end              = "{WS}*<[/]op>{WS}*" )
		| ( op_attr             = "{WS}*op{WS}*" )
		| ( fieldref_begin      = "{WS}*<fieldref>{WS}*" )
			[
				lex::_state = "ELEMENT_VALUE"
			]
		| ( fieldref_end        = "{WS}*[/]fieldref>{WS}*" )
		| ( value_begin         = "{WS}*<value>{WS}*" )
			[
				lex::_state = "ELEMENT_VALUE"
			]
		| ( value_end           = "{WS}*[/]value>{WS}*" )
		| ( bit_begin           = "{WS}*<bit>{WS}*" )
			[
				lex::_state = "ELEMENT_VALUE"
			]
		| ( bit_end             = "{WS}*[/]bit>{WS}*" )
		| ( exprfield_begin     = "{WS}*<exprfield{WS}+" )
		| ( exprfield_end       = "{WS}*<[/]exprfield>{WS}*" )
		| ( valueparam          = "{WS}*<valueparam{WS}+" )
		| ( value_mask_type     = "{WS}*value\\-mask\\-type{WS}*" )
		| ( value_mask_name     = "{WS}*value\\-mask\\-name{WS}*" )
		| ( value_list_name     = "{WS}*value\\-list\\-name{WS}*" )
		| ( number              = "{WS}*number{WS}*" )
		| ( ref                 = "{WS}*ref{WS}*" )
		| ( request_begin       = "{WS}*<request{WS}+" )
		| ( request_end         = "{WS}*<[/]request>{WS}*" )
		| ( opcode              = "{WS}*opcode{WS}*" )
		| ( combine_adjacent    = "{WS}*combine\\-adjacent{WS}*" )
		| ( reply_begin         = "{WS}*<reply>{WS}*" )
		| ( reply_end           = "{WS}*<[/]reply>{WS}*" )
		| ( event_begin         = "{WS}*<event{WS}+" )
		| ( event_end           = "{WS}*<[/]event>{WS}*" )
		| ( no_sequence_number  = "{WS}*no\\-sequence\\-number{WS}*" )
		| ( eventcopy           = "{WS}*<eventcopy{WS}+" )
		| ( error_begin         = "{WS}*<error{WS}+" )
		| ( error_end           = "{WS}*<[/]error>{WS}*" )
		| ( errorcopy           = "{WS}*<errorcopy{WS}+" )
		| ( struct_begin        = "{WS}*<struct{WS}+" )
		| ( struct_end          = "{WS}*<[/]struct>{WS}*" )
		| ( union_begin         = "{WS}*<union{WS}+" )
		| ( union_end           = "{WS}*<[/]union>{WS}*" )
		| ( xidtype             = "{WS}*<xidtype{WS}+" )
		| ( xidunion_begin      = "{WS}*<xidunion{WS}+" )
		| ( xidunion_end        = "{WS}*<[/]xidunion>{WS}*" )
		| ( type_begin          = "{WS}*<type>{WS}*" )
			[
				lex::_state = "ELEMENT_VALUE"
			]
		| ( type_end            = "{WS}*[/]type>{WS}*" )
		| ( enum_begin          = "{WS}*<enum{WS}+" )
		| ( enum_end            = "{WS}*<[/]enum>{WS}*" )
		| ( item_begin          = "{WS}*<item{WS}+" )
		| ( item_end            = "{WS}*<[/]item>{WS}*" )
		| ( typedef_            = "{WS}*<typedef{WS}+" )
		| ( oldname             = "{WS}*oldname{WS}*" )
		| ( newname             = "{WS}*newname{WS}*" )
		| ( import_begin        = "{WS}*<import>{WS}*" )
			[
				lex::_state = "ELEMENT_VALUE"
			]
		| ( import_end          = "{WS}*[/]import>{WS}*" )
		| ( close_tag           = "{WS}*>|{WS}*[/]>{WS}*" )
		| ( attribute_begin     = "{WS}*(\\\"|')" )
			[
				lex::_state = "ATTRIBUTE_VALUE"
			]
		|   lex::token_def<>( '=' )
		| ( any = "." )
		;
}

}

}
