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
  #include "ACEtk/electron/MottScatteringCorrectionBlock/src/verifyMottCorrectionIndex.hpp"
  
public:

  /* constructor */
  #include "ACEtk/electron/MottScatteringCorrectionBlock/src/ctor.hpp"
  
  /* methods */
  
  /**
   *  @brief Return the number of energy points
   */
  unsigned int NMOT() const { return this->N(); }
  
  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NMOT(); }
  
  /**
   *  @brief Return the energy points
   */
  auto energies() const { return this->darray(1); }
  
  /**
   *  @brief Return the Mott scattering correction for an index
   *
   *  When the index is out of range an std::out_of_range exception is
   *  thrown (debug mode only).
   *
   *  @param[in] index   the index (1 to 5, one-based)
   */
  auto mottScatteringCorrection( std::size_t index ) const {
    
    #ifndef NDEBUG
    this->verifyMottCorrectionIndex( index );
    #endif
    return this->darray( 1 + index );
  }
  
  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using MOT = MottScatteringCorrectionBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
