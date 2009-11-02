
#ifndef XCPPB_GENERIC_REPLY_HPP
#define XCPPB_GENERIC_REPLY_HPP

#include <xcppb/data/object.hpp>
#include <xcppb/data/pad.hpp>

#include <boost/cstdint.hpp>
#include <boost/mpl/vector.hpp>

namespace xcppb
{
	// wrapper class for a generic reply
	//
	// wraps access to elements of the data structure
	// NOTE: only use while data object is valid.
	//       Dangling reference hazard!
	class generic_reply
	{
		MAKE_ELEMENT( response_type_, uint8_t );
		MAKE_ELEMENT( sequence_     , uint16_t );
		MAKE_ELEMENT( length_       , uint32_t );
		
		public:
			typedef xcppb::data::object
			<
				boost::mpl::vector
				<
					response_type_,
					xcppb::data::pad< uint8_t, 1 >,
					sequence_,
					length_,
					xcppb::data::pad< uint32_t, 6 >
				>
			> data;

			enum
			{
				ERROR = 0,
				REPLY = 1
			};

			generic_reply( const data& d )
				: d_( d )
			{}

			unsigned type() const
			{
				return d_.get< response_type_ >();
			};
			unsigned sequence() const
			{
				return d_.get< sequence_ >();
			}
			unsigned length() const
			{
				return d_.get< length_ >();
			}

		private:
			const data &d_;
	};
} // end namespace xcppb

#endif
