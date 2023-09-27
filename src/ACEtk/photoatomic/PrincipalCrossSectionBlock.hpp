#ifndef NJOY_ACETK_PHOTOATOMIC_PRINCIPALCROSSSECTIONBLOCK
#define NJOY_ACETK_PHOTOATOMIC_PRINCIPALCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace photoatomic {

/**
 *  @class
 *  @brief The photoatomic ESZG block with the principal cross sections
 *
 *  The PrincipalCrossSectionBlock class contains 5 arrays of the
 *  same length (all values are stored as the natural logarithm with the
 *  exception of 0 values which are interpreted as 0 and NOT as exp(0) = 1):
 *    - the energy points
 *    - the incoherent cross section
 *    - the coherent cross section
 *    - the photoelectric cross section
 *    - the pair production cross section
 *
 *  The size of each (the total number of energy points NES) is stored in NXS(3).
 */
class PrincipalCrossSectionBlock : protected block::details::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/photoatomic/PrincipalCrossSectionBlock/src/ctor.hpp"

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
  auto incoherent() const { return this->darray( 2 ); }

  /**
   *  @brief Return the coherent cross section values
   */
  auto coherent() const { return this->darray( 3 ); }

  /**
   *  @brief Return the photo-electric cross section values
   */
  auto photoelectric() const { return this->darray( 4 ); }

  /**
   *  @brief Return the pair production cross section values
   */
  auto pairproduction() const { return this->darray( 5 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using ESZG = PrincipalCrossSectionBlock;

} // photoatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
