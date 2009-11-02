
#include <xcppb/screen.hpp>

#include <iostream>

#include <cstring>

namespace xcppb
{

screen::screen( const data::screen& s )
	: data_( s )
{
}

void screen::print( std::ostream& os ) const
{
	os	<< "Resolution: " 
		<< +data_.get< data::width_in_pixels >() 
		<< "x" 
		<< +data_.get< data::height_in_pixels >() 
		<< " ("
		<< +data_.get< data::width_in_millimeters >() 
		<< "x" 
		<< +data_.get< data::height_in_millimeters >()
		<< " ) Depth: "
		<< +data_.get< data::root_depth >();

}

std::ostream& operator<<( std::ostream& os, const screen& s )
{
	s.print( os );

	return os;
}

}
