
#include <xcppb/proto/tokens_ctor.hpp>

namespace lex = boost::spirit::lex;
namespace phoenix = boost::phoenix;

namespace
{

void instantiate_my_tokens()
{
	lex::token_def< std::string > strings;

	lex::token_def< lex::omit   > tags;
	lex::token_def< char        > any;

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

	xcppb::proto::tokens< lexer_type > l;
}

}
