#ifndef NJOY_ACETK_BLOCK_DETAILS_BASEBLOCKWITHLOCATORS
#define NJOY_ACETK_BLOCK_DETAILS_BASEBLOCKWITHLOCATORS

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {
namespace details {

/**
 *  @class
 *  @brief The base class for a combined locator and data block like the
 *         LSI&SIG, LAND&AND, LDLW&DLW, etc. blocks
 */
template < typename Derived, typename Data >
class BaseBlockWithLocators : protected details::Base {

  /* fields */
  unsigned int nr_;  // the number of reactions
  Iterator iterator_; // the begin iterator of the data block
  std::vector< Data > data_;

  /* auxiliary functions */
  #include "ACEtk/block/details/BaseBlockWithLocators/src/generateXSS.hpp"
  #include "ACEtk/block/details/BaseBlockWithLocators/src/generateData.hpp"
  #include "ACEtk/block/details/BaseBlockWithLocators/src/generateBlocks.hpp"
  #include "ACEtk/block/details/BaseBlockWithLocators/src/verifyDataIndex.hpp"
  #include "ACEtk/block/details/BaseBlockWithLocators/src/verifySize.hpp"

protected:

  /* fields */

  /* constructor */
  #include "ACEtk/block/details/BaseBlockWithLocators/src/ctor.hpp"

  /**
   *  @brief Return the iterator to the start of the sig block
   */
  Iterator iter() const { return this->iterator_; }

public:

  /* methods */

  /**
   *  @brief Return the number of available reactions
   */
  unsigned int NR() const { return this->nr_; }

  /**
   *  @brief Return the number of available reactions
   */
  unsigned int numberReactions() const { return this->NR(); }

  /**
   *  @brief Return the relative cross section locator for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LLOC( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyReactionIndex( index, 1, this->NR() );
    #endif
    return XSS( index );
  }

  /**
   *  @brief Return the relative cross section locator for a reaction index
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
   *  @brief Return the cross section data for a reaction index
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
  using Base::begin;
  using Base::end;
};

} // details namespace
} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
