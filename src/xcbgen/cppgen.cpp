
#include <xcppb/xcbgen/grammar.hpp>

#include <boost/spirit/include/lex.hpp>
#include <boost/spirit/include/lex_lexer.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>

#include <string>
#include <iostream>
#include <fstream>

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

namespace spirit = boost::spirit;
namespace qi = boost::spirit::qi;
namespace lex = boost::spirit::lex;
namespace ascii = boost::spirit::ascii;

int main( int /*argc*/, char **argv )
{

	typedef std::string::const_iterator base_iterator_type;

	typedef lex::lexertl::token
	<
		base_iterator_type,
		boost::mpl::vector
		<
			lex::omit,
			std::string,
			char
		>
	> token_type;

	typedef lex::lexertl::actor_lexer< token_type > lexer_type;

	typedef xcppb::xcbgen::tokens< lexer_type > xcbgen_tokens;

	typedef xcbgen_tokens::iterator_type iterator_type;

	typedef xcppb::xcbgen::grammar< iterator_type /*, xcbgen_lexer::lexer_def*/ > xcbgen_grammar;
	//typedef xcppb::xcbgen::grammar< base_iterator_type > xcbgen_grammar;

	xcbgen_tokens tokens;
	xcbgen_grammar xcbgen( tokens );
	//xcbgen_grammar xcbgen;

	std::string str( read_from_file( argv[1] ) );

	/*std::string::iterator it = str.begin();
	iterator_type iter = tokens.begin( it, str.end() );
	iterator_type end = tokens.end();*/

	base_iterator_type start( str.begin() );
	base_iterator_type end( str.end() );

	xcppb::xcbgen::xcb xcb;

	//bool r = qi::phrase_parse( start, end, xcbgen, ascii::space );
	bool r = lex::tokenize_and_parse( start, end, tokens, xcbgen
			, xcb
			);

	if( r )
	{
		std::cout << "header: " << xcb.header() << "\n";
		std::cout << "extension_xname: " << xcb.extension_xname() << "\n";
		std::cerr << "success\n";
	}
	else
	{
		std::cerr << "fail\n";
	}

	return 0;
}
