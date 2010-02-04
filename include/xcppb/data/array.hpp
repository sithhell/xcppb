
#ifndef XCPPB_DATA_ARRAY_HPP
#define XCPPB_DATA_ARRAY_HPP

namespace xcppb
{
namespace data
{

template< typename T, unsigned int N >
struct array
{
	typedef T type[N];
};

}

}

#endif
