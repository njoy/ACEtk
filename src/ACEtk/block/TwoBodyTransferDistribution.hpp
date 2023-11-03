#ifndef NJOY_ACETK_BLOCK_TWOBODYTRANSFERDISTRIBUTION
#define NJOY_ACETK_BLOCK_TWOBODYTRANSFERDISTRIBUTION

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/TwoParameterDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The energy distribution uses two body transfer
 *
 *  It is used in the DLW block as ACE LAW 33.
 */
class TwoBodyTransferDistribution : protected base::TwoParameterDistribution {

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

    return TwoParameterDistribution::minimumIncidentEnergy();
  }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const {

    return TwoParameterDistribution::maximumIncidentEnergy();
  }

  /**
   *  @brief Return the value of C1
   */
  double C1() const { return TwoParameterDistribution::C1(); }

  /**
   *  @brief Return the value of C2
   */
  double C2() const { return TwoParameterDistribution::C2(); }

  using TwoParameterDistribution::empty;
  using TwoParameterDistribution::name;
  using TwoParameterDistribution::length;
  using TwoParameterDistribution::XSS;
  using TwoParameterDistribution::begin;
  using TwoParameterDistribution::end;
};

using ACELAW33 = TwoBodyTransferDistribution;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
