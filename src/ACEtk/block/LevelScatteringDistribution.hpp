#ifndef NJOY_ACETK_BLOCK_LEVELSCATTERING
#define NJOY_ACETK_BLOCK_LEVELSCATTERING

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"

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
 *  The content of the XSS array are only C1 and C2
 */
class LevelScatteringDistribution : protected details::Base {

  /* fields */
  double emin_;
  double emax_;

  /* auxiliary functions */
  #include "ACEtk/block/LevelScatteringDistribution/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/LevelScatteringDistribution/src/ctor.hpp"

  /**
   *  @brief Return the minimum incident energy for the distribution
   */
  double minimumIncidentEnergy() const { return this->emin_; }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const { return this->emax_; }

  /**
   *  @brief Return the value of C1 = ( A + 1 ) / A * abs( Q )
   */
  double C1() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the value of C2 = ( A / ( A + 1 ) )^2
   */
  double C2() const { return this->XSS( 2 ); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using ACELAW3 = LevelScatteringDistribution;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
