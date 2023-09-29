#ifndef NJOY_ACETK_BASE_ARRAYDATA
#define NJOY_ACETK_BASE_ARRAYDATA

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {
namespace details {

/**
 *  @class
 *  @brief A block of data given as a number of arrays of equal length
 */
class ArrayData : protected details::Base {

  /* fields */
  unsigned int nelements_;
  unsigned int narrays_;

  /* auxiliary functions */
  #include "ACEtk/base/ArrayData/src/verifyIndex.hpp"
  #include "ACEtk/base/ArrayData/src/generateXSS.hpp"
  #include "ACEtk/base/ArrayData/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/base/ArrayData/src/ctor.hpp"

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

} // details namespace
} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
