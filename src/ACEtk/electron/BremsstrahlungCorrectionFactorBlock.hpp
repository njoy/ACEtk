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

  BremsstrahlungCorrectionFactorBlock() = default;

  BremsstrahlungCorrectionFactorBlock( const BremsstrahlungCorrectionFactorBlock& ) = default;
  BremsstrahlungCorrectionFactorBlock( BremsstrahlungCorrectionFactorBlock&& ) = default;

  BremsstrahlungCorrectionFactorBlock& operator=( const BremsstrahlungCorrectionFactorBlock& ) = default;
  BremsstrahlungCorrectionFactorBlock& operator=( BremsstrahlungCorrectionFactorBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energies       the energy values
   *  @param[in] corrections    the correction factor values
   */
  BremsstrahlungCorrectionFactorBlock( std::vector< double > energies,
                                       std::vector< double > corrections ) :
    ArrayData( "CRB",
               std::move( energies ), std::move( corrections ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the CRB block in the XSS array
   *  @param[in] end     the end iterator of the CRB block in the XSS array
   *  @param[in] ncrb    the number of energy points
   */
  BremsstrahlungCorrectionFactorBlock( Iterator begin, Iterator end, unsigned int ncrb ) :
    ArrayData( "CRB", begin, end, ncrb, 2 ) {}
  
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
