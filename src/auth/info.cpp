
#include <xcppb/auth/info.hpp>

#include <X11/Xdmcp.h>

#include <sys/socket.h>

namespace xcppb
{

namespace auth
{

void info::compute_auth( Xauth *authptr )
{
	if( name_ == std::string( detail::AUTH_PROTO_MIT_MAGIC_COOKIE ) )
	{
		data_.insert( data_.end(), authptr->data, authptr->data + authptr->data_length );
		return;
	}
	// TODO: implement rest ...
	throw std::logic_error( "not implemented yet ..." );
	if( name_ == std::string( detail::AUTH_PROTO_XDM_AUTHORIZATION ) )
	{
	}
}

} // end namespace auth

} // end namespace xcppb
