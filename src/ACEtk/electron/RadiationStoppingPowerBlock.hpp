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
  #include "ACEtk/electron/RadiationStoppingPowerBlock/src/ctor.hpp"
  
  /* methods */
  
  /**
   *  @brief Return the number of energy points
   */
  unsigned int NRAD() const { return this->N(); }
  
  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NRAD(); }
  
  /**
   *  @brief Return the energy points for radiation stopping power interpolation
   */
  auto energies() const { return this->darray( 1 ); }
  
  /**
   *  @brief Return the normalized radiation stopping powers
   */
  auto stoppingPowers() const { return this->darray( 2 ); }
  
  /**
   *  @brief Return the electron-electron bremsstrahlung correction factors (NEL == 3)
   */
  auto corrections() const {
    
    return ( this->M() == 3 )
           ? std::optional< decltype( this->darray( 3 ) ) > { this->darray( 3 ) }
           : std::nullopt;
  }
  
  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using RAD = RadiationStoppingPowerBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
