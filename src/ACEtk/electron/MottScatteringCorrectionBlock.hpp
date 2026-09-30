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

  void verifyMottCorrectionIndex( const std::size_t index ) const {

    if ( ( index < 1 ) || ( index >= this->M() ) ) {

      Log::error( "Illegal index argument into the {} block", this->name() );
      Log::info( "Index value: {}", index );
      Log::info( "{} accepts an index between 1 and {} inclusively",
                 this->name(), this->M() - 1 );
      throw std::out_of_range( this->name() );
    }
  }
  
public:

  /* constructor */

  MottScatteringCorrectionBlock() = default;

  MottScatteringCorrectionBlock( const MottScatteringCorrectionBlock& ) = default;
  MottScatteringCorrectionBlock( MottScatteringCorrectionBlock&& ) = default;

  MottScatteringCorrectionBlock& operator=( const MottScatteringCorrectionBlock& ) = default;
  MottScatteringCorrectionBlock& operator=( MottScatteringCorrectionBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energies             the energy values
   *  @param[in] corrections0deg      the Mott scattering corrections at 0 degrees
   *  @param[in] corrections45deg     the Mott scattering corrections at 45 degrees
   *  @param[in] corrections90deg     the Mott scattering corrections at 90 degrees
   *  @param[in] corrections135deg    the Mott scattering corrections at 135 degrees
   *  @param[in] corrections180deg    the Mott scattering corrections at 180 degrees
   */
  MottScatteringCorrectionBlock( std::vector< double > energies,
                                 std::vector< double > corrections0deg,
                                 std::vector< double > corrections45deg,
                                 std::vector< double > corrections90deg,
                                 std::vector< double > corrections135deg,
                                 std::vector< double > corrections180deg ) :
    ArrayData( "MOT",
               std::move( energies ), std::move( corrections0deg ),
               std::move( corrections45deg ), std::move( corrections90deg ),
               std::move( corrections135deg ), std::move( corrections180deg ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the ESZG block in the XSS array
   *  @param[in] end     the end iterator of the ESZG block in the XSS array
   *  @param[in] nmot    the number of energy points
   */
  MottScatteringCorrectionBlock( Iterator begin, Iterator end, unsigned int nmot ) :
    ArrayData( "MOT", begin, end, nmot, 6 ) {}
  
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
  auto energies() const { return this->darray( 1 ); }
  
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
