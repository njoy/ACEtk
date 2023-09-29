#ifndef NJOY_ACETK_CONTINUOUS_PHOTONPRODUCTIONCROSSSECTIONBLOCK
#define NJOY_ACETK_CONTINUOUS_PHOTONPRODUCTIONCROSSSECTIONBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/base/BlockWithLocators.hpp"
#include "ACEtk/continuous/PhotonProductionCrossSectionData.hpp"
#include "ACEtk/continuous/TabulatedSecondaryParticleMultiplicity.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/* type alias */
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
    protected base::BlockWithLocators< PhotonProductionCrossSectionBlock,
                                       PhotonProductionData > {

  friend class base::BlockWithLocators< PhotonProductionCrossSectionBlock,
                                        PhotonProductionData >;

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/continuous/PhotonProductionCrossSectionBlock/src/generateXSS.hpp"
  #include "ACEtk/continuous/PhotonProductionCrossSectionBlock/src/generateData.hpp"

public:

  /* constructor */
  #include "ACEtk/continuous/PhotonProductionCrossSectionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of photon production reactions
   */
  unsigned int NTRP() const { return BlockWithLocators::N(); }

  /**
   *  @brief Return the number of photon production reactions
   */
  unsigned int numberPhotonProductionReactions() const {

    return BlockWithLocators::numberDataBlocks();
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

    return BlockWithLocators::LLOC( index );
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

    return BlockWithLocators::locator( index );
  }

  /**
   *  @brief Return all cross section data
   */
  const std::vector< PhotonProductionData >& data() const {

    return BlockWithLocators::data();
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

    return BlockWithLocators::data( index );
  }

  using BlockWithLocators::empty;
  using BlockWithLocators::name;
  using BlockWithLocators::length;
  using BlockWithLocators::XSS;
  using BlockWithLocators::begin;
  using BlockWithLocators::end;
};

using SIGP = PhotonProductionCrossSectionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
