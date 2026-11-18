#ifndef NJOY_ACETK_BLOCK_BREMSSTRAHLUNGBLOCK
#define NJOY_ACETK_BLOCK_BREMSSTRAHLUNGBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electroatomic {

/**
 *  @class
 *  @brief The electron BREML block with the average electron energy after
 *         Bremsstrahlung
 *
 *  This block is part of the eprdata formats.
 *
 *  The BremsstrahlungBlock class contains 2 arrays of the same length:
 *    - the energy points
 *    - the average energy remaining after Bremsstrahlung
 *
 *  The size NBL of each (the total number of energy points) is stored in NXS(12).
 */
class BremsstrahlungBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  BremsstrahlungBlock() = default;

  BremsstrahlungBlock( const BremsstrahlungBlock& ) = default;
  BremsstrahlungBlock( BremsstrahlungBlock&& ) = default;

  BremsstrahlungBlock& operator=( const BremsstrahlungBlock& ) = default;
  BremsstrahlungBlock& operator=( BremsstrahlungBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energies     the energy values
   *  @param[in] remaining    the average energy remaining after Bremsstrahlung
   */
  BremsstrahlungBlock(
      std::vector< double > energies,
      std::vector< double > remaining ) :
    ArrayData( "BREML",
               std::vector< std::vector< double > > {

                 std::move( energies ),
                 std::move( remaining )
               } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the BREML block in the XSS array
   *  @param[in] end     the end iterator of the BREML block in the XSS array
   *  @param[in] nxl     the number of energy values
   */
  BremsstrahlungBlock( Iterator begin, Iterator end, unsigned int nbl ) :
    ArrayData( "BREML", begin, end, nbl, 2 ) {}

  /* methods */

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NBL() const { return this->N(); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NBL(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->darray( 1 ); }

  /**
   *  @brief Return the average remaining energy after loss to Bremsstrahlung
   */
  auto energyAfterBremsstrahlung() const { return this->darray( 2 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using BREML = BremsstrahlungBlock;

} // electroatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
