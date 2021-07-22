#ifndef NJOY_ACETK_BLOCK_CROSSSECTIONBLOCK
#define NJOY_ACETK_BLOCK_CROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/Base.hpp"
#include "range/v3/view/drop_exactly.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy LSIG and SIG block with the cross section data
 *
 *  The CrossSectionBlock class contains NXS(4) sets of cross section values,
 *  one for each reaction number on the MTR block. The order of these cross
 *  section data sets is the same as the order of the reaction numbers in the
 *  MTR block.
 */
class CrossSectionBlock : protected Base {

  /* fields */
  unsigned int ntr_; // the number of reactions (excluding elastic)
  Iterator sig_;     // the begin iterator of the SIG block

  /* auxiliary functions */
  #include "ACEtk/block/CrossSectionBlock/src/verifyReactionIndex.hpp"
  #include "ACEtk/block/CrossSectionBlock/src/verifySize.hpp"

public:

  #include "ACEtk/block/CrossSectionBlock/CrossSectionData.hpp"

  /* constructor */
  #include "ACEtk/block/CrossSectionBlock/src/ctor.hpp"

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
   *  When the index is out of range an std::out_of_range exception is thrown.
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LSIG( std::size_t index ) const {

    this->verifyReactionIndex( index );
    return XSS( index );
  }

  /**
   *  @brief Return the relative cross section locator for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown.
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t crossSectionLocator( std::size_t index ) const {

    return this->LSIG( index );
  }

  /**
   *  @brief Return the cross section data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown.
   *
   *  @param[in] index     the index (one-based)
   */
  auto crossSectionData( std::size_t index ) const {

    auto locator = this->LSIG( index );
    auto sig = std::distance( this->begin(), this->sig_ ) + 1;
    auto xss = XSS( sig + locator - 1,
                    static_cast< std::size_t >( XSS( sig + locator ) ) + 2 );
    using Chunk = decltype( xss );
    return CrossSectionData< Chunk >( std::move( xss ) );
  }

  /**
   *  @brief Return the energy index for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown.
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t energyIndex( std::size_t index ) const {

    auto locator = this->LSIG( index );
    auto sig = std::distance( this->begin(), this->sig_ ) + 1;
    return XSS( sig + locator - 1 );
  }

  /**
   *  @brief Return the number of cross section values for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown.
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t numberValues( std::size_t index ) const {

    auto locator = this->LSIG( index );
    auto sig = std::distance( this->begin(), this->sig_ ) + 1;
    return XSS( sig + locator );
  }

  /**
   *  @brief Return the cross section values for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown.
   *
   *  @param[in] index     the index (one-based)
   */
  auto crossSections( std::size_t index ) const {

    auto locator = this->LSIG( index );
    auto sig = std::distance( this->begin(), this->sig_ ) + 1;
    return XSS( sig + locator + 1,
                static_cast< std::size_t >( XSS( sig + locator ) ) );
  }

  using Base::name;
  using Base::length;
  using Base::XSS;
};

using SIG = CrossSectionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
