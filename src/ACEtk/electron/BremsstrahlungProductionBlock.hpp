#ifndef NJOY_ACETK_ELECTRON_BREMSSTRAHLUNGPRODUCTIONBLOCK
#define NJOY_ACETK_ELECTRON_BREMSSTRAHLUNGPRODUCTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron XSB block with the bremsstrahlung photon production data
 *
 *  This block is part of el03 format.
 *
 *  The BremsstrahlungProductionBlock class contains a variable number of
 *  arrays of differing lengths:
 *    - The electron energy points
 *    - The photon energy ratio points
 *    - The cross section values
 *
 *  The size NEB of the electron energy values array (the total number of
 *  electron energy points) is stored in NXS(5). The size NPB of the photon
 *  energy ratio values array (the total number of photon energy points) is
 *  stored in NXS(6). The size of the bremsstrahlung production cross
 *  section array (the number of values for interpolation) is NEB*NPB.
 */
class BremsstrahlungProductionBlock : protected base::ArrayData {

  /* fields */
  
  /* auxiliary functions */
  
public:

  /* constructor */
  
  /* methods */
  

};

using XSB = BremsstrahlungProductionBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
