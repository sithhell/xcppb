
#ifndef XCPPB_PADDING_HPP
#define XCPPB_PADDING_HPP

#include <cstddef>

namespace xcppb
{
/*
size_t padding( size_t size )
{
	return ( -size & 3 );
}*/

// replacement for XCB_*PAD
template< typename T >
size_t padding( size_t i )
{
	return ( -i & ( sizeof( T ) > 4 ? 3 : sizeof( T ) - 1 ) );
}

} // end of namespace xcppb

#endif
