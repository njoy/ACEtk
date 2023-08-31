#ifndef NJOY_ACETK_BLOCK_PHOTOATOMICELECTRONBREMSSTRAHLUNGBLOCK
#define NJOY_ACETK_BLOCK_PHOTOATOMICELECTRONBREMSSTRAHLUNGBLOCK

// system includes

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The photoatomic BREML block with the electron Bremsstrahlung energy
 *         loss data
 *
 *  This block is part of the eprdata formats.
 *
 *  The PhotoatomicElectronBremsstrahlungBlock class contains 2 arrays of the
 *  same length:
 *    - the energy points
 *    - the average energy remaining after loss to Bremsstrahlung
 *
 *  The size NBL of each (the total number of energy points) is stored in NXS(12).
 */
class PhotoatomicElectronBremsstrahlungBlock : protected details::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/PhotoatomicElectronBremsstrahlungBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NBL() const { return this->N(); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NBL(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->darray( 1 ); }

  /**
   *  @brief Return the average remaining energy after loss to Bremsstrahlung
   */
  auto energyAfterBremsstrahlung() const { return this->darray( 2 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using BREML = PhotoatomicElectronBremsstrahlungBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
