#ifndef NJOY_ACETK_BLOCK_PHOTONUCLEARPRINCIPALCROSSSECTIONBLOCK
#define NJOY_ACETK_BLOCK_PHOTONUCLEARPRINCIPALCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The photonuclear ESZU block with the principal cross sections
 *
 *  The PhotonuclearPrincipalCrossSectionBlock class contains 3 or 4 arrays of the
 *  same length (all values are stored as the natural logarithm):
 *    - the energy points
 *    - the total cross section
 *    - the elastic scattering cross section (optional)
 *    - the heating numbers
 *
 *  The size of each (the total number of energy points) is stored in NXS(3).
 */
class PhotonuclearPrincipalCrossSectionBlock : protected details::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/PhotonuclearPrincipalCrossSectionBlock/src/ctor.hpp"

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

using ESZU = PhotonuclearPrincipalCrossSectionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
