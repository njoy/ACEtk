#ifndef NJOY_ACETK_BLOCK_PHOTONPRODUCTIONCROSSSECTIONBLOCK
#define NJOY_ACETK_BLOCK_PHOTONPRODUCTIONCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/BaseBlockWithLocators.hpp"
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
 *  @brief The continuous energy LSIGP and SIGP block with the photon
 *         production cross section data
 *
 *  The PhotonProductionCrossSectionBlock class contains NXS(6) sets of photon
 *  production data, one for each reaction number on the MTRP block. The order
 *  of these cross section data sets is the same as the order of the reaction
 *  numbers in the MTRP block.
 */
class PhotonProductionCrossSectionBlock :
    protected details::BaseBlockWithLocators< PhotonProductionCrossSectionBlock,
                                              PhotonProductionData > {

  friend class details::BaseBlockWithLocators< PhotonProductionCrossSectionBlock,
                                               PhotonProductionData >;

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/block/PhotonProductionCrossSectionBlock/src/generateXSS.hpp"
  #include "ACEtk/block/PhotonProductionCrossSectionBlock/src/generateData.hpp"

public:

  /* constructor */
  #include "ACEtk/block/PhotonProductionCrossSectionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of photon production reactions
   */
  unsigned int NTRP() const { return BaseBlockWithLocators::NTR(); }

  /**
   *  @brief Return the number of photon production reactions
   */
  unsigned int numberPhotonProductionReactions() const {

    return BaseBlockWithLocators::numberReactions();
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

    return BaseBlockWithLocators::LLOC( index );
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

    return BaseBlockWithLocators::locator( index );
  }

  /**
   *  @brief Return the cross section data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const PhotonProductionData& crossSectionData( std::size_t index ) const {

    return BaseBlockWithLocators::data( index );
  }

  using BaseBlockWithLocators::empty;
  using BaseBlockWithLocators::name;
  using BaseBlockWithLocators::length;
  using BaseBlockWithLocators::XSS;
  using BaseBlockWithLocators::begin;
  using BaseBlockWithLocators::end;
};

using SIGP = PhotonProductionCrossSectionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
