#ifndef NJOY_ACETK_ELECTRON_RILEYCROSSSECTIONBLOCK
#define NJOY_ACETK_ELECTRON_RILEYCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron RLY block with the Riley cross section data
 *
 *  This block is part of el and el03 formats.
 *
 *  The RileyCrossSectionBlock class contains 9 arrays of the same length.
 *  Each array contains an energy value from 1 to 256 keV followed by the
 *  set of Riley scattering cross section parameters at that energy.
 *
 *  The size of each Riley set array is 14 (1 energy + 13 parameters).
 *  This size value is hard-coded and is not stored in the NXS array.
 */
class RileyCrossSectionBlock : protected base::ArrayData {

  /* fields */
  
  /* auxiliary functions */
  
public:

  /* constructor */
  
  /* methods */
  

};

using RLY = RileyCrossSectionBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
