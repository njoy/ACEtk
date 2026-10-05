#ifndef NJOY_ACETK_BASE_ARRAYDATA
#define NJOY_ACETK_BASE_ARRAYDATA

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief A block of data given as a number of arrays of equal length
 */
class ArrayData : protected Base {

  /* fields */

  unsigned int nelements_;
  unsigned int narrays_;

  /* auxiliary functions */

  void verifyIndex( const std::size_t index ) const {

    if ( ( index < 1 ) || ( index > this->M() ) ) {

      Log::error( "Illegal index argument into the {} block", this->name() );
      Log::info( "Index value: {}", index );
      Log::info( "{} accepts an index between {} and {} inclusively",
                 this->name(), 1, this->M() );
      throw std::out_of_range( this->name() );
    }
  }

  void verifyIndex( const std::size_t array, const std::size_t index ) const {

    verifyIndex( array );
    if ( ( index < 1 ) || ( index > this->N() ) ) {

      Log::error( "Illegal index argument into the {} block", this->name() );
      Log::info( "Index value: {}", index );
      Log::info( "{} accepts an index between {} and {} inclusively",
                 this->name(), 1, this->N() );
      throw std::out_of_range( this->name() );
    }
  }

  template < typename Number >
  static std::vector< double >
  generateXSS( std::vector< std::vector< Number > >&& arrays ) {

    std::vector< double > xss;
    if ( arrays.size() > 0 ) {

      const auto n = arrays.front().size();
      xss.reserve( arrays.size() * n );

      unsigned int index = 1;
      for ( auto&& array : arrays ) {

        if ( array.size() != n ) {

          Log::error( "The size of the array with index {} is not as expected", index );
          Log::info( "Expected: {}", n );
          Log::info( "Found: {}", array.size() );
          throw std::exception();
        }

        xss.insert( xss.end(), array.begin(), array.end() );
        ++index;
      }
    }

    return xss;
  }

