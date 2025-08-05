#ifndef NJOY_ACETK_ELECTRON_MOTTSCATTERINGCORRECTIONBLOCK
#define NJOY_ACETK_ELECTRON_MOTTSCATTERINGCORRECTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron MOT block with the Mott scattering correction data
 *
 *  This block is part of el and el03 formats.
 *
 *  The MottScatteringCorrectionBlock class contains 6 arrays of the same
 *  length:
 *    - The energy points
 *    - The Mott scattering correction h(theta) for theta = 0
 *    - The Mott scattering correction h(theta) for theta = pi/4
 *    - The Mott scattering correction h(theta) for theta = pi/2
 *    - The Mott scattering correction h(theta) for theta = 3*pi/4
 *    - The Mott scattering correction h(theta) for theta = pi
 *
 *  The size NMOT of each (the total number of Mott scattering cross
 *  section energy points) is stored in NXS(4).
 */
class MottScatteringCorrectionBlock : protected base::ArrayData {

  /* fields */
  
  /* auxiliary functions */
  
public:

  /* constructor */
  
  /* methods */
  

};

using MOT = MottScatteringCorrectionBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
