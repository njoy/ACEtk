#ifndef NJOY_ACETK_BLOCK_LEVELSCATTERING
#define NJOY_ACETK_BLOCK_LEVELSCATTERING

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/block/details/BaseTwoParameterDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The energy distribution uses analytical level scattering
 *
 *  The LevelScatteringDistribution class contains two parameter values that
 *  determine the level scattering distribution (in the centre of mass):
 *    Eprime = C2 * ( E - C1 )
 *  with:
 *    C1 = ( A + 1 ) / A * abs( Q )
 *    C2 = ( A / ( A + 1 ) )^2
 *
 *  It is used in the DLW block as ACE LAW 3.
 */
class LevelScatteringDistribution :
  protected details::BaseTwoParameterDistribution {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/LevelScatteringDistribution/src/ctor.hpp"

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::LevelScattering;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::LevelScattering;
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
   *  @brief Return the value of C1 = ( A + 1 ) / A * abs( Q )
   */
  double C1() const { return BaseTwoParameterDistribution::C1(); }

  /**
   *  @brief Return the value of C2 = ( A / ( A + 1 ) )^2
   */
  double C2() const { return BaseTwoParameterDistribution::C2(); }

  using BaseTwoParameterDistribution::empty;
  using BaseTwoParameterDistribution::name;
  using BaseTwoParameterDistribution::length;
  using BaseTwoParameterDistribution::XSS;
  using BaseTwoParameterDistribution::begin;
  using BaseTwoParameterDistribution::end;
};

using ACELAW3 = LevelScatteringDistribution;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