  void verifySize( Iterator begin, Iterator end, unsigned int n, unsigned int m ) {

    // there are at least n * m values
    auto size = std::distance( begin, end );
    if ( size < n * m ) {

      Log::error( "The size of the XSS subrange in the {} block should be at "
                  "least {} * N", this->name(), m );
      Log::info( "N value: {}", n );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  /* constructor */

  template < typename Number >
  ArrayData( std::string&& name, std::vector< std::vector< Number > >&& values,
             unsigned int n, unsigned int m ) :
    Base( std::move( name ), generateXSS( std::move( values ) ) ),
    nelements_( n ), narrays_( m ) {}

public:

  /* constructor */

  ArrayData() = default;

  ArrayData( const ArrayData& ) = default;
  ArrayData( ArrayData&& ) = default;

  ArrayData& operator=( const ArrayData& ) = default;
  ArrayData& operator=( ArrayData&& ) = default;

  /**
   *  @brief Convenience constructor
   *
   *  @param[in] name     the name of the block
   *  @param[in] values   the values
   */
  template < typename Number >
  ArrayData( std::string&& name, std::vector< std::vector< Number > >&& values ) :
    ArrayData( std::move( name ), std::move( values ),
               values.size() > 0 ? values.front().size() : 0,
               values.size() ) {}

  /**
   *  @brief Convenience constructor
   *
   *  @param[in] name     the name of the block
   *  @param[in] array1   the values for array 1
   *  @param[in] array2   the values for array 2
   */
  template < typename Number >
  ArrayData( std::string&& name,
             std::vector< Number >&& array1,
             std::vector< Number >&& array2 ) :
    ArrayData( std::move( name ),
               std::vector< std::vector< Number > >{

                 std::move( array1 ), std::move( array2 ) } ) {}

  /**
   *  @brief Convenience constructor
   *
   *  @param[in] name     the name of the block
   *  @param[in] array1   the values for array 1
   *  @param[in] array2   the values for array 2
   *  @param[in] array3   the values for array 3
   */
  template < typename Number >
  ArrayData( std::string&& name,
             std::vector< Number >&& array1,
             std::vector< Number >&& array2,
             std::vector< Number >&& array3 ) :
    ArrayData( std::move( name ),
               std::vector< std::vector< Number > >{

                 std::move( array1 ), std::move( array2 ),
                 std::move( array3 )
               } ) {}

  /**
   *  @brief Convenience constructor
   *
   *  @param[in] name     the name of the block
   *  @param[in] array1   the values for array 1
   *  @param[in] array2   the values for array 2
   *  @param[in] array3   the values for array 3
   *  @param[in] array4   the values for array 4
   */
  template < typename Number >
  ArrayData( std::string&& name,
             std::vector< Number >&& array1,
             std::vector< Number >&& array2,
             std::vector< Number >&& array3,
             std::vector< Number >&& array4 ) :
    ArrayData( std::move( name ),
               std::vector< std::vector< Number > >{

                 std::move( array1 ), std::move( array2 ),
                 std::move( array3 ), std::move( array4 )
               } ) {}

  /**
   *  @brief Convenience constructor
   *
   *  @param[in] name     the name of the block
   *  @param[in] array1   the values for array 1
   *  @param[in] array2   the values for array 2
   *  @param[in] array3   the values for array 3
   *  @param[in] array4   the values for array 4
   *  @param[in] array5   the values for array 5
   */
  template < typename Number >
  ArrayData( std::string&& name,
             std::vector< Number >&& array1,
             std::vector< Number >&& array2,
             std::vector< Number >&& array3,
             std::vector< Number >&& array4,
             std::vector< Number >&& array5 ) :
    ArrayData( std::move( name ),
               std::vector< std::vector< Number > >{

                 std::move( array1 ), std::move( array2 ),
                 std::move( array3 ), std::move( array4 ),
                 std::move( array5 )
               } ) {}

  /**
   *  @brief Convenience constructor
   *
   *  @param[in] name     the name of the block
   *  @param[in] array1   the values for array 1
   *  @param[in] array2   the values for array 2
   *  @param[in] array3   the values for array 3
   *  @param[in] array4   the values for array 4
   *  @param[in] array5   the values for array 5
   *  @param[in] array6   the values for array 6
   */
  template < typename Number >
  ArrayData( std::string&& name,
             std::vector< Number >&& array1,
             std::vector< Number >&& array2,
             std::vector< Number >&& array3,
             std::vector< Number >&& array4,
             std::vector< Number >&& array5,
             std::vector< Number >&& array6 ) :
    ArrayData( std::move( name ),
               std::vector< std::vector< Number > >{

                 std::move( array1 ), std::move( array2 ),
                 std::move( array3 ), std::move( array4 ),
                 std::move( array5 ), std::move( array6 )
               } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the array data in the XSS array
   *  @param[in] end     the end iterator of the array data in the XSS array
   *  @param[in] n       the number of values in each array
   *  @param[in] m       the number of arrays
   */
  ArrayData( std::string&& name,
             Iterator begin, Iterator end, unsigned int n, unsigned int m ) :
    Base( std::move( name ), begin, end ), nelements_( n ), narrays_( m ) {

    verifySize( this->begin(), this->end(), this->nelements_, this->narrays_ );
  }

  /* methods */

  /**
   *  @brief Return the number of values in each array
   */
  unsigned int N() const { return this->nelements_; }

  /**
   *  @brief Return the number of values in each array
   */
  unsigned int numberValues() const { return this->N(); }

  /**
   *  @brief Return the number of arrays
   */
  unsigned int M() const { return this->narrays_; }

  /**
   *  @brief Return the number of arrays
   */
  unsigned int numberArrays() const { return this->M(); }

  /**
   *  @brief Return a double value
   *
   *  @param[in] array      the array index (one-based)
   *  @param[in] index      the index in the array (one-based)
   */
  double dvalue( std::size_t array, std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIndex( array, index );
    #endif
    return this->XSS( ( array - 1 ) * this->N() + index );
  }

  /**
   *  @brief Return an integer value
   *
   *  @param[in] array      the array index (one-based)
   *  @param[in] index      the index in the array (one-based)
   */
  double ivalue( std::size_t array, std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIndex( array, index );
    #endif
    return this->IXSS( ( array - 1 ) * this->N() + index );
  }

  /**
   *  @brief Return an array of doubles
   *
   *  @param[in] index      the array index (one-based)
   */
  auto darray( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIndex( index );
    #endif
    return this->XSS( 1 + ( index - 1 ) * this->N(), this->N() );
  }

  /**
   *  @brief Return an array of integers
   *
   *  @param[in] index      the array index (one-based)
   */
  auto iarray( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIndex( index );
    #endif
    return this->IXSS( 1 + ( index - 1 ) * this->N(), this->N() );
  }

  /**
   *  @brief Return an empty array
   */
  auto emptyArray() const {

    return this->XSS( 1, 0 );
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::IXSS;
  using Base::begin;
  using Base::end;
};

} // base namespace
} // ACEtk namespace
} // njoy namespace

#endif
