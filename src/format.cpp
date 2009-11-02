
#include <xcppb/format.hpp>

#include <cstring>


namespace xcppb
{

format::format( const data::format& f )
	: data_( f )
{
}

void format::print( std::ostream& os ) const
{
	os << "Depth: " << +data_.get< data::depth >() << ", Bits per pixel: " << +data_.get< data::bits_per_pixel >();
}

std::ostream& operator<<( std::ostream& os, const format& f )
{
	f.print( os );

	return os;
}

} // end namespace xcppb
