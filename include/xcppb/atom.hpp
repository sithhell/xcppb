
#ifndef XCPPB_ATOM_HPP
#define XCPPB_ATOM_HPP

//#include <xcppb/protocol_request.hpp>
#include <xcppb/data/object.hpp>
#include <xcppb/data/pad.hpp>

#include <xcppb/generic_reply.hpp>

#include <boost/cstdint.hpp>
#include <boost/mpl/vector.hpp>

#include <algorithm>
#include <utility>
#include <vector>
#include <string>

#include <iostream>

#include <cassert>

namespace xcppb
{

class atom
{
	public:
		struct data
		{
			MAKE_ELEMENT( major_opcode, uint8_t );
			MAKE_ELEMENT( only_if_exist, uint8_t );
			MAKE_ELEMENT( length, uint16_t );
			MAKE_ELEMENT( name_len, uint16_t );

			typedef xcppb::data::object
			<
				boost::mpl::vector
				<
					major_opcode,
					only_if_exist,
					length,
					name_len,
					xcppb::data::pad< uint8_t, 2 >
				>
			> request;

			MAKE_ELEMENT( response_type, uint8_t );
			MAKE_ELEMENT( sequence     , uint16_t );
			MAKE_ELEMENT( reply_length , uint32_t );
			MAKE_ELEMENT( atom         , uint32_t );
			typedef xcppb::data::object
			<
				boost::mpl::vector
				<
					response_type,
					xcppb::data::pad< uint8_t, 1 >,
					sequence,
					reply_length,
					atom,
					xcppb::data::pad< uint32_t, 5 >
				>
			> reply;
		};

		atom( const std::string& name )
			: valid( false ),
			  name_( name )
		{}

		std::pair
		<
			data::request,
			std::vector<char>
		> request() const
		{
			static char pad[] = {0, 0, 0};
			data::request r;

			std::vector<char> data;

			r.set< data::major_opcode >( 16 );
			r.set< data::only_if_exist >( 0 );
			r.set< data::name_len >( static_cast< uint16_t >( name_.size() ) );

			std::copy( pad, pad + ( -r.size() & 3 ), std::back_inserter( data ) );
			std::copy( name_.begin(), name_.end(), std::back_inserter( data ) );
			std::copy( pad, pad + ( -name_.size() & 3 ), std::back_inserter( data ) );

			return make_pair( r, data );
		}

		atom& construct( const generic_reply::data& rd )
		{
			data::reply d( rd );

			atom_id = d.get< data::atom >();

			valid = true;
			return *this;
		}

		uint32_t id() const
		{
			assert( valid );

			return atom_id;
		}

	private:
		bool valid;
		std::string name_;

		uint32_t atom_id;
};

} // end of namespace xcppb

#endif
