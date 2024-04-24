#ifndef NJOY_ACETK_CONTINUOUS_NBODYPHASESPACEDISTRIBUTION
#define NJOY_ACETK_CONTINUOUS_NBODYPHASESPACEDISTRIBUTION

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/Base.hpp"
#include "ACEtk/base/ColumnData.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief The energy distribution uses the N-body phase space formalism
 *
 *  The NBodyPhaseSpaceDistribution class contains two parameter values that
 *  determine the distribution: the number of particles in the system and the
 *  total mass ratio. It is used in the DLW block as ACE LAW 66.
 */
class NBodyPhaseSpaceDistribution : protected base::Base {

  /* fields */
  double emin_ = 0.0;
  double emax_ = 0.0;

  /* auxiliary functions */
  #include "ACEtk/continuous/NBodyPhaseSpaceDistribution/src/generateXSS.hpp"
  #include "ACEtk/continuous/NBodyPhaseSpaceDistribution/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/continuous/NBodyPhaseSpaceDistribution/src/ctor.hpp"

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
  unsigned int NPSX() const { return this->IXSS( 1 ); }

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

  /**
   *  @brief Return the interpolation flag
   */
  int interpolation() const { return this->IXSS( 3 ); }

  /**
   *  @brief Return the number of normalised energy values
   */
  std::size_t numberValues() const { return this->IXSS( 4 ); }

  /**
   *  @brief Return the normalised energy values
   */
  auto values() const {

    return this->XSS( 5, this->numberValues() );
  }

  /**
   *  @brief Return the pdf values
   */
  auto pdf() const {

    return this->XSS( 5 + this->numberValues(), this->numberValues() );
  }

  /**
   *  @brief Return the cdf values
   */
  auto cdf() const {

    return this->XSS( 5 + 2 * this->numberValues(), this->numberValues() );
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using ACELAW66 = NBodyPhaseSpaceDistribution;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
