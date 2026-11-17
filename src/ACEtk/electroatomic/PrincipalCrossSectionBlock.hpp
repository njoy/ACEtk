#ifndef NJOY_ACETK_ELECTROATOMIC_PRINCIPALCROSSSECTIONBLOCK
#define NJOY_ACETK_ELECTROATOMIC_PRINCIPALCROSSSECTIONBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electroatomic {

/**
 *  @class
 *  @brief The electron ESZE block with the electron cross section data
 *
 *  This block is part of the eprdata formats.
 *
 *  The PrincipalCrossSectionBlock class contains 5 + NSSH arrays of the same
 *  length:
 *    - the energy points
 *    - the total cross section (sum of the following three arrays)
 *    - the elastic scattering cross section
 *    - the Bremsstrahlung cross section
 *    - the excitation cross section
 *    - the total electroionisation cross section (sum of the following NSSH arrays)
 *    - the electroionisation cross section for each subshell (NSSH arrays)
 *
 *  The size NE of each (the total number of electron energy points) is stored in
 *  NXS(8). The number of subshells NSSH is stored in NXS(7).
 */
class PrincipalCrossSectionBlock : protected base::ArrayData {

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

  static std::vector< std::vector< double > > generateArrays(
      std::vector< double > energies,
      std::vector< double > elastic,
      std::vector< double > bremsstrahlung,
      std::vector< double > excitation,
      std::vector< std::vector< double > > electroionisation ) {

    const auto ne = energies.size();
    const auto nssh = electroionisation.size();

    if ( electroionisation.size() == 0 ) {

      Log::error( "Expected at least 1 electroionisation cross section, found 0" );
      throw std::exception();
    }
    bool size = false;
    for ( const auto& values : electroionisation ) {

      if ( values.size() != ne ) {

        size = true;
      }
    }
    if ( ( elastic.size() != ne ) || ( bremsstrahlung.size() != ne ) ||
         ( excitation.size() != ne ) || size ) {

      Log::error( "The sizes of the principal cross sections are not consistent" );
      Log::info( "energies.size(): {}", ne );
      Log::info( "elastic.size(): {}", elastic.size() );
      Log::info( "bremsstrahlung.size(): {}", bremsstrahlung.size() );
      Log::info( "excitation.size(): {}", excitation.size() );
      unsigned int index = 0;
      for ( const auto& values : electroionisation ) {

        Log::info( "electroionisation.size() for subshell {}: {}", index, values.size() );
        ++index;
      }
      throw std::exception();
    }

    std::vector< std::vector< double > > arrays;

    std::vector< double > total = elastic;
    std::vector< double > totalionisation = electroionisation.front();

    arrays.push_back( std::move( energies ) );
    arrays.push_back( std::move( elastic ) );
    arrays.push_back( std::move( bremsstrahlung ) );
    std::transform( arrays.back().cbegin(), arrays.back().cend(),
                    total.cbegin(), total.begin(), std::plus<>{} );
    arrays.push_back( std::move( excitation ) );
    std::transform( arrays.back().cbegin(), arrays.back().cend(),
                    total.cbegin(), total.begin(), std::plus<>{} );
    for ( unsigned int i = 0; i < nssh; ++i ) {

      arrays.push_back( std::move( electroionisation[i] ) );
      if ( i != 0 ) {

        std::transform( arrays.back().cbegin(), arrays.back().cend(),
                        totalionisation.cbegin(), totalionisation.begin(),
                        std::plus<>{} );
      }
    }
    std::transform( totalionisation.cbegin(), totalionisation.cend(),
                    total.cbegin(), total.begin(), std::plus<>{} );

    arrays.insert( std::next( arrays.begin(), 4 ), totalionisation );
    arrays.insert( std::next( arrays.begin() ), total );

    return arrays;
  }

public:

  /* constructor */

  PrincipalCrossSectionBlock() = default;

  PrincipalCrossSectionBlock( const PrincipalCrossSectionBlock& ) = default;
  PrincipalCrossSectionBlock( PrincipalCrossSectionBlock&& ) = default;

  PrincipalCrossSectionBlock& operator=( const PrincipalCrossSectionBlock& ) = default;
  PrincipalCrossSectionBlock& operator=( PrincipalCrossSectionBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energies             the energy values
   *  @param[in] elastic              the elastic cross section values
   *  @param[in] bremsstrahlung       the Bremsstrahlung cross section values
   *  @param[in] excitation           the excitation cross section values
   *  @param[in] electroionisation    the electroionisation cross section values
   *                                  for each shell
   */
  PrincipalCrossSectionBlock(
      std::vector< double > energies,
      std::vector< double > elastic,
      std::vector< double > bremsstrahlung,
      std::vector< double > excitation,
      std::vector< std::vector< double > > electroionisation ) :
    ArrayData( "ESZE",
               generateArrays( std::move( energies ), std::move( elastic ),
                               std::move( bremsstrahlung ), std::move( excitation ),
                               std::move( electroionisation ) ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the ESZE block in the XSS array
   *  @param[in] end     the end iterator of the ESZE block in the XSS array
   *  @param[in] nssh    the number of electron shells
   *  @param[in] ne      the number of energy values
   */
  PrincipalCrossSectionBlock( Iterator begin, Iterator end,
                                        unsigned int nssh, unsigned int ne ) :
    ArrayData( "ESZE", begin, end, ne, 6 + nssh ) {}

  /* methods */

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NE() const { return this->N(); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NE(); }

  /**
   *  @brief Return the number of electron subshells
   */
  unsigned int NSSH() const { return this->M() - 6; }

  /**
   *  @brief Return the number of electron shells
   */
  unsigned int numberElectronSubshells() const { return this->NSSH(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->darray( 1 ); }

  /**
   *  @brief Return the total cross section values
   */
  auto total() const { return this->darray( 2 ); }

  /**
   *  @brief Return the elastic cross section values
   */
  auto elastic() const { return this->darray( 3 ); }

  /**
   *  @brief Return the Bremsstrahlung cross section values
   */
  auto bremsstrahlung() const { return this->darray( 4 ); }

  /**
   *  @brief Return the excitation cross section values
   */
  auto excitation() const { return this->darray( 5 ); }

  /**
   *  @brief Return the total electroionisation cross section values
   */
  auto totalElectroionisation() const { return this->darray( 6 ); }

  /**
   *  @brief Return the electroionisation cross section values for a specific
   *         shell
   *
   *  @param[in] index    the electron subshell index (one-based)
   */
  auto electroionisation( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIndex( index );
    #endif
    return this->darray( 6 + index );
  }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using ESZE = PrincipalCrossSectionBlock;

} // electroatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
