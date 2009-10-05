
#ifndef XCPPB_FORMAT_HPP
#define XCPPB_FORMAT_HPP

#include <xcppb/padding.hpp>
#include <xcppb/detail/format_data.hpp>

namespace xcppb
{

class format
{
	public:
		format( char *&data, size_t &index );

		static size_t padding( size_t index )
		{
			return xcppb::padding<detail::format_data>( index );
		};

	private:
		detail::format_data data_;
};

}
#endif
