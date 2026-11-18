#ifndef NJOY_ACETK_ELECTRON_BREMSSTRAHLUNGHIGHFREQUENCYBLOCK
#define NJOY_ACETK_ELECTRON_BREMSSTRAHLUNGHIGHFREQUENCYBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron HFB block with the bremsstrahlung high-frequency limit cross sections
 *
 *  This block is part of the el format.
 *
 *  The BremsstrahlungHighFrequencyBlock class contains 2 arrays of the
 *  same length:
 *    - The energy points
 *    - The cross section values
 *
 *  The size NHFB of each (the total number of electron energy points) is
 *  stored in NXS(6).
 */
class BremsstrahlungHighFrequencyBlock : protected base::ArrayData {

  /* fields */
  
  /* auxiliary functions */
  
public:

  /* constructor */

  BremsstrahlungHighFrequencyBlock() = default;

  BremsstrahlungHighFrequencyBlock( const BremsstrahlungHighFrequencyBlock& ) = default;
  BremsstrahlungHighFrequencyBlock( BremsstrahlungHighFrequencyBlock&& ) = default;

  BremsstrahlungHighFrequencyBlock& operator=( const BremsstrahlungHighFrequencyBlock& ) = default;
  BremsstrahlungHighFrequencyBlock& operator=( BremsstrahlungHighFrequencyBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energies         the energy values
   *  @param[in] crosssections    the high-frequency-limit cross section values
   */
  BremsstrahlungHighFrequencyBlock( std::vector< double > energies,
                                    std::vector< double > crosssections ) :
    ArrayData( "HFB",
               std::move( energies ), std::move( crosssections ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the HFB block in the XSS array
   *  @param[in] end     the end iterator of the HFB block in the XSS array
   *  @param[in] nhfb    the number of energy points
   */
  BremsstrahlungHighFrequencyBlock( Iterator begin, Iterator end, unsigned int nhfb ) :
    ArrayData( "HFB", begin, end, nhfb, 2 ) {}
  
  /* methods */
  
  /**
   *  @brief Return the number of energy points
   */
  unsigned int NHFB() const { return this->N(); }
  
  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NHFB(); }
  
  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->darray( 1 ); }
  
  /**
   *  @brief Return the high-frequency-limit bremsstrahlung cross sections
   */
  auto crossSections() const { return this->darray( 2 ); }
  
  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using HFB = BremsstrahlungHighFrequencyBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
