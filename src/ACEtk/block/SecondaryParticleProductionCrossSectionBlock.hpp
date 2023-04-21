#ifndef NJOY_ACETK_BLOCK_SECONDARYPARTICLEPRODUCTIONCROSSSECTIONBLOCK
#define NJOY_ACETK_BLOCK_SECONDARYPARTICLEPRODUCTIONCROSSSECTIONBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/block/details/BaseBlockWithLocators.hpp"
#include "ACEtk/block/TabulatedSecondaryParticleMultiplicity.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

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
    protected details::BaseBlockWithLocators< SecondaryParticleProductionCrossSectionBlock,
                                              TabulatedSecondaryParticleMultiplicity > {

  friend class details::BaseBlockWithLocators< SecondaryParticleProductionCrossSectionBlock,
                                               TabulatedSecondaryParticleMultiplicity >;

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/SecondaryParticleProductionCrossSectionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of secondary particle production reactions
   */
  unsigned int NP() const { return BaseBlockWithLocators::NR(); }

  /**
   *  @brief Return the number of secondary particle production reactions
   */
  unsigned int numberSecondaryParticleProductionReactions() const {

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
   *  @brief Return all cross section data
   */
  const std::vector< TabulatedSecondaryParticleMultiplicity >& data() const {

    return BaseBlockWithLocators::data();
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

    return BaseBlockWithLocators::data( index );
  }

  using BaseBlockWithLocators::empty;
  using BaseBlockWithLocators::name;
  using BaseBlockWithLocators::length;
  using BaseBlockWithLocators::XSS;
  using BaseBlockWithLocators::begin;
  using BaseBlockWithLocators::end;
};

using SIGH = SecondaryParticleProductionCrossSectionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
