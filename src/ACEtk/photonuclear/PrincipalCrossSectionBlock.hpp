#ifndef NJOY_ACETK_PHOTONUCLEAR_PRINCIPALCROSSSECTIONBLOCK
#define NJOY_ACETK_PHOTONUCLEAR_PRINCIPALCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace photonuclear {

/**
 *  @class
 *  @brief The photonuclear ESZU block with the principal cross sections
 *
 *  The PrincipalCrossSectionBlock class contains 3 or 4 arrays of the same
 *  length:
 *    - the energy points
 *    - the total cross section
 *    - the elastic scattering cross section (optional)
 *    - the heating numbers
 *
 *  The size of each (the total number of energy points) is stored in NXS(3).
 */
class PrincipalCrossSectionBlock : protected block::details::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/photonuclear/PrincipalCrossSectionBlock/src/ctor.hpp"

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
  auto energies() const { return this->darray( 1 ); }

  /**
   *  @brief Return the incoherent cross section values
   */
  auto total() const { return this->darray( 2 ); }

  /**
   *  @brief Return the coherent cross section values
   */
  auto elastic() const { return this->M() == 3 ? this->emptyArray()
                                               : this->darray( 3 ); }

  /**
   *  @brief Return the average heating cross section values
   */
  auto heating() const { return this->darray( this->M() ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using ESZU = PrincipalCrossSectionBlock;

} // photonuclear namespace
} // ACEtk namespace
} // njoy namespace

#endif
