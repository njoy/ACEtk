#ifndef NJOY_ACETK_PHOTONUCLEAR_PRINCIPALCROSSSECTIONBLOCK
#define NJOY_ACETK_PHOTONUCLEAR_PRINCIPALCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace photonuclear {

/**
 *  @class
 *  @brief The photonuclear ESZU block with the principal cross sections
 *
 *  The PrincipalCrossSectionBlock class contains 3 or 4 arrays of the same
 *  length:
 *    - the energy points
 *    - the total cross section
 *    - the elastic scattering cross section (optional)
 *    - the heating numbers
 *
 *  The size of each (the total number of energy points) is stored in NXS(3).
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
   *  @param[in] energies         the energy values
   *  @param[in] total            the total cross section values
   *  @param[in] elastic          the elastic cross section values
   *  @param[in] heating          the average heating cross section values
   */
  PrincipalCrossSectionBlock( std::vector< double > energies,
                              std::vector< double > total,
                              std::vector< double > elastic,
                              std::vector< double > heating ) :
    ArrayData( "ESZU",
               std::move( energies ), std::move( total ),
               std::move( elastic ), std::move( heating ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] energies         the energy values
   *  @param[in] total            the total cross section values
   *  @param[in] heating          the average heating cross section values
   */
  PrincipalCrossSectionBlock( std::vector< double > energies,
                              std::vector< double > total,
                              std::vector< double > heating ) :
    ArrayData( "ESZU",
               std::move( energies ), std::move( total ),
               std::move( heating ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the ESZ block in the XSS array
   *  @param[in] end     the end iterator of the ESZ block in the XSS array
   *  @param[in] nes     the number of energy points
   */
  PrincipalCrossSectionBlock( Iterator begin, Iterator end,
                              unsigned int nes, unsigned int size ) :
    ArrayData( "ESZU", begin, end, nes, size ) {}

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
   *  @brief Return the total cross section values
   */
  auto total() const { return this->darray( 2 ); }

  /**
   *  @brief Return the elastic cross section values (this can be empty)
   */
  auto elastic() const { return this->M() == 3 ? this->emptyArray()
                                               : this->darray( 3 ); }

  /**
   *  @brief Return the average heating numbers
   */
  auto heating() const { return this->darray( this->M() ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using ESZU = PrincipalCrossSectionBlock;

} // photonuclear namespace
} // ACEtk namespace
} // njoy namespace

#endif
