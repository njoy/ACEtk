#ifndef NJOY_ACETK_BLOCK_TABULATEDDATA
#define NJOY_ACETK_BLOCK_TABULATEDDATA

// system includes

// other includes
#include "ACEtk/block/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Tabulated data representing a function y = f(x)
 */
class TabulatedData : protected Base {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/block/TabulatedData/src/generateXSS.hpp"
  #include "ACEtk/block/TabulatedData/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/TabulatedData/src/ctor.hpp"

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const { return this->NB(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return this->XSS( 2, this->NB() ); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const {

    std::size_t nb = this->NB();
    return this->XSS( 2 + nb, nb );
  }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the number of values
   */
  std::size_t NE() const {

    std::size_t nb = this->NB();
    return this->XSS( 2 + 2 * nb );
  }

  /**
   *  @brief Return the number of values
   */
  std::size_t numberValues() const {  return this->NE(); }

  /**
   *  @brief Return the x values
   */
  auto x() const {

    std::size_t nb = this->NB();
    std::size_t ne = this->NE();
    return this->XSS( 3 + 2 * nb, ne );
  }

  /**
   *  @brief Return the y values
   */
  auto y() const {

    std::size_t nb = this->NB();
    std::size_t ne = this->NE();
    return this->XSS( 3 + 2 * nb + ne, ne );
  }

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
