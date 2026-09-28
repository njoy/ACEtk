#ifndef NJOY_ACETK_BLOCK_BREMSSTRAHLUNGBLOCK
#define NJOY_ACETK_BLOCK_BREMSSTRAHLUNGBLOCK

// system includes
#include <stdexcept>

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electroatomic {

/**
 *  @class
 *  @brief The electron BREML block with the average electron energy after
 *         Bremsstrahlung
 *
 *  This block is part of the eprdata formats.
 *
 *  The BremsstrahlungBlock class contains 2 arrays of the same length:
 *    - the energy points
 *    - the average energy remaining after Bremsstrahlung
 *
 *  For NEPR = 3, the second array contains the average energy loss instead.
 *
 *  The size NBL of each (the total number of energy points) is stored in NXS(12).
 */
class BremsstrahlungBlock : protected base::ArrayData {

  /* fields */
  unsigned int nepr_ = 1;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/electroatomic/BremsstrahlungBlock/src/ctor.hpp"

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
   *
   *  Requires NEPR = 1.
   */
  auto energyAfterBremsstrahlung() const {

    if ( this->nepr_ != 1 ) {

      throw std::logic_error( "BREML remaining energy requires NEPR = 1" );
    }
    return this->darray( 2 );
  }

  /**
   *  @brief Return the average energy loss (requires NEPR = 3)
   */
  auto energyLoss() const {

    if ( this->nepr_ != 3 ) {

      throw std::logic_error( "BREML energy loss requires NEPR = 3" );
    }
    return this->darray( 2 );
  }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using BREML = BremsstrahlungBlock;

} // electroatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
