
#include <xcppb/proto/grammar.hpp>

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

	typedef xcppb::proto::tokens< lexer_type > proto_tokens;

	typedef proto_tokens::iterator_type iterator_type;

	typedef xcppb::proto::grammar< iterator_type /*, proto_lexer::lexer_def*/ > proto_grammar;
	//typedef xcppb::proto::grammar< base_iterator_type > proto_grammar;

	proto_tokens tokens;
	proto_grammar proto( tokens );
	//proto_grammar proto;

	std::string str( read_from_file( argv[1] ) );

	/*std::string::iterator it = str.begin();
	iterator_type iter = tokens.begin( it, str.end() );
	iterator_type end = tokens.end();*/

	base_iterator_type start( str.begin() );
	base_iterator_type end( str.end() );

	xcppb::proto::xcb xcb;

	//bool r = qi::phrase_parse( start, end, proto, ascii::space );
	bool r = lex::tokenize_and_parse( start, end, tokens, proto
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
