
#ifndef XCPPB_COOKIE_HPP
#define XCPPB_COOKIE_HPP

#include <xcppb/generic_reply.hpp>

#include <vector>

#include <boost/utility/enable_if.hpp>

namespace xcppb
{

/*
class generic_cookie
{
	public:
		virtual       std::vector<char> request() = 0;
		
		bool finished() const;

	private:
		unsigned int sequence;
		bool finished_;
};*/

template< typename Type >
class cookie
{
	public:
		//typedef typename Type::data::request request_type;

		explicit cookie( unsigned sequence, Type& t );

		cookie( const cookie& );
		//cookie( const Type& t );

		/*template< typename Connection >
		void request( Connection& c );

		// blocks until reply is received from the server
		template< typename Connection >
		const Type& reply( Connection& c );
		*/

		unsigned int sequence() const
		{
			return sequence_;
		}

		/*typename boost::enable_if
		<
			expect_reply
			<
				Type
			>
		>::type*/
		void construct( const generic_reply::data& data ) const
		{
			t_.construct( data );
		}

		/*unsigned int& sequence()
		{
			return sequence_;
		}*/

		/*std::pair
		<
			request_type,
			std::vector<char>
		> request() const
		{
			return t_.request();
		}*/

	private:
		unsigned int sequence_;
		bool finished_;

		Type& t_;
};


template< typename Type >
cookie<Type>::cookie( unsigned sequence, Type& t )
	: sequence_( sequence ),
	  finished_( false ),
	  t_( t )
{}

template< typename Type >
cookie<Type>::cookie( const cookie& c )
	: sequence_( c.sequence_ ),
	  finished_( c.finished_ ),
	  t_( c.t_ )
{}

#if 0
template< typename Type >
cookie<Type>::cookie( const Type& t )
	: sequence_( 0 ),
	  finished_( false ),
	  t_( t )
{}

/*
template< typename Type >
template< typename Connection >
void cookie<Type>::request( Connection& c )
{
	sequence = c.send_request( t_ );
}*/

template< typename Type >
template< typename Connection >
const Type& cookie<Type>::reply( Connection& c )
{
	/*const std::vector<char>& reply_data( c.get_reply( sequence ) );

	return t_.construct( reply_data );*/
}
#endif

} // end namespace xcppb

#endif
