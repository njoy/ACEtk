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
 *  The LevelScattering class contains two parameter values that determine the
 *  level scattering distribution (in the centre of mass):
 *    Eprime = C2 * ( E - C1 )
 *  with:
 *    C1 = ( A + 1 ) / A * abs( Q )
 *    C2 = ( A / ( A + 1 ) )^2
 *
 *  The content of the XSS array are only C1 and C2
 */
class LevelScattering : protected details::Base {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/block/LevelScattering/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/LevelScattering/src/ctor.hpp"

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

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
