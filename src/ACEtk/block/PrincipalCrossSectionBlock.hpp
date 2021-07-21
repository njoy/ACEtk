#ifndef NJOY_ACETK_BLOCK_PRINCIPALCROSSSECTIONS
#define NJOY_ACETK_BLOCK_PRINCIPALCROSSSECTIONS

// system includes

// other includes
#include "ACEtk/block/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The ESZ block with the CE principal cross sections
 *
 *  The PrincipalCrossSectionBlock class contains 5 arrays of the same length:
 *    - the energy points
 *    - the total cross section
 *    - the elastic scattering cross section
 *    - the projectile disappearance cross section
 *    - the average heating numbers
 *
 *  The size of each (the total number of energy points) is stored in NXS(3).
 *  When constructing the XSS array, this block will provide the NES = NXS(3)
 *  value.
 */
class PrincipalCrossSectionBlock : protected Base {

  /* fields */
  int nes_;

  /* auxiliary functions */
  #include "ACEtk/block/PrincipalCrossSectionBlock/src/subrange.hpp"
  #include "ACEtk/block/PrincipalCrossSectionBlock/src/generateXSS.hpp"
  #include "ACEtk/block/PrincipalCrossSectionBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/PrincipalCrossSectionBlock/src/ctor.hpp"

  /* methods */
  int NES() const { return this->nes_; }
  int numberEnergyPoints() const { return this->NES(); }

  auto energies() const { return this->subrange( 0 ); }
  auto total() const { return this->subrange( 1 ); }
  auto disappearance() const { return this->subrange( 2 ); }
  auto elastic() const { return this->subrange( 3 ); }
  auto heating() const { return this->subrange( 4 ); }
};

using ESZ = PrincipalCrossSectionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
