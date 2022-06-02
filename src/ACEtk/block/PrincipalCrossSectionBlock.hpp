#ifndef NJOY_ACETK_BLOCK_PRINCIPALCROSSSECTIONBLOCK
#define NJOY_ACETK_BLOCK_PRINCIPALCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy ESZ block with the principal cross sections
 *
 *  The PrincipalCrossSectionBlock class contains 5 arrays of the same length:
 *    - the energy points
 *    - the total cross section
 *    - the elastic scattering cross section
 *    - the projectile disappearance cross section
 *    - the average heating numbers
 *
 *  The size of each (the total number of energy points) is stored in NXS(3).
 */
class PrincipalCrossSectionBlock : protected details::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/PrincipalCrossSectionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NES() const { return this->N(); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NES(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->array( 1 ); }

  /**
   *  @brief Return the total cross section values
   */
  auto total() const { return this->array( 2 ); }

  /**
   *  @brief Return the projectile disappearance cross section values
   */
  auto disappearance() const { return this->array( 3 ); }

  /**
   *  @brief Return the elastic cross section values
   */
  auto elastic() const { return this->array( 4 ); }

  /**
   *  @brief Return the average heating cross section values
   */
  auto heating() const { return this->array( 5 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using ESZ = PrincipalCrossSectionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
