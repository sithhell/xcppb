
#ifndef XCPPB_SCREEN_HPP
#define XCPPB_SCREEN_HPP

//#include <xcppb/padding.hpp>
//#include <xcppb/detail/screen_data.hpp>
#include <xcppb/window.hpp>
#include <xcppb/colormap.hpp>
#include <xcppb/visualid.hpp>

#include <xcppb/data/object.hpp>
#include <xcppb/data/pad.hpp>

#include <boost/cstdint.hpp>
#include <boost/mpl/vector.hpp>

#include <iostream>

namespace xcppb
{

class screen
{
	public:
		struct data
		{
			MAKE_ELEMENT( root                 , window );
			MAKE_ELEMENT( default_colormap     , colormap );
			MAKE_ELEMENT( white_pixel          , uint32_t );
			MAKE_ELEMENT( black_pixel          , uint32_t );
			MAKE_ELEMENT( current_input_masks  , uint32_t );
			MAKE_ELEMENT( width_in_pixels      , uint16_t );
			MAKE_ELEMENT( height_in_pixels     , uint16_t );
			MAKE_ELEMENT( width_in_millimeters , uint16_t );
			MAKE_ELEMENT( height_in_millimeters, uint16_t );
			MAKE_ELEMENT( min_installed_maps   , uint16_t );
			MAKE_ELEMENT( max_installed_maps   , uint16_t );
			MAKE_ELEMENT( root_visual          , visualid );
			MAKE_ELEMENT( backing_stores       , uint8_t );
			MAKE_ELEMENT( save_unders          , uint8_t );
			MAKE_ELEMENT( root_depth           , uint8_t );
			MAKE_ELEMENT( allowed_depths_len   , uint8_t );

			typedef xcppb::data::object
			<
				boost::mpl::vector
				<
					root,
					default_colormap,
					white_pixel,    
					black_pixel,         
					current_input_masks,
					width_in_pixels, 
					height_in_pixels,     
					width_in_millimeters,
					height_in_millimeters,
					min_installed_maps,
					max_installed_maps,  
					root_visual,  
					backing_stores,
					save_unders,
					root_depth,
					allowed_depths_len
				>
			> screen;
		};
		screen( const data::screen& s );

		void print( std::ostream& os ) const;

	private:
		data::screen data_;
};

std::ostream& operator<<( std::ostream& os, const screen& s );

}
#endif
