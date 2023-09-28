#ifndef NJOY_ACETK_BLOCK_DETAILS_ELECTRONBASEBLOCKWITHLOCATORS
#define NJOY_ACETK_BLOCK_DETAILS_ELECTRONBASEBLOCKWITHLOCATORS

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {
namespace details {

/**
 *  @class
 *  @brief The base class for a combined locator and data block prepended
 */
template < typename Derived, typename Data >
class BaseElectronBlockWithLocators : protected details::Base {

  /* fields */
  std::size_t n_;
  ArrayData information_;
  std::vector< Data > data_; // the data blocks

  /* auxiliary functions */
  #include "ACEtk/block/details/BaseElectronBlockWithLocators/src/generateXSS.hpp"
  #include "ACEtk/block/details/BaseElectronBlockWithLocators/src/generateBlocks.hpp"

protected:

  /* auxiliary functions */
  #include "ACEtk/block/details/BaseElectronBlockWithLocators/src/verifyDataIndex.hpp"

  /* constructor */
  #include "ACEtk/block/details/BaseElectronBlockWithLocators/src/ctor.hpp"

  /**
   *  @brief Return the iterator to the start of the data block
   */
  Iterator iter() const { return this->iterator_; }

public:

  /* methods */

  /**
   *  @brief Return the number of available data blocks
   */
  unsigned int N() const { return this->n_; }

  /**
   *  @brief Return the number of available data blocks
   */
  unsigned int numberDataBlocks() const { return this->N(); }

  /**
   *  @brief Return the relative data locator for a data block index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LLOC( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->information_.ivalue( 3, index ) + 1;
  }

  /**
   *  @brief Return the relative data locator for a data block index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t locator( std::size_t index ) const {

    return this->LLOC( index );
  }

  /**
   *  @brief Return the energy values
   */
  auto E() const { return this->information_.darray( 1 ); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->E(); }

  /**
   *  @brief Return the table lengths
   */
  auto L() const { return this->information_.iarray( 1 ); }

  /**
   *  @brief Return the table lengths
   */
  auto lengths() const { return this->L(); }

  /**
   *  @brief Return the data vector
   */
  const std::vector< Data >& data() const {

    return this->data_;
  }

  /**
   *  @brief Return the energy for a data block index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  double energy( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->information_.dvalue( 1, index );
  }

  /**
   *  @brief Return the table length for a data block index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  unsigned int length( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->information_.ivalue( 2, index );
  }

  /**
   *  @brief Return the data for a data block index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const Data& data( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->data_[ index - 1 ];
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
