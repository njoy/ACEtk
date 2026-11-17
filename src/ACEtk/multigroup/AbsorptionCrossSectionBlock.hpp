#ifndef NJOY_ACETK_MULTIGROUP_ABSORPTIONCROSSSECTIONBLOCK
#define NJOY_ACETK_MULTIGROUP_ABSORPTIONCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup ABS block with the absorption cross section for each group
 *
 *  The AbsorptionCrossSectionBlock class contains 1 array 
 *    - the absorption cross section for each group
 *
 *  The size the array (the total number of energy groups) is stored in NXS(5).
 */
class AbsorptionCrossSectionBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  AbsorptionCrossSectionBlock() = default;

  AbsorptionCrossSectionBlock( const AbsorptionCrossSectionBlock& ) = default;
  AbsorptionCrossSectionBlock( AbsorptionCrossSectionBlock&& ) = default;

  AbsorptionCrossSectionBlock& operator=( const AbsorptionCrossSectionBlock& ) = default;
  AbsorptionCrossSectionBlock& operator=( AbsorptionCrossSectionBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] absorptionCrossSection      the absorption cross section for each group
   */
  AbsorptionCrossSectionBlock( std::vector< double > absorptionCrossSection ) :
    ArrayData( "ABS", std::vector< std::vector< double > >{ std::move( absorptionCrossSection ) } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the FISS block in the XSS array
   *  @param[in] end     the end iterator of the FISS block in the XSS array
   *  @param[in] ngrp     the number of energy groups
   */
  AbsorptionCrossSectionBlock( Iterator begin, Iterator end, unsigned int ngrp ) :
    ArrayData( "ABS", begin, end, ngrp, 1 ) {}

  /* methods */
    
  /**
   *  @brief Return the number of energy groups
   */
  unsigned int NGRP() const { return this->N(); }

  /**
   *  @brief Return the number of energy groups
   */
  unsigned int numberEnergyGroups() const { return this->NGRP(); }

  /**
   *  @brief Return the absorption cross section values
   */
  auto SIGABS() const { return this->darray( 1 ); }

  /**
   *  @brief Return the absorption cross section values
   */
  auto absorptionCrossSection() const { return this->SIGABS(); }


  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using ABS = AbsorptionCrossSectionBlock;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
