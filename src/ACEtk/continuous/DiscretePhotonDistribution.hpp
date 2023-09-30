#ifndef NJOY_ACETK_CONTINUOUS_DISCRETEPHOTONDISTRIBUTION
#define NJOY_ACETK_CONTINUOUS_DISCRETEPHOTONDISTRIBUTION

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/TwoParameterDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief A discrete photon energy distribution
 *
 *  The DiscretePhotonDistribution class contains the photon energy if the
 *  photon is a primary photon or the binding energy when the photon is not a
 *  primary photon. It is used in the DLW block as ACE LAW 2.
 */
class DiscretePhotonDistribution : protected base::TwoParameterDistribution {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/continuous/DiscretePhotonDistribution/src/ctor.hpp"

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

    return TwoParameterDistribution::minimumIncidentEnergy();
  }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const {

    return TwoParameterDistribution::maximumIncidentEnergy();
  }

  /**
   *  @brief Return the primary flag value (0, 1 or 2)
   */
  unsigned int LP() const { return TwoParameterDistribution::C1(); }

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
  double EG() const { return TwoParameterDistribution::C2(); }

  /**
   *  @brief Return the photon or binding energy
   */
  double photonOrBindingEnergy() const { return this->EG(); }

  using TwoParameterDistribution::empty;
  using TwoParameterDistribution::name;
  using TwoParameterDistribution::length;
  using TwoParameterDistribution::XSS;
  using TwoParameterDistribution::begin;
  using TwoParameterDistribution::end;
};

using ACELAW2 = DiscretePhotonDistribution;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
