#ifndef NJOY_ACETK_CONTINUOUS_SECONDARYPARTICLEANGULARDISTRIBUTIONBLOCK
#define NJOY_ACETK_CONTINUOUS_SECONDARYPARTICLEANGULARDISTRIBUTIONBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/base/AngularDistributionBlock.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief The continuous energy LANDP, ANDP and LANDH, ANDH blocks with the
 *         angular distribution data for secondary particles that are not the
 *         incident particle type
 *
 *  The SecondaryParticleAngularDistributionBlock class contains angular
 *  distribution data, one for each the NXS(6) reaction numbers on the MTRP
 *  block (for the LANDP, ANDP blocks) and each of the NTRO(ITYPE) reactions on
 *  the MTRH(ITYPE) block. The order of the distribution data sets is the same
 *  as the order of the reaction numbers in the corresponding MTR block.
 */
class SecondaryParticleAngularDistributionBlock :
    protected base::AngularDistributionBlock {

  /* fields */

  /* auxiliary functions */

public:

  /* type alias */

  using DistributionData = base::AngularDistributionBlock::DistributionData;

  /* constructor */

  SecondaryParticleAngularDistributionBlock() = default;

  SecondaryParticleAngularDistributionBlock( const SecondaryParticleAngularDistributionBlock& ) = default;
  SecondaryParticleAngularDistributionBlock( SecondaryParticleAngularDistributionBlock&& ) = default;

  SecondaryParticleAngularDistributionBlock& operator=( const SecondaryParticleAngularDistributionBlock& ) = default;
  SecondaryParticleAngularDistributionBlock& operator=( SecondaryParticleAngularDistributionBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] data    the distribution data for all reactions
   */
  SecondaryParticleAngularDistributionBlock( std::vector< DistributionData > data ) :
    AngularDistributionBlock( "ANDH", std::move( data ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] loc     the begin iterator of the LSIG block in the XSS array
   *  @param[in] data    the begin iterator of the SIG block in the XSS array
   *  @param[in] end     the end iterator of the SIG block in the XSS array
   *  @param[in] nr      the number of reactions (excluding elastic)
   */
  SecondaryParticleAngularDistributionBlock( Iterator loc, Iterator data,
                                             Iterator end, unsigned int nr ) :
    AngularDistributionBlock( "ANDH", loc, data, end, nr, false ) {}

  /* methods */

  /**
   *  @brief Return the number of reactions with angular distribution data
   */
  unsigned int NR() const {

    return AngularDistributionBlock::NR();
  }

  /**
  *  @brief Return the number of reactions with angular distribution data
   */
  unsigned int numberReactions() const {

    return AngularDistributionBlock::numberReactions();
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

    return AngularDistributionBlock::LAND( index );
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

    return AngularDistributionBlock::angularDistributionLocator( index );
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

    return AngularDistributionBlock::isFullyIsotropic( index );
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

    return AngularDistributionBlock::isGiven( index );
  }

  /**
   *  @brief Return all angular distribution data
   */
  const std::vector< DistributionData >& data() const {

    return AngularDistributionBlock::data();
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

    return AngularDistributionBlock::angularDistributionData( index );
  }

  using AngularDistributionBlock::empty;
  using AngularDistributionBlock::name;
  using AngularDistributionBlock::length;
  using AngularDistributionBlock::XSS;
  using AngularDistributionBlock::begin;
  using AngularDistributionBlock::end;
};

using ANDP = SecondaryParticleAngularDistributionBlock;
using ANDH = SecondaryParticleAngularDistributionBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
