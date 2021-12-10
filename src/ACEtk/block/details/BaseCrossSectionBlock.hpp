#ifndef NJOY_ACETK_BLOCK_DETAILS_BASECROSSSECTIONBLOCK
#define NJOY_ACETK_BLOCK_DETAILS_BASECROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {
namespace details {

/**
 *  @class
 *  @brief The base class for a LSIG and SIG block with cross section data
 */
template < typename Derived, typename Data >
class BaseCrossSectionBlock : protected details::Base {

  /* fields */
  unsigned int ntr_; // the number of reactions (excluding elastic)
  Iterator sig_;     // the begin iterator of the SIG block
  std::vector< Data > xs_;

  /* auxiliary functions */
  #include "ACEtk/block/details/BaseCrossSectionBlock/src/generateXSS.hpp"
  #include "ACEtk/block/details/BaseCrossSectionBlock/src/generateData.hpp"
  #include "ACEtk/block/details/BaseCrossSectionBlock/src/generateBlocks.hpp"
  #include "ACEtk/block/details/BaseCrossSectionBlock/src/verifyCrossSectionIndex.hpp"
  #include "ACEtk/block/details/BaseCrossSectionBlock/src/verifySize.hpp"

protected:

  /* fields */

  /* constructor */
  #include "ACEtk/block/details/BaseCrossSectionBlock/src/ctor.hpp"

  /**
   *  @brief Return the iterator to the start of the sig block
   */
  Iterator sig() const { return this->sig_; }

public:

  /* methods */

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int NTR() const { return this->ntr_; }

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int numberReactions() const { return this->NTR(); }

  /**
   *  @brief Return the relative cross section locator for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LSIG( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyReactionIndex( index, 1, this->NTR() );
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
  std::size_t crossSectionLocator( std::size_t index ) const {

    return this->LSIG( index );
  }

  /**
   *  @brief Return the cross section data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const Data& crossSectionData( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyCrossSectionIndex( index );
    #endif
    return this->xs_[ index - 1 ];
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
