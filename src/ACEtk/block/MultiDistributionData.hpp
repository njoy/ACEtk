#ifndef NJOY_ACETK_BLOCK_MULTIDISTRIBUTIONDATA
#define NJOY_ACETK_BLOCK_MULTIDISTRIBUTIONDATA

// system includes
#include <variant>

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/block/details/Base.hpp"
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
#include "ACEtk/block/DistributionProbability.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief
 */
class MultiDistributionData : protected details::Base {

public:

  /* type alias */
  using DistributionData = std::variant< EquiprobableOutgoingEnergyBinData,
                                         DiscretePhotonDistribution,
                                         LevelScatteringDistribution,
                                         OutgoingEnergyDistributionData,
                                         GeneralEvaporationSpectrum,
                                         SimpleMaxwellianFissionSpectrum,
                                         EvaporationSpectrum,
                                         EnergyDependentWattSpectrum,
                                         KalbachMannDistributionData,
                                         NBodyPhaseSpaceDistribution >;

private:

  /* fields */
  std::size_t locb_;
  std::vector< DistributionProbability > probabilities_;
  std::vector< DistributionData > distributions_;

  /* auxiliary functions */
//  #include "ACEtk/block/MultiDistributionData/src/verifySize.hpp"
  #include "ACEtk/block/MultiDistributionData/src/generateBlocks.hpp"
//  #include "ACEtk/block/MultiDistributionData/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/block/MultiDistributionData/src/ctor.hpp"

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::MultiDistribution;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::MultiDistribution;
  }

  /**
   *  @brief Return the probability for each distribution
   */
  const std::vector< DistributionProbability >& probabilities() const {

    return this->probabilities_;
  }

  /**
   *  @brief Return the distributions
   */
  const std::vector< DistributionData >& distributions() const {

    return this->distributions_;
  }

  /**
   *  @brief Return the number of distributions
   */
  auto numberDistributions() const { return this->distributions().size(); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
