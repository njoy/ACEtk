#ifndef NJOY_ACETK_MULTIGROUP_SECONDARYPARTICLEGROUPSTRUCTUREBLOCK
#define NJOY_ACETK_MULTIGROUP_SECONDARYPARTICLEGROUPSTRUCTUREBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup energy ERG2 block with the secondary particle group structures
 *
 *  The SecondaryParticleGroupStructureBlock class contains 2 arrays of the same length:
 *    - the mean energies of each group (in MeV)
 *    - the widths of each group (in MeV)
 *
 *  The size of each (the total number of energy groups), NERG, is LERG2(i).
 */
class SecondaryParticleGroupStructureBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  SecondaryParticleGroupStructureBlock() = default;

  SecondaryParticleGroupStructureBlock( const SecondaryParticleGroupStructureBlock& ) = default;
  SecondaryParticleGroupStructureBlock( SecondaryParticleGroupStructureBlock&& ) = default;

  SecondaryParticleGroupStructureBlock& operator=( const SecondaryParticleGroupStructureBlock& ) = default;
  SecondaryParticleGroupStructureBlock& operator=( SecondaryParticleGroupStructureBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] groupMeans         the mean energies of the groups in MeV
   *  @param[in] groupWidths        the widths of each group in MeV
   */
  SecondaryParticleGroupStructureBlock( std::vector< double > groupMeans, std::vector< double > groupWidths ) :
    ArrayData( "ERG2",
               std::move( groupMeans ), std::move( groupWidths ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin    the iterator to the second element of the  of the ERG2 block in the XSS array
   *  @param[in] end      the end iterator of the ERG2 block in the XSS array
   *  @param[in] ngrp     the number of energy groups
   */
  SecondaryParticleGroupStructureBlock( Iterator begin, Iterator end, unsigned int ngrp ) :
    ArrayData( "ERG2", begin, end, ngrp, 2 ) {}

  /* methods */

  /**
   *  @brief Return the number of energy groups
   */
  unsigned int NERG() const { return this->N(); }

  /**
   *  @brief Return the number of energy groups
   */
  unsigned int numberEnergyGroups() const { return this->NERG(); }

  /**
   *  @brief Return the mean energies of the groups
   */
  auto ECENT2() const { return this->darray( 1 ); }

  /**
   *  @brief Return the mean energies of the groups
   */
  auto groupMeans() const { return this->ECENT2(); }


  /**
   *  @brief Return the widths of the energy groups in MeV
   */
  auto EWID2() const { return this->darray( 2 ); }

  /**
   *  @brief Return the widths of the energy groups in MeV
   */
  auto groupWidths() const { return this->EWID2(); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using ERG2 = SecondaryParticleGroupStructureBlock;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
