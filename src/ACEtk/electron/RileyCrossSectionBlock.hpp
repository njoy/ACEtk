#ifndef NJOY_ACETK_ELECTRON_RILEYCROSSSECTIONBLOCK
#define NJOY_ACETK_ELECTRON_RILEYCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electron {

/**
 *  @class
 *  @brief The electron RLY block with the Riley cross section data
 *
 *  This block is part of el and el03 formats.
 *
 *  The RileyCrossSectionBlock class contains 9 arrays of the same length.
 *  Each array contains an energy value from 1 to 256 keV followed by the
 *  set of Riley scattering cross section parameters at that energy.
 *
 *  The size of each Riley set array is 14 (1 energy + 13 parameters).
 *  This size value is hard-coded and is not stored in the NXS array.
 */
class RileyCrossSectionBlock : protected base::ArrayData {

  /* fields */
  
  /* auxiliary functions */

  void verifyRileyIndex( const std::size_t index ) const {

    if ( ( index < 1 ) || ( index > this->M() ) ) {

      Log::error( "Illegal index argument into the {} block", this->name() );
      Log::info( "Index value: {}", index );
      Log::info( "{} accepts an index between 1 and {} inclusively",
                 this->name(), this->M() );
      throw std::out_of_range( this->name() );
    }
  }
  
public:

  /* constructor */

  RileyCrossSectionBlock() = default;

  RileyCrossSectionBlock( const RileyCrossSectionBlock& ) = default;
  RileyCrossSectionBlock( RileyCrossSectionBlock&& ) = default;

  RileyCrossSectionBlock& operator=( const RileyCrossSectionBlock& ) = default;
  RileyCrossSectionBlock& operator=( RileyCrossSectionBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] rileySet256keV    the Riley cross section parameters at 256 keV
   *  @param[in] rileySet128keV    the Riley cross section parameters at 128 keV
   *  @param[in] rileySet64keV     the Riley cross section parameters at 64 keV
   *  @param[in] rileySet32keV     the Riley cross section parameters at 32 keV
   *  @param[in] rileySet16keV     the Riley cross section parameters at 16 keV
   *  @param[in] rileySet8keV      the Riley cross section parameters at 8 keV
   *  @param[in] rileySet4keV      the Riley cross section parameters at 4 keV
   *  @param[in] rileySet2keV      the Riley cross section parameters at 2 keV
   *  @param[in] rileySet1keV      the Riley cross section parameters at 1 keV
   */
  RileyCrossSectionBlock( std::vector< double > rileySet256keV,
                          std::vector< double > rileySet128keV,
                          std::vector< double > rileySet64keV,
                          std::vector< double > rileySet32keV,
                          std::vector< double > rileySet16keV,
                          std::vector< double > rileySet8keV,
                          std::vector< double > rileySet4keV,
                          std::vector< double > rileySet2keV,
                          std::vector< double > rileySet1keV ) :
    ArrayData( "RLY",
               std::vector< std::vector< double > > {
                   rileySet256keV, rileySet128keV, rileySet64keV,
                   rileySet32keV, rileySet16keV, rileySet8keV,
                   rileySet4keV, rileySet2keV, rileySet1keV } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the ESZG block in the XSS array
   *  @param[in] end     the end iterator of the ESZG block in the XSS array
   */
  RileyCrossSectionBlock( Iterator begin, Iterator end ) :
    ArrayData( "RLY", begin, end, 14, 9 ) {}
  
  /* methods */
  
  /**
   *  @brief Return the number of Riley cross section parameter sets
   */
  unsigned int NRLY() const { return 9; }
  
  /**
   *  @brief Return the number of Riley cross section parameter sets
   */
  unsigned int numberEnergyPoints() const { return this->NRLY(); }
  
  /**
   *  @brief Return the length of a Riley cross section parameter set
   *
   *  This includes the energy value for the paremeter set, which is
   *  listed as the first parameter.
   */
  unsigned int parameterSetLength() const { return 14; }
  
  /**
   *  @brief Return the energy of a Riley cross section parameter set
   *
   *  @param[in] index    the index (1 to 9, one-based)
   */
  auto energy( std::size_t index ) const {
    
    #ifndef NDEBUG
    verifyRileyIndex( index );
    #endif
    return this->dvalue(index, 1);
  }
  
  /**
   *  @brief Return the Riley cross section parameter set at the index
   *
   *  @param[in] index    the index (1 to 9, one-based)
   */
  auto parameterSet( std::size_t index ) const {
    
    #ifndef NDEBUG
    verifyRileyIndex( index );
    #endif
    return this->darray(index);
  }
  
  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using RLY = RileyCrossSectionBlock;

} // electron namespace
} // ACEtk namespace
} // njoy namespace

#endif
