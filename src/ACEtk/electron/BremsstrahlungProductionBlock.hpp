#ifndef NJOY_ACETK_ELECTRON_BREMSSTRAHLUNGPRODUCTIONBLOCK
#define NJOY_ACETK_ELECTRON_BREMSSTRAHLUNGPRODUCTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/MatrixData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron XSB block with the bremsstrahlung photon production data
 *
 *  This block is part of el03 format.
 *
 *  The BremsstrahlungProductionBlock class contains a variable number of
 *  arrays of differing lengths:
 *    - The electron energy points
 *    - The photon energy ratio points
 *    - The cross section values
 *
 *  The size NEB of the electron energy values array (the total number of
 *  electron energy points) is stored in NXS(5). The size NPB of the photon
 *  energy ratio values array (the total number of photon energy points) is
 *  stored in NXS(6). The size of the bremsstrahlung production cross
 *  section array (the number of values for interpolation) is NEB*NPB.
 */
class BremsstrahlungProductionBlock : protected base::MatrixData {

  /* fields */
  
  /* auxiliary functions */
  
public:

  /* constructor */
  #include "ACEtk/electron/BremsstrahlungProductionBlock/src/ctor.hpp"
  
  /* methods */
  
  /**
   *  @brief Return the number of electron energy points
   */
  unsigned int NEB() const { return this->M(); }
  
  /**
   *  @brief Return the number of electron energy points
   */
  unsigned int numberElectronEnergies() const { return this->NEB(); }
  
  /**
   *  @brief Return the number of photon energy ratio points
   */
  unsigned int NPB() const { return this->N(); }
  
  /**
   *  @brief Return the number of photon energy ratio points
   */
  unsigned int numberPhotonRatios() const { return this->NPB(); }
  
  /**
   *  @brief Return the number of cross section values
   */
  unsigned int numberCrossSections() const { return this->numberValues(); }
  
  /**
   *  @brief Return a single electron energy point
   *
   *  @param[in] index    the electron energy index (one-based)
   */
  double electronEnergy( std::size_t index ) const {
    
    return this->drowLabel( index );
  }
  
  /**
   *  @brief Return the electron energy points
   */
  auto electronEnergies() const { return this->drowLabels(); }
  
  /**
   *  @brief Return a single photon energy ratio point
   *
   *  @param[in] index    the photon energy ratio index (one-based)
   */
  double photonRatio( std::size_t index ) const {
    
    return this->dcolumnLabel( index );
  }
  
  /**
   *  @brief Return the photon energy ratio points
   */
  auto photonRatios() const { return this->dcolumnLabels(); }
  
  /**
   *  @brief Return a single bremsstrahlung cross section value
   *
   *  @param[in] eeIndex    the electron energy index (one-based)
   *  @param[in] prIndex    the photon energy ratio index (one-based)
   */
  double crossSection( std::size_t eeIndex, std::size_t prIndex ) const {
    
    return this->dvalue( eeIndex, prIndex );
  }
  
  /**
   *  @brief Return the cross section values for a given electron energy index
   *
   *  @param[in] index    the electron energy index (one-based)
   */
  auto crossSections( std::size_t index ) const {
    
    return this->drow( index );
  }
  
  /**
   *  @brief Return the bremsstrahlung cross section data array
   */
  auto crossSectionData() const { return this->dmatrix(); }
  
  using MatrixData::empty;
  using MatrixData::name;
  using MatrixData::length;
  using MatrixData::XSS;
  using MatrixData::begin;
  using MatrixData::end;
};

using XSB = BremsstrahlungProductionBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
