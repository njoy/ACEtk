#ifndef NJOY_ACETK_CONTINUOUS_SECONDARYPARTICLEENERGYDISTRIBUTIONBLOCK
#define NJOY_ACETK_CONTINUOUS_SECONDARYPARTICLEENERGYDISTRIBUTIONBLOCK

// system includes
#include <variant>

// other includes
#include "tools/overload.hpp"
#include "ACEtk/base/BlockWithLocators.hpp"
#include "ACEtk/continuous/FrameAndMultiplicityBlock.hpp"
#include "ACEtk/continuous/EquiprobableOutgoingEnergyBinData.hpp"
#include "ACEtk/continuous/DiscretePhotonDistribution.hpp"
#include "ACEtk/continuous/LevelScatteringDistribution.hpp"
#include "ACEtk/continuous/OutgoingEnergyDistributionData.hpp"
#include "ACEtk/continuous/GeneralEvaporationSpectrum.hpp"
#include "ACEtk/continuous/SimpleMaxwellianFissionSpectrum.hpp"
#include "ACEtk/continuous/EvaporationSpectrum.hpp"
#include "ACEtk/continuous/EnergyDependentWattSpectrum.hpp"
#include "ACEtk/continuous/KalbachMannDistributionData.hpp"
#include "ACEtk/continuous/NBodyPhaseSpaceDistribution.hpp"
#include "ACEtk/continuous/TwoBodyTransferDistribution.hpp"
#include "ACEtk/continuous/EnergyAngleDistributionData.hpp"
#include "ACEtk/continuous/AngleEnergyDistributionData.hpp"
#include "ACEtk/continuous/MultiDistributionData.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

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
    protected base::BlockWithLocators< SecondaryParticleEnergyDistributionBlock,
                                       EnergyDistributionData > {

  friend class base::BlockWithLocators< SecondaryParticleEnergyDistributionBlock,
                                        EnergyDistributionData >;

  /* fields */
  std::optional< continuous::TYRH > tyrh_;
  std::vector< std::optional< ReferenceFrame > > frames_;

  /* auxiliary functions */
  #include "ACEtk/continuous/SecondaryParticleEnergyDistributionBlock/src/generateXSS.hpp"
  #include "ACEtk/continuous/SecondaryParticleEnergyDistributionBlock/src/generateData.hpp"
  #include "ACEtk/continuous/SecondaryParticleEnergyDistributionBlock/src/generateFrames.hpp"

  /**
   *  @brief Return the associated TYRH block
   */
  const std::optional< continuous::TYRH >& TYRH() const { return this->tyrh_; }

public:

  /* constructor */
  #include "ACEtk/continuous/SecondaryParticleEnergyDistributionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of reactions with energy distribution data
   */
  unsigned int NR() const { return BlockWithLocators::N(); }

  /**
   *  @brief Return the number of reactions with energy distribution data
   */
  unsigned int numberReactions() const {

    return BlockWithLocators::numberDataBlocks();
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

    return BlockWithLocators::LLOC( index );
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

    return BlockWithLocators::locator( index );
  }

  /**
   *  @brief Return all energy distribution data
   */
  const std::vector< EnergyDistributionData >& data() const {

    return BlockWithLocators::data();
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

    return BlockWithLocators::data( index );
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

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
