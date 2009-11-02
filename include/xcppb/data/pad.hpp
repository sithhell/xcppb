
#ifndef XCPPB_DATA_PAD_HPP
#define XCPPB_DATA_PAD_HPP

namespace xcppb
{
namespace data
{

template< typename T, unsigned int N >
struct pad
{
	typedef T type[N];
};

} // end namespace data

} // end namespace xcppb

#endif
