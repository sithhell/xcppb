
#ifndef XCPPB_CONNECTION_HPP
#define XCPPB_CONNECTION_HPP

#include <xcppb/setup.hpp>

#include <boost/asio/buffer.hpp>

namespace xcppb
{

template< typename SocketType >
class connection
{
	public:
		typedef SocketType socket;

		connection( SocketType &s )
			: s_( s ),
			  setup_( s )
		{}

		void flush();
		
		size_t maximum_request_length() const;
		void prefetch_maximum_request_length() const;

		/*xcppb::event wait_for_event();
		xcppb::event poll_for_event();

		xcppb::extension::reply extension_data( xcppb::extension::object );
		xcppb::extension::reply prefetch_extension_data( xcppb::extension::object );*/

		xcppb::setup &setup() const;

		uint32_t generate_id() const;

		void print( std::ostream &os ) const;

	private:
		SocketType &s_;

		xcppb::setup setup_;
};

template< typename SocketType >
void connection<SocketType>::flush()
{
	// returns when all data si written.
	char buf[1];
	s_.write_some( buf );
}

template< typename SocketType >
void connection<SocketType>::print( std::ostream &os ) const
{
	os << setup_;
}

template< typename SocketType >
std::ostream &operator<< ( std::ostream &os, const connection<SocketType>& c )
{
	c.print( os );
	return os;
}


} // end of namespace xcppb

#endif
