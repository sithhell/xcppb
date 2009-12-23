
#include <xcppb/xcbgen/grammar/xcb.hpp>
#include <xcppb/xcbgen/grammar/tokens.hpp>

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

inline bool compile( std::string const & str )
{
	using namespace xcppb::xcbgen::grammar;

	lexer_tokens t;
	xcb< iterator_type > xcb_grammar( t );

	/*std::string::iterator it = str.begin();
	iterator_type iter = tokens.begin( it, str.end() );
	iterator_type end = tokens.end();*/

	base_iterator_type start( str.begin() );
	base_iterator_type end( str.end() );

	bool r = lex::tokenize_and_parse( start, end, t, xcb_grammar
			//, xcb
			);
	
	if( r )
	{
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
