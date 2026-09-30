#ifndef NJOY_ACETK_CONTINUOUS_LEVELSCATTERING
#define NJOY_ACETK_CONTINUOUS_LEVELSCATTERING

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/TwoParameterDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

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
class LevelScatteringDistribution : protected base::TwoParameterDistribution {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  LevelScatteringDistribution() = default;

  LevelScatteringDistribution( const LevelScatteringDistribution& ) = default;
  LevelScatteringDistribution( LevelScatteringDistribution&& ) = default;

  LevelScatteringDistribution& operator=( const LevelScatteringDistribution& ) = default;
  LevelScatteringDistribution& operator=( LevelScatteringDistribution&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] emin    the minimum energy for the distribution
   *  @param[in] emax    the maximum energy for the distribution
   *  @param[in] c1      the value of C1 = ( A + 1 ) / A * abs( Q )
   *  @param[in] c2      the value of C2 = ( A / ( A + 1 ) )^2
   */
  LevelScatteringDistribution( double emin, double emax, double c1, double c2 ) :
    TwoParameterDistribution( "LevelScatteringDistribution", emin, emax, c1, c2 ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the block
   *  @param[in] end     the end iterator of the block
   *  @param[in] emin    the minimum energy for the distribution
   *  @param[in] emax    the maximum energy for the distribution
   */
  LevelScatteringDistribution( Iterator begin, Iterator end,
                               double emin, double emax ) :
    TwoParameterDistribution( "LevelScatteringDistribution", begin, end, emin, emax ) {}

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

    return TwoParameterDistribution::minimumIncidentEnergy();
  }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const {

    return TwoParameterDistribution::maximumIncidentEnergy();
  }

  /**
   *  @brief Return the value of C1 = ( A + 1 ) / A * abs( Q )
   */
  double C1() const { return TwoParameterDistribution::C1(); }

  /**
   *  @brief Return the value of C2 = ( A / ( A + 1 ) )^2
   */
  double C2() const { return TwoParameterDistribution::C2(); }

  using TwoParameterDistribution::empty;
  using TwoParameterDistribution::name;
  using TwoParameterDistribution::length;
  using TwoParameterDistribution::XSS;
  using TwoParameterDistribution::begin;
  using TwoParameterDistribution::end;
};

using ACELAW3 = LevelScatteringDistribution;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
