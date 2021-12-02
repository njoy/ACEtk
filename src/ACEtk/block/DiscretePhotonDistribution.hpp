#ifndef NJOY_ACETK_BLOCK_DISCRETEPHOTONDISTRIBUTION
#define NJOY_ACETK_BLOCK_DISCRETEPHOTONDISTRIBUTION

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/block/details/Base.hpp"

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
class DiscretePhotonDistribution : protected details::Base {

  /* fields */
  double emin_;
  double emax_;

  /* auxiliary functions */
  #include "ACEtk/block/DiscretePhotonDistribution/src/verifySize.hpp"

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
  double minimumIncidentEnergy() const { return this->emin_; }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const { return this->emax_; }

  /**
   *  @brief Return the primary flag value (0, 1 or 2)
   */
  unsigned int LP() const { return this->XSS( 1 ); }

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
  double EG() const { return this->XSS( 2 ); }

  /**
   *  @brief Return the photon or binding energy
   */
  double photonOrBindingEnergy() const { return this->EG(); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using ACELAW2 = DiscretePhotonDistribution;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
