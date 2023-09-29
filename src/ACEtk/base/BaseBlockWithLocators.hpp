#ifndef NJOY_ACETK_BASE_BASEBLOCKWITHLOCATORS
#define NJOY_ACETK_BASE_BASEBLOCKWITHLOCATORS

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {
namespace details {

/**
 *  @class
 *  @brief The base class for a combined locator and data block like the
 *         LSIG&SIG, LDLW&DLW, etc. blocks
 */
template < typename Derived, typename Data >
class BaseBlockWithLocators : protected details::Base {

  /* fields */
  unsigned int n_;           // the number of data blocks
  bool locator_;             // flag to indicate if locators or offsets are used
  Iterator iterator_;        // the begin iterator of the data block
  std::vector< Data > data_; // the data blocks

  /* auxiliary functions */
  #include "ACEtk/base/BaseBlockWithLocators/src/generateXSS.hpp"
  #include "ACEtk/base/BaseBlockWithLocators/src/generateData.hpp"
  #include "ACEtk/base/BaseBlockWithLocators/src/generateBlocks.hpp"
  #include "ACEtk/base/BaseBlockWithLocators/src/verifySize.hpp"

protected:

  /* auxiliary functions */
  #include "ACEtk/base/BaseBlockWithLocators/src/verifyDataIndex.hpp"

  /* constructor */
  #include "ACEtk/base/BaseBlockWithLocators/src/ctor.hpp"

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
    return this->locator_ ? this->IXSS( index ) : this->IXSS( index ) + 1;
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
   *  @brief Return the data vector
   */
  const std::vector< Data >& data() const {

    return this->data_;
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
