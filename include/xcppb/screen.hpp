
#ifndef XCPPB_SCREEN_HPP
#define XCPPB_SCREEN_HPP

#include <xcppb/padding.hpp>
#include <xcppb/detail/screen_data.hpp>

namespace xcppb
{

class screen
{
	public:
		screen( char *&data, size_t &index );

		static size_t padding( size_t index )
		{
			return xcppb::padding<detail::screen_data>( index );
		};

	private:
		detail::screen_data data_;
};

}
#endif
