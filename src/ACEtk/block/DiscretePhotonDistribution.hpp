#ifndef NJOY_ACETK_BLOCK_DISCRETEPHOTONDISTRIBUTION
#define NJOY_ACETK_BLOCK_DISCRETEPHOTONDISTRIBUTION

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/block/details/BaseTwoParameterDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief A discrete photon energy distribution
 *
 *  The DiscretePhotonDistribution class contains the photon energy if the
 *  photon is a primary photon or the binding energy when the photon is not a
 *  primary photon. It is used in the DLW block as ACE LAW 2.
 */
class DiscretePhotonDistribution : protected details::BaseTwoParameterDistribution {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/DiscretePhotonDistribution/src/ctor.hpp"

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::DiscretePhoton;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::DiscretePhoton;
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
   *  @brief Return the primary flag value (0, 1 or 2)
   */
  unsigned int LP() const { return BaseTwoParameterDistribution::C1(); }

  /**
   *  @brief Return the primary flag value (0, 1 or 2)
   */
  unsigned int primaryPhotonFlag() const { return this->LP(); }

  /**
   *  @brief Return whether or not the photon is a primary photon
   */
  bool isPrimaryPhoton() const { return this->LP() == 2; }

  /**
   *  @brief Return the photon or binding energy
   */
  double EG() const { return BaseTwoParameterDistribution::C2(); }

  /**
   *  @brief Return the photon or binding energy
   */
  double photonOrBindingEnergy() const { return this->EG(); }

  using BaseTwoParameterDistribution::empty;
  using BaseTwoParameterDistribution::name;
  using BaseTwoParameterDistribution::length;
  using BaseTwoParameterDistribution::XSS;
  using BaseTwoParameterDistribution::begin;
  using BaseTwoParameterDistribution::end;
};

using ACELAW2 = DiscretePhotonDistribution;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
