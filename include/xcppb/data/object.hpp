
#ifndef XCPPB_DATA_OBJECT_HPP
#define XCPPB_DATA_OBJECT_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/accumulate.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/greater_equal.hpp>
#include <boost/mpl/plus.hpp>

#include <cstring>

namespace xcppb
{
namespace data
{
	
namespace mpl = boost::mpl;
namespace placeholders = boost::mpl::placeholders;

// small macro to make creation of element types less verbose
#define MAKE_ELEMENT( name, t ) \
	struct name \
	{ \
		typedef t type; \
	}

//=============================================================================
/**\!brief container to store inhomogeneous pod data in a contigous way
 *
 * The main purpose of this class is to model C structs ( POD structs, only
 * containing data members ) to be able to easily searialize them.
 *
 * Example:
 * \code
 *
 * #include <xcppb/data/object.hpp>
 * #include <xcppb/data/pad.hpp>
 *
 * #include <boost/mpl/vector.hpp>
 * #include <boost/cstdint.hpp>
 *
 * // declare elements with the desired types
 * MAKE_ELEMENT( foo, uint32_t ) // declare foo with type uint32_t
 * MAKE_ELEMENT( bar, uint64_t ) // declare bar with type uint64_t
 * MAKE_ELEMENT( baz, uint32_t ) // declare baz with type uint8_t
 *
 * typedef data::object
 * <
 * 	boost::mpl::vector
 * 	<
 * 		foo,
 * 		pad< uint16_t, 2 >, // pad with two uint16_t
 * 		bar
 * 	>
 * > foobar_data;
 *
 * typedef data::object
 * <
 * 	boost::mpl::vector
 * 	<
 * 		baz
 * 	>
 * > baz_data;
 *
 * foobar_data d1;
 * baz_data    d2;
 *
 * d1.set<foo>( 42 ); // set element foo to 42, stores it as an uint32_t
 * d1.set<bar>( 23 ); // set element bar to 23, stores it as an uint32_t
 * d1.get<foo>();     // get element foo, returns 42
 *
 * d2.set<baz>( 64 ); // set element baz to 64
 *
 * d1 = d2;           // copy d2 to d1, only d2.size() bytes are copied to d1
 * assert( d1.get<foo>() == d2.get<baz>() );
 * assert( d1.get<bar>() == 23            );
 *
 * d2 = d1;           // error d1.size() > d2.size()
 * 						 // i.e. d1 doesn't entirly fit in d2, therefore this conversion is prohibited
 *
 * d1.set<baz>( 32 ); // error, this type is not in the container
 * \endcode
 */
template< typename Sequence >
class object
{

	template< typename > friend struct object;
	
	public:
		typedef typename mpl::accumulate
			<
				Sequence,
				mpl::int_<0>,
				mpl::plus
				<
					placeholders::_1,
					mpl::sizeof_
					<
						mpl::deref
						<
							placeholders::_2
						>
					>
				>
			>::type size_; //!< 

		typedef Sequence types; //!<
		typedef char type; //!<
		typedef char * iterator; //!<
		typedef char const* const_iterator; //!<

		/** !\brief default constructor
		 */
		object()
			: data_( new char[ size_::value ] )
		{
			memset( data_, 0, size_::value );
		}

		/** !\brief copy constructor for same data types
		 */
		object( const object& other )
			: data_( new char[ size_::value ] )
		{
			memset( data_, 0, size_::value );
			memcpy( data_, other.data_, size_::value );
		}

		/** !\brief copy constructor for different data types
		 *
		 * Note: The copy from different data types leads to a representation of the
		 * specified types. 
		 */
		template< typename OtherSequence >
		object( const object<OtherSequence>& other, 
				typename boost::enable_if
				<
					mpl::greater_equal
					<
						typename object<types>::size_,
						typename object<OtherSequence>::size_
					>,
					void *
				>::type = 0 )
			: data_( new char[ size_::value ] )
		{
			memset( data_, 0, size_::value );
			memcpy( data_, other.data_, size_::value );
		}

		/** !\brief default destructor
		 */
		~object()
		{
			delete[] data_;
		}

		/** !\brief assignment operator for same data types
		 */
		object& operator=( const object& other )
		{
			if( &other == this ) return *this;

			memcpy( data_, other.data_, size_::value );

			return *this;
		}

		/** !\brief assignment operator for different data types
		 *
		 * Note: The copy from different data types leads to a representation of the
		 * specified types. 
		 */
		template< typename OtherSequence >
		typename boost::enable_if
		<
			mpl::greater_equal
			<
				typename object<types>::size_,
				typename object<OtherSequence>::size_
			>,
			object&
		>::type operator=( const object<OtherSequence>& other )
		{
			memcpy( data_, other.data_, size_::value );

			return *this;
		}

		/** !\brief getter of specific element
		 */
		template< typename T >
		typename boost::enable_if
		<
			mpl::contains< types, T >,
			typename T::type
		>::type
		get() const
		{
			const unsigned int idx( element_pos<T>::value );
			typename T::type t;

			std::memcpy( &t, data_ + idx, sizeof( typename T::type ) );

			return t;
		}
		
		/** !\brief setter of specific element
		 */
		template< typename T >
		typename boost::enable_if
		<
			mpl::contains< types, T >
		>::type
		set( typename T::type t)
		{
			const unsigned int idx( element_pos<T>::value );
			
			std::memcpy( data_ + idx, &t, sizeof( typename T::type ) );
		}

		unsigned int length() const
		{
			return size_::value;
		}

		unsigned int size() const
		{
			return size_::value;
		}

		iterator begin()
		{
			return data_;
		}

		iterator end()
		{
			return data_ + size();
		}
		
		const_iterator begin() const
		{
			return data_;
		}

		const_iterator end() const
		{
			return data_ + size();
		}

	private:
		char *data_; //!< data buffer
		
		template< typename Type >
		struct element_pos
			: mpl::accumulate
			<
				mpl::iterator_range
				<
					typename mpl::begin< types >::type,
					typename mpl::find< types, Type >::type
				>,
				mpl::int_<0>,
				mpl::plus
				<
					placeholders::_1,
					mpl::sizeof_
					<
						mpl::deref
						<
							placeholders::_2
						>
					>
				>
			>::type
		{};

};

} // end namespace data

} // end namespace xcppb

#endif
