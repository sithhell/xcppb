
#ifndef XCPPB_CONNECTION_HPP
#define XCPPB_CONNECTION_HPP

#include <xcppb/setup.hpp>
#include <xcppb/cookie.hpp>
#include <xcppb/generic_reply.hpp>
#include <xcppb/event/generic.hpp>

#include <list>
#include <vector>

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
			  setup_( s ),
			  last_xid( 0 ),
			  last_sequence( 0 )
		{}

		void flush();
		
		size_t maximum_request_length() const;
		void prefetch_maximum_request_length() const;

		xcppb::event::generic wait_for_event();
		xcppb::event::generic poll_for_event();

		/*xcppb::extension::reply extension_data( xcppb::extension::object );
		xcppb::extension::reply prefetch_extension_data( xcppb::extension::object );*/

		xcppb::setup &setup() const;

		uint32_t generate_id() const;

		template< typename Type >
		cookie<Type> request( Type &t );
		template< typename Type >
		void reply( const cookie<Type> &c );

		void print( std::ostream &os ) const;

	private:
		void get_replies();

		SocketType &s_;

		xcppb::setup setup_;
		
		mutable uint32_t last_xid;

		unsigned int last_sequence;
		std::list< std::pair<unsigned int, std::vector<char> > > replies;
};

template< typename SocketType >
void connection<SocketType>::flush()
{
	// returns when all data is written.
	char buf[1];
	s_.write_some( buf );
}

/*template< typename SocketType >
xcppb::event::generic connection<SocketType>::wait_for_event()
{
}*/

template< typename SocketType >
uint32_t connection<SocketType>::generate_id() const
{
	// TODO: implement xc_misc extension
	if( last_xid > setup_.resource_id_mask() - 1 )
		assert( false );

	return  ++last_xid | setup_.resource_id_base() ;
}

template< typename SocketType >
template< typename Type >
cookie<Type> connection<SocketType>::request( Type& t )
{
	cookie<Type> c( ++last_sequence, t );
	// TODO: implement possible overflow of sequence
	assert( c.sequence() );

	std::pair
	<
		typename Type::data::request,
		std::vector<char>
	> request_data( t.request() );

	// set length field
	// TODO: Big requests!
	request_data.first.template set< typename Type::data::length >
	(
		static_cast< uint16_t >
		(
			request_data.first.size() + request_data.second.size()
		) / 4
	);

	// write reuest
	s_.write_some( boost::asio::buffer( request_data.first.begin(), request_data.first.size() ) );
	s_.write_some( boost::asio::buffer( request_data.second ) );
	
	//if( r.expect_reply() )
		replies.push_back( make_pair( c.sequence(), std::vector<char>() ) );

	return c;
}

template< typename SocketType >
template< typename Type >
void connection<SocketType>::reply( const cookie<Type>& c )
{
	typedef std::list< std::pair<unsigned int, std::vector<char> > >::iterator iterator;
					

	if( replies.empty() ) return;

	std::cout << "want: " << c.sequence() << "\n";
	iterator itr( replies.begin() );
	for( ; itr != replies.end(); ++itr )
	{
		// recieve data
		if( itr->second.size() == 0 )
		{
			generic_reply::data reply_data;
			std::cout << "wait ... \n";
			s_.read_some( boost::asio::buffer( reply_data.begin(), reply_data.size() ) );
			std::cout << "got one: " << itr->first << "\n";
			std::copy( reply_data.begin(), reply_data.end(), std::back_inserter( itr->second ) );
		}
		if( itr->first == c.sequence() )
			break;
	}

	generic_reply::data data;
	std::copy( itr->second.begin(), itr->second.end(), data.begin() );

	c.construct( data );
}

template< typename SocketType >
void connection<SocketType>::print( std::ostream &os ) const
{
	os << setup_;
}

template< typename SocketType >
void connection<SocketType>::get_replies()
{
}

template< typename SocketType >
std::ostream &operator<< ( std::ostream &os, const connection<SocketType>& c )
{
	c.print( os );
	return os;
}


} // end of namespace xcppb

#endif
