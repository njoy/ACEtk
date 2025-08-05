#ifndef NJOY_ACETK_ELECTRON_TRANSITIONENERGYBLOCK
#define NJOY_ACETK_ELECTRON_TRANSITIONENERGYBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron EKT block with the transition energy data
 *
 *  This block is part of el and el03 formats.
 *
 *  The TransitionEnergyBlock class contains 3 arrays of the same
 *  length:
 *    - The energy points
 *    - The normalized stopping powers
 *    - The electron-electron bremsstrahlung correction (NEL = 3)
 *
 *  The size NRAD of each (the total number of electron energy points) is
 *  stored in NXS(3).
 */
class TransitionEnergyBlock : protected base::ArrayData {

  /* fields */
  
  /* auxiliary functions */
  
public:

  /* constructor */
  #include "ACEtk/electron/TransitionEnergyBlock/src/ctor.hpp"
  
  /* methods */
  
  
  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using EKT = TransitionEnergyBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
