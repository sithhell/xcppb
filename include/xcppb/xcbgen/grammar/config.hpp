
#ifndef XCPPB_PROTO_CONFIG_HPP
#define XCPPB_PROTO_CONFIG_HPP

#include <boost/spirit/include/lex.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>

#include <string>

namespace xcppb
{
	namespace xcbgen
	{
		namespace grammar
		{

			//template< typename > struct tokens;

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
		}
	}
}

#endif
