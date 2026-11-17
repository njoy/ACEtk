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

  BremsstrahlungAngularSpectrumBlock() = default;

  BremsstrahlungAngularSpectrumBlock( const BremsstrahlungAngularSpectrumBlock& ) = default;
  BremsstrahlungAngularSpectrumBlock( BremsstrahlungAngularSpectrumBlock&& ) = default;

  BremsstrahlungAngularSpectrumBlock& operator=( const BremsstrahlungAngularSpectrumBlock& ) = default;
  BremsstrahlungAngularSpectrumBlock& operator=( BremsstrahlungAngularSpectrumBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energyratios    the photon energy ratios
   */
  BremsstrahlungAngularSpectrumBlock( std::vector< double > energyratios ) :
    ArrayData( "RKA",
               std::vector< std::vector< double > > { energyratios } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the RKA block in the XSS array
   *  @param[in] end     the end iterator of the RKA block in the XSS array
   *  @param[in] nrka    the number of photon energy ratios
   */
  BremsstrahlungAngularSpectrumBlock( Iterator begin, Iterator end, unsigned int nrka ) :
    ArrayData( "RKA", begin, end, nrka, 1 ) {}
  
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
