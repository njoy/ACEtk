#ifndef NJOY_ACETK_BLOCK_SECONDARYPARTICLEENERGYDISTRIBUTIONBLOCK
#define NJOY_ACETK_BLOCK_SECONDARYPARTICLEENERGYDISTRIBUTIONBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/base/BaseBlockWithLocators.hpp"
#include "ACEtk/block/FrameAndMultiplicityBlock.hpp"
#include "ACEtk/block/EquiprobableOutgoingEnergyBinData.hpp"
#include "ACEtk/block/DiscretePhotonDistribution.hpp"
#include "ACEtk/block/LevelScatteringDistribution.hpp"
#include "ACEtk/block/OutgoingEnergyDistributionData.hpp"
#include "ACEtk/block/GeneralEvaporationSpectrum.hpp"
#include "ACEtk/block/SimpleMaxwellianFissionSpectrum.hpp"
#include "ACEtk/block/EvaporationSpectrum.hpp"
#include "ACEtk/block/EnergyDependentWattSpectrum.hpp"
#include "ACEtk/block/KalbachMannDistributionData.hpp"
#include "ACEtk/block/NBodyPhaseSpaceDistribution.hpp"
#include "ACEtk/block/TwoBodyTransferDistribution.hpp"
#include "ACEtk/block/EnergyAngleDistributionData.hpp"
#include "ACEtk/block/AngleEnergyDistributionData.hpp"
#include "ACEtk/block/MultiDistributionData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/* type alias */
using EnergyDistributionData = std::variant< EquiprobableOutgoingEnergyBinData,
                                             DiscretePhotonDistribution,
                                             LevelScatteringDistribution,
                                             OutgoingEnergyDistributionData,
                                             GeneralEvaporationSpectrum,
                                             SimpleMaxwellianFissionSpectrum,
                                             EvaporationSpectrum,
                                             EnergyDependentWattSpectrum,
                                             KalbachMannDistributionData,
                                             NBodyPhaseSpaceDistribution,
                                             TwoBodyTransferDistribution,
                                             EnergyAngleDistributionData,
                                             AngleEnergyDistributionData,
                                             MultiDistributionData >;

/**
 *  @class
 *  @brief The continuous energy LDLWP, DLWP and LDLWH, DLWH blocks with the
 *         energy distribution data for secondary particles that are not the
 *         incident particle type
 *
 *  The SecondaryParticleAngularDistributionBlock class contains energy
 *  distribution data, one for each the NXS(6) reaction numbers on the MTRP
 *  block (for the LANDP, ANDP blocks) and each of the NTRO(ITYPE) reactions on
 *  the MTRH(ITYPE) block. The order of the distribution data sets is the same
 *  as the order of the reaction numbers in the corresponding MTR block.
 */
class SecondaryParticleEnergyDistributionBlock :
    protected details::BaseBlockWithLocators< SecondaryParticleEnergyDistributionBlock,
                                              EnergyDistributionData > {

  friend class details::BaseBlockWithLocators< SecondaryParticleEnergyDistributionBlock,
                                               EnergyDistributionData >;

  /* fields */
  std::optional< block::TYRH > tyrh_;
  std::vector< std::optional< ReferenceFrame > > frames_;

  /* auxiliary functions */
  #include "ACEtk/block/SecondaryParticleEnergyDistributionBlock/src/generateXSS.hpp"
  #include "ACEtk/block/SecondaryParticleEnergyDistributionBlock/src/generateData.hpp"
  #include "ACEtk/block/SecondaryParticleEnergyDistributionBlock/src/generateFrames.hpp"

  /**
   *  @brief Return the associated TYRH block
   */
  const std::optional< block::TYRH >& TYRH() const { return this->tyrh_; }

public:

  /* constructor */
  #include "ACEtk/block/SecondaryParticleEnergyDistributionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of reactions with energy distribution data
   */
  unsigned int NR() const { return BaseBlockWithLocators::N(); }

  /**
   *  @brief Return the number of reactions with energy distribution data
   */
  unsigned int numberReactions() const {

    return BaseBlockWithLocators::numberDataBlocks();
  }

  /**
   *  @brief Return the relative energy distribution locator for a reaction
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int LDLW( std::size_t index ) const {

    return BaseBlockWithLocators::LLOC( index );
  }

  /**
   *  @brief Return the relative energy distribution locator for a reaction
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int energyDistributionLocator( std::size_t index ) const {

    return BaseBlockWithLocators::locator( index );
  }

  /**
   *  @brief Return all energy distribution data
   */
  const std::vector< EnergyDistributionData >& data() const {

    return BaseBlockWithLocators::data();
  }

  /**
   *  @brief Return the energy distribution data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const EnergyDistributionData& energyDistributionData( std::size_t index ) const {

    return BaseBlockWithLocators::data( index );
  }

  /**
   *  @brief Return all reference frames
   */
  const std::vector< std::optional< ReferenceFrame > >& referenceFrames() const {

    return this->frames_;
  }

  /**
   *  @brief Return the reference frame for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const std::optional< ReferenceFrame >& referenceFrame( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->frames_[ index - 1 ];
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using DLWP = SecondaryParticleEnergyDistributionBlock;
using DNED = SecondaryParticleEnergyDistributionBlock;
using DLWH = SecondaryParticleEnergyDistributionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
