#ifndef NJOY_ACETK_ELECTRON_RADIATIONSTOPPINGPOWERBLOCK
#define NJOY_ACETK_ELECTRON_RADIATIONSTOPPINGPOWERBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron RAD block with the radiation stopping power data
 *
 *  This block is part of el and el03 formats.
 *
 *  The RadiationStoppingPowerBlock class contains 3 arrays of the same
 *  length:
 *    - The energy points
 *    - The normalized stopping powers
 *    - The electron-electron bremsstrahlung correction (NEL = 3)
 *
 *  The size NRAD of each (the total number of electron energy points) is
 *  stored in NXS(3).
 */
class RadiationStoppingPowerBlock : protected base::ArrayData {

  /* fields */
  
  /* auxiliary functions */
  
public:

  /* constructor */
  
  /* methods */
  

};

using RAD = RadiationStoppingPowerBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
