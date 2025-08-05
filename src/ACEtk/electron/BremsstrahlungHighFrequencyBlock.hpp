#ifndef NJOY_ACETK_ELECTRON_BREMSSTRAHLUNGHIGHFREQUENCYBLOCK
#define NJOY_ACETK_ELECTRON_BREMSSTRAHLUNGHIGHFREQUENCYBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron CRB block with the bremsstrahlung high-frequency limit cross sections
 *
 *  This block is part of the el format.
 *
 *  The BremsstrahlungHighFrequencyBlock class contains 2 arrays of the
 *  same length:
 *    - The energy points
 *    - The cross section values
 *
 *  The size NHFB of each (the total number of electron energy points) is
 *  stored in NXS(6).
 */
class BremsstrahlungHighFrequencyBlock : protected base::ArrayData {

  /* fields */
  
  /* auxiliary functions */
  
public:

  /* constructor */
  
  /* methods */
  

};

using HFB = BremsstrahlungHighFrequencyBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
