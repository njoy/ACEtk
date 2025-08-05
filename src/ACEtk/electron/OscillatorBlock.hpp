#ifndef NJOY_ACETK_ELECTRON_OSCILLATORBLOCK
#define NJOY_ACETK_ELECTRON_OSCILLATORBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron CRB block with the oscillator descriptions
 *
 *  This block is part of the el03 format.
 *
 *  The OscillatorBlock class contains 2 arrays of the
 *  same length:
 *    - The level occupation numbers
 *    - The level binding energies
 *
 *  The size NOSC of each (the total number of oscillator points) is stored
 *  in NXS(11).
 */
class OscillatorBlock : protected base::ArrayData {

  /* fields */
  
  /* auxiliary functions */
  
public:

  /* constructor */
  
  /* methods */
  

};

using OSC = OscillatorBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
