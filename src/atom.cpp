
#include <xcppb/atom.hpp>

namespace xcppb
{

std::pair
<
	atom::data::request,
	std::vector<char>
> atom::request() const
{
	static char pad[] = {0, 0, 0};
	data::request r;

	std::vector<char> data;

	r.set< data::major_opcode >( 16 );
	r.set< data::only_if_exist >( 0 );
	r.set< data::name_len >( static_cast< uint16_t >( name_.size() ) );

	std::copy( pad, pad + ( -r.size() & 3 ), std::back_inserter( data ) );
	std::copy( name_.begin(), name_.end(), std::back_inserter( data ) );
	std::copy( pad, pad + ( -name_.size() & 3 ), std::back_inserter( data ) );

	return make_pair( r, data );
}

} // end namespace
