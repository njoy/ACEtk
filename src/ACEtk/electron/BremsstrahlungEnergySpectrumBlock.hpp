#ifndef NJOY_ACETK_ELECTRON_BREMSSTRAHLUNGENERGYSPECTRUMBLOCK
#define NJOY_ACETK_ELECTRON_BREMSSTRAHLUNGENERGYSPECTRUMBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron RKT block with the bremsstrahlung energy spectrum data
 *
 *  This block is part of the el03 format.
 *
 *  The BremsstrahlungEnergySpectrumBlock class contains 1 array with
 *  the ratio values of photon energy over electron energy for the
 *  bremsstrahlung energy spectrum calculation (NEL == 3).
 *
 *  The size NRKT is stored in NXS(9).
 */
class BremsstrahlungEnergySpectrumBlock : protected base::ArrayData {

  /* fields */
  
  /* auxiliary functions */
  
public:

  /* constructor */
  #include "ACEtk/electron/BremsstrahlungEnergySpectrumBlock/src/ctor.hpp"
  
  /* methods */
  
  /**
   *  @brief Return the number of bremstrahlung energy spectrum points
   */
  unsigned int NRKT() const { return this->N(); }
  
  /**
   *  @brief Return the number of bremstrahlung energy spectrum points
   */
  unsigned int numberPhotonEnergyRatios() const { return this->NRKT(); }
  
  /**
   *  @brief Return the energy points for bremstrahlung energy spectrum interpolation
   */
  auto photonEnergyRatios() const { return this->darray( 1 ); }
  
  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using RKT = BremsstrahlungEnergySpectrumBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
