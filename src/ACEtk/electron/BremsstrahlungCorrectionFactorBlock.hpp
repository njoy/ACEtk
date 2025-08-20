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
  #include "ACEtk/electron/BremsstrahlungCorrectionFactorBlock/src/ctor.hpp"
  
  /* methods */
  
  /**
   *  @brief Return the number of energy points
   */
  unsigned int NCRB() const { return this->N(); }
  
  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NCRB(); }
  
  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->darray( 1 ); }
  
  /**
   *  @brief Return the bremsstrahlung production correction factors
   */
  auto corrections() const { return this->darray( 2 ); }
  
  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using CRB = BremsstrahlungCorrectionFactorBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
