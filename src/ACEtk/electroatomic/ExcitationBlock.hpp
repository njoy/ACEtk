#ifndef NJOY_ACETK_ELECTROATOMIC_EXCITATIONBLOCK
#define NJOY_ACETK_ELECTROATOMIC_EXCITATIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electroatomic {

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
class ExcitationBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/electroatomic/ExcitationBlock/src/ctor.hpp"

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

} // electroatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
