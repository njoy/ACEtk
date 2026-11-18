#ifndef NJOY_ACETK_BLOCK_BREMSSTRAHLUNGENERGYLOSSBLOCK
#define NJOY_ACETK_BLOCK_BREMSSTRAHLUNGENERGYLOSSBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace electroatomic {

/**
 *  @class
 *  @brief The electron BREML block with the average electron energy loss due to
 *         Bremsstrahlung
 *
 *  This block is part of the eprdata formats.
 *
 *  The BremsstrahlungEnergyLossBlock class contains 2 arrays of the same length:
 *    - the energy points
 *    - the average energy loss due to Bremsstrahlung
 *
 *  The size NBL of each (the total number of energy points) is stored in NXS(12).
 */
class BremsstrahlungEnergyLossBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  BremsstrahlungEnergyLossBlock() = default;

  BremsstrahlungEnergyLossBlock( const BremsstrahlungEnergyLossBlock& ) = default;
  BremsstrahlungEnergyLossBlock( BremsstrahlungEnergyLossBlock&& ) = default;

  BremsstrahlungEnergyLossBlock& operator=( const BremsstrahlungEnergyLossBlock& ) = default;
  BremsstrahlungEnergyLossBlock& operator=( BremsstrahlungEnergyLossBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energies     the energy values
   *  @param[in] loss         the average energy loss due to Bremsstrahlung
   */
  BremsstrahlungEnergyLossBlock(
      std::vector< double > energies,
      std::vector< double > loss ) :
    ArrayData( "BREML",
               std::vector< std::vector< double > > {

                 std::move( energies ),
                 std::move( loss )
               } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the BREML block in the XSS array
   *  @param[in] end     the end iterator of the BREML block in the XSS array
   *  @param[in] nbl     the number of energy values
   */
  BremsstrahlungEnergyLossBlock( Iterator begin, Iterator end, unsigned int nbl ) :
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
   *  @brief Return the average energy loss due to Bremsstrahlung
   */
  auto energyLoss() const { return this->darray( 2 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

} // electroatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
