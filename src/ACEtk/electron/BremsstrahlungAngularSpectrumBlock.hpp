#ifndef NJOY_ACETK_ELECTRON_BREMSSTRAHLUNGANGULARSPECTRUMBLOCK
#define NJOY_ACETK_ELECTRON_BREMSSTRAHLUNGANGULARSPECTRUMBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron RKA block with the bremsstrahlung angular spectrum data
 *
 *  This block is part of the el03 format.
 *
 *  The BremsstrahlungAngularSpectrumBlock class contains 1 array with
 *  the ratio values of photon energy over electron energy for the
 *  bremsstrahlung angular spectrum calculation (NEL == 3).
 *
 *  The size NRKA is stored in NXS(10).
 */
class BremsstrahlungAngularSpectrumBlock : protected base::ArrayData {

  /* fields */
  
  /* auxiliary functions */
  
public:

  /* constructor */
  #include "ACEtk/electron/BremsstrahlungAngularSpectrumBlock/src/ctor.hpp"
  
  /* methods */
  
  /**
   *  @brief Return the number of bremstrahlung angular spectrum points
   */
  unsigned int NRKA() const { return this->N(); }
  
  /**
   *  @brief Return the number of bremstrahlung angular spectrum points
   */
  unsigned int numberPhotonEnergyRatios() const { return this->NRKA(); }
  
  /**
   *  @brief Return the energy points for bremstrahlung angular spectrum interpolation
   */
  auto photonEnergyRatios() const { return this->darray( 1 ); }
  
  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using RKA = BremsstrahlungAngularSpectrumBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
