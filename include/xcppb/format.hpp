
#ifndef XCPPB_FORMAT_HPP
#define XCPPB_FORMAT_HPP

#include <xcppb/data/object.hpp>
#include <xcppb/data/pad.hpp>

#include <boost/cstdint.hpp>
#include <boost/mpl/vector.hpp>

#include <iostream>

namespace xcppb
{

class format
{
	public:
		struct data
		{
			MAKE_ELEMENT( depth         , uint8_t );
			MAKE_ELEMENT( bits_per_pixel, uint8_t );
			MAKE_ELEMENT( scanline_pad  , uint8_t );

			typedef xcppb::data::object
			<
				boost::mpl::vector
				<
					depth,
					bits_per_pixel,
					scanline_pad,
					xcppb::data::pad< uint8_t, 5 >
				>
			> format;
		};

		format( const data::format& f );

		void print( std::ostream& os ) const;

	private:
		//detail::format_data data_;
		data::format data_;
};

std::ostream& operator<<( std::ostream& os, const format& f );

} // end namespace xcppb
#endif
