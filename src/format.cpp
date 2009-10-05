
#include <xcppb/format.hpp>

#include <iostream>

#include <cstring>


namespace xcppb
{

format::format( char *&data, size_t &index )
{
	std::memcpy( &data_, data, sizeof( detail::format_data ) );

	data += sizeof( detail::format_data );
	index += sizeof( detail::format_data );
}

} // end namespace xcppb
