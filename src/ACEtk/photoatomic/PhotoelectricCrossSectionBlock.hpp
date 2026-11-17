#ifndef NJOY_ACETK_PHOTOATOMIC_PHOTOELECTRICCROSSSECTIONBLOCK
#define NJOY_ACETK_PHOTOATOMIC_PHOTOELECTRICCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace photoatomic {

/**
 *  @class
 *  @brief The photoatomic SPHEL block with the photoelectric cross section for
 *         each subshell
 *
 *  This block is part of the eprdata formats.
 *
 *  The PhotoelectricCrossSectionBlock class contains NSSH arrays
 *  of the same length, each one being the photoelectric cross section of a
 *  subshell.
 *
 *  The size of each (the total number of energy points NES) is stored in NXS(3).
 */
class PhotoelectricCrossSectionBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

  void verifyIndex( const std::size_t index ) const {

    if ( ( index < 1 ) || ( index > this->NSSH() ) ) {

      Log::error( "Illegal subshell index argument into the {} block", this->name() );
      Log::info( "Index value: {}", index );
      Log::info( "{} accepts an index between {} and {} inclusively",
                 this->name(), 1, this->NSSH() );
      throw std::out_of_range( this->name() );
    }
  }

public:

  /* constructor */

  PhotoelectricCrossSectionBlock() = default;

  PhotoelectricCrossSectionBlock( const PhotoelectricCrossSectionBlock& ) = default;
  PhotoelectricCrossSectionBlock( PhotoelectricCrossSectionBlock&& ) = default;

  PhotoelectricCrossSectionBlock& operator=( const PhotoelectricCrossSectionBlock& ) = default;
  PhotoelectricCrossSectionBlock& operator=( PhotoelectricCrossSectionBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] photoelectric    the photoelectric cross section values
   *                              for each shell
   */
  PhotoelectricCrossSectionBlock(
      std::vector< std::vector< double > > electroionisation ) :
    ArrayData( "SPHEL", std::move( electroionisation ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the SPHEL block in the XSS array
   *  @param[in] end     the end iterator of the SPHEL block in the XSS array
   *  @param[in] nssh    the number of electron shells
   *  @param[in] nes     the number of energy values
   */
  PhotoelectricCrossSectionBlock( Iterator begin, Iterator end,
                                  unsigned int nssh, unsigned int nes ) :
    ArrayData( "SPHEL", begin, end, nes, nssh ) {}

  /* methods */

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NES() const { return this->N(); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NES(); }

  /**
   *  @brief Return the number of electron subshells
   */
  unsigned int NSSH() const { return this->M(); }

  /**
   *  @brief Return the number of electron shells
   */
  unsigned int numberElectronSubshells() const { return this->NSSH(); }

  /**
   *  @brief Return the photoelectric cross section values for a specific shell
   *
   *  @param[in] index    the electron subshell index (one-based)
   */
  auto photoelectric( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIndex( index );
    #endif
    return this->darray( index );
  }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using SPHEL = PhotoelectricCrossSectionBlock;

} // photoatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
