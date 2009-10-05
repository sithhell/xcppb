
#ifndef XCPPB_AUTH_GET_AUTHPTR_HPP
#define XCPPB_AUTH_GET_AUTHPTR_HPP

#include <xcppb/auth/detail/get_addr.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <stdexcept>

#include <sys/socket.h>

#include <X11/Xauth.h>
#include <X11/Xdmcp.h>

namespace xcppb
{

namespace auth
{

namespace detail
{

enum
{
    FAMILY_INTERNET = 0,
    FAMILY_DECNET = 1,
    FAMILY_CHAOS = 2,
    FAMILY_SERVER_INTERPRETED = 5,
    FAMILY_INTERNET_6 = 6
};

enum
{
	AUTH_XA1,
	AUTH_MC1,
	N_AUTH_PROTOS
};

static char AUTH_PROTO_XDM_AUTHORIZATION[] = "XDM-AUTHORIZATION-1";
static char AUTH_PROTO_MIT_MAGIC_COOKIE[] =  "MIT-MAGIC-COOKIE-1";

static char *authnames[] = {
    AUTH_PROTO_XDM_AUTHORIZATION,
    AUTH_PROTO_MIT_MAGIC_COOKIE,
};

static int authnameslen[] = {
    sizeof(AUTH_PROTO_XDM_AUTHORIZATION) - 1,
    sizeof(AUTH_PROTO_MIT_MAGIC_COOKIE) - 1,
};

template< typename EndpointType >
Xauth *get_authptr( const EndpointType &endpoint, int display )
{
	unsigned short family( 256 ); // FamilyLocal

	switch( endpoint.protocol().family() )
	{
		case AF_INET6:
			family = detail::FAMILY_INTERNET_6;
			break;
		case AF_INET:
			family = detail::FAMILY_INTERNET;
			break;
		case AF_UNIX:
			break;
		default:
			throw std::runtime_error( "cannot athenticate this family ..." );
	}

	std::string addr( get_addr( endpoint ) );

	std::string disp_str( boost::lexical_cast< std::string >( display ) );

	return XauGetBestAuthByAddr
		(
			family,
			addr.size(), addr.c_str(),
			disp_str.size(), disp_str.c_str(),
			N_AUTH_PROTOS, authnames, authnameslen
		);
}

} // end namespace detail
	
} // end namespace auth

} // end namespace xcppb

#endif
