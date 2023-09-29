#ifndef NJOY_ACETK_BLOCK_TWOBODYTRANSFERDISTRIBUTION
#define NJOY_ACETK_BLOCK_TWOBODYTRANSFERDISTRIBUTION

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/BaseTwoParameterDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The energy distribution uses two body transfer
 *
 *  It is used in the DLW block as ACE LAW 33.
 */
class TwoBodyTransferDistribution :
  protected details::BaseTwoParameterDistribution {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/TwoBodyTransferDistribution/src/ctor.hpp"

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::TwoBodyTransfer;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::TwoBodyTransfer;
  }

  /**
   *  @brief Return the minimum incident energy for the distribution
   */
  double minimumIncidentEnergy() const {

    return BaseTwoParameterDistribution::minimumIncidentEnergy();
  }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const {

    return BaseTwoParameterDistribution::maximumIncidentEnergy();
  }

  /**
   *  @brief Return the value of C1
   */
  double C1() const { return BaseTwoParameterDistribution::C1(); }

  /**
   *  @brief Return the value of C2
   */
  double C2() const { return BaseTwoParameterDistribution::C2(); }

  using BaseTwoParameterDistribution::empty;
  using BaseTwoParameterDistribution::name;
  using BaseTwoParameterDistribution::length;
  using BaseTwoParameterDistribution::XSS;
  using BaseTwoParameterDistribution::begin;
  using BaseTwoParameterDistribution::end;
};

using ACELAW33 = TwoBodyTransferDistribution;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
