#ifndef NJOY_ACETK_PHOTOATOMIC_PRINCIPALCROSSSECTIONBLOCK
#define NJOY_ACETK_PHOTOATOMIC_PRINCIPALCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace photoatomic {

/**
 *  @class
 *  @brief The photoatomic ESZG block with the principal cross sections
 *
 *  The PrincipalCrossSectionBlock class contains 5 arrays of the
 *  same length (all values are stored as the natural logarithm with the
 *  exception of 0 values which are interpreted as 0 and NOT as exp(0) = 1):
 *    - the energy points
 *    - the incoherent cross section
 *    - the coherent cross section
 *    - the photoelectric cross section
 *    - the pair production cross section
 *
 *  The size of each (the total number of energy points NES) is stored in NXS(3).
 */
class PrincipalCrossSectionBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

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
   *  @param[in] energies          the energy values
   *  @param[in] incoherent        the incoherent cross section values
   *  @param[in] coherent          the coherent cross section values
   *  @param[in] photoelectric     the photo-electric cross section values
   *  @param[in] pairproduction    the pair production cross section values
   */
  PrincipalCrossSectionBlock( std::vector< double > energies,
                              std::vector< double > incoherent,
                              std::vector< double > coherent,
                              std::vector< double > photoelectric,
                              std::vector< double > pairproduction ) :
    ArrayData( "ESZG",
               std::move( energies ), std::move( incoherent ),
               std::move( coherent ), std::move( photoelectric ),
               std::move( pairproduction ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the ESZG block in the XSS array
   *  @param[in] end     the end iterator of the ESZG block in the XSS array
   *  @param[in] nes     the number of energy points
   */
  PrincipalCrossSectionBlock( Iterator begin, Iterator end, unsigned int nes ) :
    ArrayData( "ESZG", begin, end, nes, 5 ) {}

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
   *  @brief Return the energy values
   */
  auto energies() const { return this->darray( 1 ); }

  /**
   *  @brief Return the incoherent cross section values
   */
  auto incoherent() const { return this->darray( 2 ); }

  /**
   *  @brief Return the coherent cross section values
   */
  auto coherent() const { return this->darray( 3 ); }

  /**
   *  @brief Return the photo-electric cross section values
   */
  auto photoelectric() const { return this->darray( 4 ); }

  /**
   *  @brief Return the pair production cross section values
   */
  auto pairproduction() const { return this->darray( 5 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using ESZG = PrincipalCrossSectionBlock;

} // photoatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
