#ifndef NJOY_ACETK_BLOCK_POLYNOMIALFISSIONMULTIPLICITY
#define NJOY_ACETK_BLOCK_POLYNOMIALFISSIONMULTIPLICITY

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Polynomial fission multiplicity
 *
 *  The PolynomialFissionMultiplicity class contains the polynomial
 *  representation (LNU = 1) of the fission multiplicity. It is
 *  used in the NU block.
 */
class PolynomialFissionMultiplicity : protected details::Base {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/block/PolynomialFissionMultiplicity/src/generateXSS.hpp"
  #include "ACEtk/block/PolynomialFissionMultiplicity/src/verifySize.hpp"
  #include "ACEtk/block/PolynomialFissionMultiplicity/src/verifyLNU.hpp"

public:

  /* constructor */
  #include "ACEtk/block/PolynomialFissionMultiplicity/src/ctor.hpp"

  /**
   *  @brief Return the representation type (should always be 1)
   */
  unsigned int LNU() const {

    return static_cast< unsigned int >( this->IXSS( 1 ) );
  }

  /**
   *  @brief Return the representation type (should always be 1)
   */
  unsigned int type() const { return this->LNU(); }

  /**
   *  @brief Return the number of polynomial coefficients
   */
  std::size_t NC() const { return this->IXSS( 2 ); }

  /**
   *  @brief Return the number of polynomial coefficients
   */
  std::size_t numberCoefficients() const { return this->NC(); }

  /**
   *  @brief Return the coefficients
   */
  auto C() const {

    return this->XSS( 3, this->numberCoefficients() );
  }

  /**
   *  @brief Return the coefficients
   */
  auto coefficients() const { return this->C(); }

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
