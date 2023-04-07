#ifndef NJOY_ACETK_BLOCK_NBODYPHASESPACEDISTRIBUTION
#define NJOY_ACETK_BLOCK_NBODYPHASESPACEDISTRIBUTION

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/block/details/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The energy distribution uses the N-body phase space formalism
 *
 *  The NBodyPhaseSpaceDistribution class contains two parameter values that
 *  determine the distribution: the number of particles in the system and the
 *  total mass ratio. It is used in the DLW block as ACE LAW 66.
 */
class NBodyPhaseSpaceDistribution : protected details::Base {

  /* fields */
  double emin_;
  double emax_;

  /* auxiliary functions */
  #include "ACEtk/block/NBodyPhaseSpaceDistribution/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/NBodyPhaseSpaceDistribution/src/ctor.hpp"

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::NBodyPhaseSpace;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::NBodyPhaseSpace;
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
   *  @brief Return the number of particles in the system
   */
  unsigned int NPSX() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the number of particles in the system
   */
  unsigned int numberParticles() const { return this->NPSX(); }

  /**
   *  @brief Return the total mass ratio of the particles
   */
  double AP() const { return this->XSS( 2 ); }

  /**
   *  @brief Return the total mass ratio of the particles
   */
  double totalMassRatio() const { return this->AP(); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using ACELAW66 = NBodyPhaseSpaceDistribution;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
