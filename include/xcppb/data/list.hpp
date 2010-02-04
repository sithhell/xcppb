
#ifndef XCPPB_DATA_LIST_HPP
#define XCPPB_DATA_LIST_HPP

#include <boost/mpl/bool.hpp>

namespace xcppb
{
namespace data
{

template< typename Operation >
struct is_constant
{
	enum { value 
		=  is_constant< typename Operation::lhs >::value
		&& is_constant< typename Operation::rhs >::value
	};
};

template< typename Operation >
struct is_none
	: boost::mpl::false_
{
};

struct none
{
	enum { value = 0u };
};

template<>
struct is_none<none>
	: boost::mpl::true_
{
};

template<>
struct is_constant<none>
	: boost::mpl::false_
{
};

template< typename Reference >
struct field
{
	enum { value = 0u };
	typedef Reference ref;
};

template< typename Reference >
struct is_constant< field<Reference> >
	: boost::mpl::false_
{
};

template< unsigned int N >
struct constant
{
	enum { value = N };
};

template< unsigned int N >
struct is_constant< constant<N> >
	: boost::mpl::true_
{
};

template< typename Lhs, typename Rhs >
struct plus
{
	typedef Lhs lhs;
	typedef Rhs rhs;

	enum { value = Lhs::value + Rhs::value };
};

template< typename Lhs, typename Rhs >
struct minus
{
	typedef Lhs lhs;
	typedef Rhs rhs;

	enum { value = Lhs::value - Rhs::value };
};

template< typename Lhs, typename Rhs >
struct mult
{
	typedef Lhs lhs;
	typedef Rhs rhs;

	enum { value = Lhs::value * Rhs::value };
};

template< typename Lhs, typename Rhs >
struct div
{
	typedef Lhs lhs;
	typedef Rhs rhs;

	enum { value = Lhs::value / Rhs::value };
};

template< typename Lhs, typename Rhs >
struct and_
{
	typedef Lhs lhs;
	typedef Rhs rhs;

	enum { value = Lhs::value & Rhs::value };
};

template< typename Lhs, typename Rhs >
struct shift
{
	typedef Lhs lhs;
	typedef Rhs rhs;

	enum { value = Lhs::value << Rhs::value };
};

template< typename T, typename L = none >
struct list
{
	typedef T type;
	typedef L length;
};

template< typename T >
struct is_list
	: boost::mpl::false_
{
};

template< typename T, typename L >
struct is_list< list<T, L> >
	: boost::mpl::true_
{
};

}

}

#endif
