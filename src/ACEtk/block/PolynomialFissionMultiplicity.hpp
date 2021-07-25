#ifndef NJOY_ACETK_BLOCK_POLYNOMIALFISSIONMULTIPLICITY
#define NJOY_ACETK_BLOCK_POLYNOMIALFISSIONMULTIPLICITY

// system includes

// other includes
#include "ACEtk/block/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Polynomial fission multiplicity
 *
 *  The PolynomialFissionMultiplicity class contains the polynomial
 *  representation of fission multiplicity.
 */
class PolynomialFissionMultiplicity : protected Base {

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
  std::size_t LNU() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the representation type (should always be 1)
   */
  std::size_t type() const { return this->LNU(); }

  /**
   *  @brief Return the number of polynomial coefficients
   */
  std::size_t NC() const { return this->XSS( 2 ); }

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
