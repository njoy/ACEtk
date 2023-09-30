#ifndef NJOY_ACETK_CONTINUOUS_SECONDARYPARTICLEPRODUCTIONCROSSSECTIONBLOCK
#define NJOY_ACETK_CONTINUOUS_SECONDARYPARTICLEPRODUCTIONCROSSSECTIONBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/base/BlockWithLocators.hpp"
#include "ACEtk/continuous/TabulatedSecondaryParticleMultiplicity.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief The continuous energy LSIGH and SIGH block with the secondary
 *         particle production cross section data (multiplicity data only)
 *
 *  The SecondaryParticleProductionCrossSectionBlock class contains NTRO.NP sets
 *  of secondary particle production data, one for each reaction number on the
 *  MTRH block. The order of these cross section data sets is the same as the
 *  order of the reaction numbers in the MTRH block.
 */
class SecondaryParticleProductionCrossSectionBlock :
    protected base::BlockWithLocators< SecondaryParticleProductionCrossSectionBlock,
                                       TabulatedSecondaryParticleMultiplicity > {

  friend class base::BlockWithLocators< SecondaryParticleProductionCrossSectionBlock,
                                        TabulatedSecondaryParticleMultiplicity >;

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/continuous/SecondaryParticleProductionCrossSectionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of secondary particle production reactions
   */
  unsigned int NP() const { return BlockWithLocators::N(); }

  /**
   *  @brief Return the number of secondary particle production reactions
   */
  unsigned int numberSecondaryParticleProductionReactions() const {

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
  const std::vector< TabulatedSecondaryParticleMultiplicity >& data() const {

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
  const TabulatedSecondaryParticleMultiplicity& crossSectionData( std::size_t index ) const {

    return BlockWithLocators::data( index );
  }

  using BlockWithLocators::empty;
  using BlockWithLocators::name;
  using BlockWithLocators::length;
  using BlockWithLocators::XSS;
  using BlockWithLocators::begin;
  using BlockWithLocators::end;
};

using SIGH = SecondaryParticleProductionCrossSectionBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
