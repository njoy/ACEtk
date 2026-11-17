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

  DiscretePhotonDistribution() = default;

  DiscretePhotonDistribution( const DiscretePhotonDistribution& ) = default;
  DiscretePhotonDistribution( DiscretePhotonDistribution&& ) = default;

  DiscretePhotonDistribution& operator=( const DiscretePhotonDistribution& ) = default;
  DiscretePhotonDistribution& operator=( DiscretePhotonDistribution&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] emin      the minimum energy for the distribution
   *  @param[in] emax      the maximum energy for the distribution
   *  @param[in] lp        the primary photon flag (0, 1 or 2)
   *  @param[in] energy    the photon or binding energy
   */
  DiscretePhotonDistribution( double emin, double emax,
                              unsigned int lp, double energy ) :
    TwoParameterDistribution( "DiscretePhotonDistribution", emin, emax,
                              static_cast< double >( lp ), energy ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the block
   *  @param[in] end     the end iterator of the block
   *  @param[in] emin    the minimum energy for the distribution
   *  @param[in] emax    the maximum energy for the distribution
   */
  DiscretePhotonDistribution( Iterator begin, Iterator end,
                              double emin, double emax ) :
    TwoParameterDistribution( "DiscretePhotonDistribution", begin, end, emin, emax ) {}

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
