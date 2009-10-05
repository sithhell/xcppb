
#include <xcppb/screen.hpp>

#include <iostream>

#include <cstring>

namespace xcppb
{

screen::screen( char *&data, size_t &index )
{
	std::memcpy( &data_, data, sizeof( detail::screen_data ) );

	data += sizeof( detail::screen_data );
	index += sizeof( detail::screen_data );
}

}
