#ifndef NJOY_ACETK_BLOCK_ENERGYDISTRIBUTIONBLOCK
#define NJOY_ACETK_BLOCK_ENERGYDISTRIBUTIONBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/block/details/BaseBlockWithLocators.hpp"
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
#include "ACEtk/block/TwoBodyTransferDistribution.hpp"
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
 *  @brief The continuous energy LDLW and DLW block with the energy
 *         distribution data
 *
 *  The EnergyDistributionBlock class contains energy distribution data,
 *  one for each the first NXS(5) reaction numbers on the MTR block. The order
 *  of the distribution data sets is the same as the order of the reaction
 *  numbers in the MTR block.
 *
 *  @todo verify if DiscretePhotonDistribution can appear here
 */
class EnergyDistributionBlock :
    protected details::BaseBlockWithLocators< EnergyDistributionBlock,
                                              EnergyDistributionData > {

  friend class details::BaseBlockWithLocators< EnergyDistributionBlock,
                                               EnergyDistributionData >;

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/block/EnergyDistributionBlock/src/generateXSS.hpp"
  #include "ACEtk/block/EnergyDistributionBlock/src/generateData.hpp"

public:

  /* constructor */
  #include "ACEtk/block/EnergyDistributionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of reactions that produce the projectile
   *         (excluding elastic )
   */
  unsigned int NR() const { return BaseBlockWithLocators::NR(); }

  /**
   *  @brief Return the number of reactions
   */
  unsigned int numberReactions() const {

    return BaseBlockWithLocators::numberReactions();
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

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using DLW = EnergyDistributionBlock;
using DLWP = EnergyDistributionBlock;
using DLWH = EnergyDistributionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
