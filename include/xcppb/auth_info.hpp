
#ifndef XCPPB_AUTH_INFO_HPP
#define XCPPB_AUTH_INFO_HPP

#include <xcppb/detail/get_authptr.hpp>

#include <string>
#include <vector>

#include <boost/system/error_code.hpp>

#include <X11/Xauth.h>

namespace xcppb
{

class auth_info
{
	public:
		template< typename SocketType >
		explicit auth_info( const SocketType &s, int display = 0 );

		const std::string &name() const
		{
			return name_;
		}

		const std::vector<char> &data() const
		{
			return data_;
		}

	private:
		std::string 			name_;
		std::vector< char > 	data_;

		void compute_auth( Xauth *authptr );
};


template< typename SocketType >
auth_info::auth_info( const SocketType &s, int display )
{
	typedef typename SocketType::endpoint_type endpoint_type;

	boost::system::error_code error;
	endpoint_type endpoint( s.remote_endpoint( error ) );
	if( error )
	{
		if( endpoint.protocol().family() != AF_UNIX )
		{
			throw std::runtime_error( "cannot set auth info ..." );
		}

		endpoint = s.local_endpoint( error );
		if( error )
		{
			throw std::runtime_error( error.message() );
		}
	}

	Xauth *authptr = detail::get_authptr( endpoint, display );
	assert( authptr );

	name_ = std::string( authptr->name, authptr->name + authptr->name_length );

	compute_auth( authptr );

	// TODO: complete error handling ...

	XauDisposeAuth( authptr );
}

} // end namespace xcppb

#endif
