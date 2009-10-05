
#ifndef XCPPB_CONNECTION_HPP
#define XCPPB_CONNECTION_HPP

#include <xcppb/setup/object.hpp>

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

		void print( std::ostream &os ) const;

	private:
		SocketType &s_;

		xcppb::setup::object setup_;
};

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
