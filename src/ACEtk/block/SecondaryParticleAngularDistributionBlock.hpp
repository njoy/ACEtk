#ifndef NJOY_ACETK_BLOCK_SECONDARYPARTICLEANGULARDISTRIBUTIONBLOCK
#define NJOY_ACETK_BLOCK_SECONDARYPARTICLEANGULARDISTRIBUTIONBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/block/details/BaseAngularDistributionBlock.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy LANDP,ANDP and LANDH,ANDH blocks with the
 *         angular distribution data for secondary particles that are not the
 *         incident particle type
 *
 *  The SecondaryParticleAngularDistributionBlock class contains angular
 *  distribution data, one for each the NXS(6) reaction numbers on the MTRP
 *  block (for the LANDP,ANDP blocks) and each of the NTRO(ITYPE) reactions on
 *  the MTRH(ITYPE) block. The order of the distribution data sets is the same
 *  as the order of the reaction numbers in the corresponding MTR block.
 */
class SecondaryParticleAngularDistributionBlock :
    protected details::BaseAngularDistributionBlock {

  /* fields */

  /* auxiliary functions */

public:

  /* type alias */
  using DistributionData = details::BaseAngularDistributionBlock::DistributionData;

  /* constructor */
  #include "ACEtk/block/SecondaryParticleAngularDistributionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of reactions that produce the projectile
   *         (excluding elastic )
   */
  unsigned int NR() const {

    return BaseAngularDistributionBlock::NR();
  }

  /**
   *  @brief Return the number of reactions that produce the projectile
   *         (excluding elastic)
   */
  unsigned int numberReactions() const {

    return BaseAngularDistributionBlock::numberReactions();
  }

  /**
   *  @brief Return the relative angular distribution locator for a reaction
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based, zero for elastic)
   */
  int LAND( std::size_t index ) const {

    return BaseAngularDistributionBlock::LAND( index );
  }

  /**
   *  @brief Return the relative angular distribution locator for a reaction
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based, zero for elastic)
   */
  int angularDistributionLocator( std::size_t index ) const {

    return BaseAngularDistributionBlock::angularDistributionLocator( index );
  }

  /**
   *  @brief Return whether or not the distribution data is fully isotropic for
   *         a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based, zero for elastic)
   */
  bool isFullyIsotropic( std::size_t index ) const {

    return BaseAngularDistributionBlock::isFullyIsotropic( index );
  }

  /**
   *  @brief Return whether or not the distribution data for a reaction index
   *         is given in the AND block
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based, zero for elastic)
   */
  bool isGiven( std::size_t index ) const {

    return BaseAngularDistributionBlock::isGiven( index );
  }

  /**
   *  @brief Return all angular distribution data
   */
  const std::vector< DistributionData >& data() const {

    return BaseAngularDistributionBlock::data();
  }

  /**
   *  @brief Return the angular distribution data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const DistributionData& angularDistributionData( std::size_t index ) const {

    return BaseAngularDistributionBlock::angularDistributionData( index );
  }

  using BaseAngularDistributionBlock::empty;
  using BaseAngularDistributionBlock::name;
  using BaseAngularDistributionBlock::length;
  using BaseAngularDistributionBlock::XSS;
  using BaseAngularDistributionBlock::begin;
  using BaseAngularDistributionBlock::end;
};

using ANDH = SecondaryParticleAngularDistributionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
