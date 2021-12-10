#ifndef NJOY_ACETK_BLOCK_PHOTONPRODUCTIONCROSSSECTIONBLOCK
#define NJOY_ACETK_BLOCK_PHOTONPRODUCTIONCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/BaseCrossSectionBlock.hpp"
#include "ACEtk/block/PhotonProductionCrossSectionData.hpp"
#include "ACEtk/block/TabulatedSecondaryParticleMultiplicity.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

using PhotonProductionData = std::variant<
                                 PhotonProductionCrossSectionData,
                                 TabulatedSecondaryParticleMultiplicity >;

/**
 *  @class
 *  @brief The continuous energy LSIG and SIG block with the cross section data
 *
 *  The CrossSectionBlock class contains NXS(4) sets of cross section values,
 *  one for each reaction number on the MTR block. The order of these cross
 *  section data sets is the same as the order of the reaction numbers in the
 *  MTR block.
 */
class PhotonProductionCrossSectionBlock :
    protected details::BaseCrossSectionBlock< PhotonProductionCrossSectionBlock,
                                              PhotonProductionData > {

  friend class details::BaseCrossSectionBlock< PhotonProductionCrossSectionBlock,
                                               PhotonProductionData >;

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/block/PhotonProductionCrossSectionBlock/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/block/PhotonProductionCrossSectionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of photon production reactions
   */
  unsigned int NTRP() const { return BaseCrossSectionBlock::NTR(); }

  /**
   *  @brief Return the number of photon production reactions
   */
  unsigned int numberPhotonProductionReactions() const {

    return BaseCrossSectionBlock::numberReactions();
  }

  /**
   *  @brief Return the relative cross section locator for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t LSIG( std::size_t index ) const {

    return BaseCrossSectionBlock::LSIG( index );
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

    return BaseCrossSectionBlock::crossSectionLocator( index );
  }

  /**
   *  @brief Return the cross section data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  PhotonProductionData crossSectionData( std::size_t index ) const {

    // sig : one-based index to the start of the SIG block
    // sig + locator - 1 : one-based index to the start of cross section data
    std::size_t sig = std::distance( this->begin(), this->sig_ ) + 1;
    const auto left = this->iterator( sig + this->LSIG( index ) - 1 );
    const auto right = index == this->NTR()
                       ? this->end()
                       : this->iterator( sig + this->LSIG( index + 1 ) - 1 );
    if ( *left == 13 ) {

      return PhotonProductionCrossSectionData( left, right );
    }
    else {

      return TabulatedSecondaryParticleMultiplicity( left, right );
    }
  }

  using BaseCrossSectionBlock::empty;
  using BaseCrossSectionBlock::name;
  using BaseCrossSectionBlock::length;
  using BaseCrossSectionBlock::XSS;
  using BaseCrossSectionBlock::begin;
  using BaseCrossSectionBlock::end;
};

using SIGP = PhotonProductionCrossSectionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
