#ifndef NJOY_ACETK_BLOCK_BREMSSTRAHLUNGBLOCK
#define NJOY_ACETK_BLOCK_BREMSSTRAHLUNGBLOCK

// system includes

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The photoatomic BREML block with the average electron energy
 *         after Bremsstrahlung
 *
 *  This block is part of the eprdata formats.
 *
 *  The BremsstrahlungBlock class contains 2 arrays of the same length:
 *    - the energy points
 *    - the average energy remaining after Bremsstrahlung
 *
 *  The size NBL of each (the total number of energy points) is stored in NXS(12).
 */
class BremsstrahlungBlock : protected block::details::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/electron/BremsstrahlungBlock/src/ctor.hpp"

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

using BREML = BremsstrahlungBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
