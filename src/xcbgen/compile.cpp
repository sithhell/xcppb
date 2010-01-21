
#include <xcppb/xcbgen/grammar/xcb.hpp>
#include <xcppb/xcbgen/grammar/tokens.hpp>

#include <boost/spirit/include/karma.hpp>

#include <string>
#include <iostream>
#include <fstream>

namespace karma = boost::spirit::karma;

template < typename OutputIterator >
struct generator
	: karma::grammar
	<
		  OutputIterator
		, xcppb::xcbgen::attribute::xcb()
	>
{
	generator()
		: generator::base_type( xcb )
	{
		xcb_attributes
			=  karma::lit( "header = \"" ) << karma::string << "\"\n"
			<< -( "extension xname = \"" << karma::string << "\"\n" )
			<< -( "extension name = \"" << karma::string << "\"\n" )
			<< -( "extension multiword = \"" << karma::string << "\"\n" )
			<< -( "major_version = \"" << karma::string << "\"\n" )
			<< -( "minor version = \"" << karma::string << "\"\n" )
			;

		xcb
			=  xcb_attributes
			<< *macro
			<< "over and out\n"
			;

		macro
			= request
			| karma::lit( "\txidtype = \"" ) << karma::string << "\"\n"
			| typedef_
			;

		request
			= karma::lit( "\trequest:\n" )
			<< request_attributes
			<< request_elements
			<< -( reply )
			;

		request_attributes
			=  karma::lit( "\tname = \"" ) << karma::string << "\"\n"
			<< "\topcode = \"" << karma::string << "\"\n"
			<< -( "\tcombine_adjacent = \"" << karma::string << "\"\n" )
			;

		request_elements
			= *(
				  fields
				| exprfield
				| valueparam
				)
			;

		fields 
			=  karma::lit( "\t\tpadding = \"" ) << karma::uint_
			| var
			| list
			;

		var
			= karma::lit( "\t\t variable: \n" )
			<< "\t\tname = \"" << karma::string << "\"\n"
			<< "\t\ttype = \"" << karma::string << "\"\n"
			<< -( "\t\tenum_attr = \"" << karma::string << "\"\n" )
			<< -( "\t\taltenum = \"" << karma::string << "\"\n" )
			<< -( "\t\tmask = \"" << karma::string << "\"\n" )
			;

		list
			= var
			<< -expression
			;
/*
		exprfield
			= karma::lit( "\t\texpression field" )
			;

		valueparam
			= karma::lit( "\t\tvalueparam" )
			;

		typedef_
			=  karma::lit( "\ttypedef:\nold=\"" )
			<< karma::string
			<< "\" new=\"" << karma::string << "\"\n"
			;*/
	}

	karma::rule
	<
		  OutputIterator
		, xcppb::xcbgen::attribute::xcb::attributes_t()
	> xcb_attributes;
	
	karma::rule
	<
		  OutputIterator
		, xcppb::xcbgen::attribute::xcb()
	> xcb;
	
	karma::rule
	<
		  OutputIterator
		, xcppb::xcbgen::attribute::macro()
	> macro;
	
	karma::rule
	<
		  OutputIterator
		, xcppb::xcbgen::attribute::request()
	> request;
	
	karma::rule
	<
		  OutputIterator
		, xcppb::xcbgen::attribute::request::attributes_t()
	> request_attributes;
	
	karma::rule
	<
		  OutputIterator
		, std::vector< xcppb::xcbgen::attribute::request::element >()
	> request_elements;
	
	karma::rule
	<
		  OutputIterator
		, xcppb::xcbgen::attribute::fields()
	> fields;
	
	karma::rule
	<
		  OutputIterator
		, xcppb::xcbgen::attribute::var()
	> var;
	
	karma::rule
	<
		  OutputIterator
		, xcppb::xcbgen::attribute::list()
	> list;
	
	karma::rule
	<
		  OutputIterator
		, xcppb::xcbgen::attribute::exprfield()
	> exprfield;
	
	karma::rule
	<
		  OutputIterator
		, xcppb::xcbgen::attribute::valueparam()
	> valueparam;
	
	karma::rule
	<
		  OutputIterator
		, xcppb::xcbgen::attribute::reply()
	> reply;

	karma::rule
	<
		  OutputIterator
		, xcppb::xcbgen::attribute::typedef_()
	> typedef_;
};



inline std::string 
read_from_file(char const* infile)
{
    std::ifstream instream(infile);
    if (!instream.is_open()) {
        std::cerr << "Couldn't open file: " << infile << std::endl;
        exit(-1);
    }
    instream.unsetf(std::ios::skipws);      // No white space skipping!
    return std::string(std::istreambuf_iterator<char>(instream.rdbuf()),
                       std::istreambuf_iterator<char>());
}

inline bool compile( std::string const & str )
{
	using namespace xcppb::xcbgen;

	grammar::lexer_tokens t;
	grammar::xcb< grammar::iterator_type > xcb_grammar( t );

	/*std::string::iterator it = str.begin();
	iterator_type iter = tokens.begin( it, str.end() );
	iterator_type end = tokens.end();*/

	grammar::base_iterator_type start( str.begin() );
	grammar::base_iterator_type end( str.end() );

	attribute::xcb xcb_attribute;

	bool r = lex::tokenize_and_parse( start, end, t, xcb_grammar
			, xcb_attribute
			);
	
	if( r )
	{
		typedef std::back_insert_iterator<std::string> sink_type;
		std::string generated;
		sink_type sink( generated );

		generator< sink_type > g;
		karma::generate( sink, g, xcb_attribute );

		std::cout << generated << "\n";

		//std::cout << "header: " << xcb.header() << "\n";
		//std::cout << "extension_xname: " << xcb.extension_xname() << "\n";
		std::cerr << "success\n";
	}
	else
	{
		std::cerr << "fail\n";
	}

	return true;
}

int main( int, char **argv )
{
	compile( read_from_file( argv[1] ) );
}
