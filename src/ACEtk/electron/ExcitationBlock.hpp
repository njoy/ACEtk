#ifndef NJOY_ACETK_ELECTRON_EXCITATIONBLOCK
#define NJOY_ACETK_ELECTRON_EXCITATIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron EXCIT block with the electron excitation energy loss data
 *
 *  This block is part of the eprdata formats.
 *
 *  The ExcitationBlock class contains 2 arrays of the same length:
 *    - the energy points
 *    - the average excitation energy loss values
 *
 *  The size NXL of each (the total number of excitation energy points) is
 *  stored in NXS(9).
 */
class ExcitationBlock : protected block::details::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/electron/ExcitationBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NXL() const { return this->N(); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NXL(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->darray( 1 ); }

  /**
   *  @brief Return the average excitation energy loss values
   */
  auto excitationEnergyLoss() const { return this->darray( 2 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using EXCIT = ExcitationBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
