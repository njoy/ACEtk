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
  #include "ACEtk/block/MultiDistributionData/src/verifyDistributionIndex.hpp"
  #include "ACEtk/block/MultiDistributionData/src/generateXSS.hpp"

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
   *  @brief Return the number of distributions
   */
  std::size_t numberDistributions() const {

    return this->distributions_.size();
  }

  /**
   *  @brief Return the probability for each distribution
   */
  const std::vector< DistributionProbability >& probabilities() const {

    return this->probabilities_;
  }

  /**
   *  @brief Return the probability data for a given distribution index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const DistributionProbability& probability( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDistributionIndex( index );
    #endif
    return this->probabilities_[ index - 1 ];
  }

  /**
   *  @brief Return the distributions
   */
  const std::vector< DistributionData >& distributions() const {

    return this->distributions_;
  }

  /**
   *  @brief Return the distribution data for a given distribution index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const DistributionData& distribution( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDistributionIndex( index );
    #endif
    return this->distributions_[ index - 1 ];
  }

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
