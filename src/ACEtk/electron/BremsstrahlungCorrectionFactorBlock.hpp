#ifndef NJOY_ACETK_ELECTRON_BREMSSTRAHLUNGCORRECTIONFACTORBLOCK
#define NJOY_ACETK_ELECTRON_BREMSSTRAHLUNGCORRECTIONFACTORBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron CRB block with the bremsstrahlung production correction factor data
 *
 *  This block is part of the el format.
 *
 *  The BremsstrahlungCorrectionFactorBlock class contains 2 arrays of the
 *  same length:
 *    - The energy points
 *    - The correction factor values
 *
 *  The size NCRB of each (the total number of electron energy points) is
 *  stored in NXS(5).
 */
class BremsstrahlungCorrectionFactorBlock : protected base::ArrayData {

  /* fields */
  
  /* auxiliary functions */
  
public:

  /* constructor */
  
  /* methods */
  

};

using CRB = BremsstrahlungCorrectionFactorBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
