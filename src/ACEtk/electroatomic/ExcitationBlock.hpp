#ifndef NJOY_ACETK_ELECTROATOMIC_EXCITATIONBLOCK
#define NJOY_ACETK_ELECTROATOMIC_EXCITATIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electroatomic {

/**
 *  @class
 *  @brief The electron EXCIT block with the electron excitation energy loss data
 *
 *  This block is part of the eprdata formats.
 *
 *  The ExcitationBlock class contains 2 arrays of the same length:
 *    - the energy points
 *    - the average excitation energy loss values
 *
 *  The size NXL of each (the total number of excitation energy points) is
 *  stored in NXS(9).
 */
class ExcitationBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  ExcitationBlock() = default;

  ExcitationBlock( const ExcitationBlock& ) = default;
  ExcitationBlock( ExcitationBlock&& ) = default;

  ExcitationBlock& operator=( const ExcitationBlock& ) = default;
  ExcitationBlock& operator=( ExcitationBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energies    the energy values
   *  @param[in] loss        the average excitation energy loss values
   */
  ExcitationBlock(
      std::vector< double > energies,
      std::vector< double > loss ) :
    ArrayData( "EXCIT",
               std::vector< std::vector< double > > {

                 std::move( energies ),
                 std::move( loss )
               } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the EXCIT block in the XSS array
   *  @param[in] end     the end iterator of the EXCIT block in the XSS array
   *  @param[in] nxl     the number of energy values
   */
  ExcitationBlock( Iterator begin, Iterator end,
                                      unsigned int nxl ) :
    ArrayData( "EXCIT", begin, end, nxl, 2 ) {}

  /* methods */

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NXL() const { return this->N(); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NXL(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->darray( 1 ); }

  /**
   *  @brief Return the average excitation energy loss values
   */
  auto excitationEnergyLoss() const { return this->darray( 2 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using EXCIT = ExcitationBlock;

} // electroatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
