#ifndef NJOY_ACETK_MULTIGROUP_FISSIONCROSSSECTIONBLOCK
#define NJOY_ACETK_MULTIGROUP_FISSIONCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup FISS block with the fission cross section for each group
 *
 *  The FissionCrossSectionBlock class contains 1 array 
 *    - the fission cross section for each group
 *
 *  The size the array (the total number of energy groups) is stored in NXS(5).
 */
class FissionCrossSectionBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  FissionCrossSectionBlock() = default;

  FissionCrossSectionBlock( const FissionCrossSectionBlock& ) = default;
  FissionCrossSectionBlock( FissionCrossSectionBlock&& ) = default;

  FissionCrossSectionBlock& operator=( const FissionCrossSectionBlock& ) = default;
  FissionCrossSectionBlock& operator=( FissionCrossSectionBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] fissionCrossSection      the fission cross section for each group
   */
  FissionCrossSectionBlock( std::vector< double > fissionCrossSection ) :
    ArrayData( "FISS", std::vector< std::vector< double > >{ std::move( fissionCrossSection ) } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the FISS block in the XSS array
   *  @param[in] end     the end iterator of the FISS block in the XSS array
   *  @param[in] ngrp     the number of energy groups
   */
  FissionCrossSectionBlock( Iterator begin, Iterator end, unsigned int ngrp ) :
    ArrayData( "FISS", begin, end, ngrp, 1 ) {}

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
   *  @brief Return the fission cross section values
   */
  auto SIGFISS() const { return this->darray( 1 ); }

  /**
   *  @brief Return the fission cross section values
   */
  auto fissionCrossSection() const { return this->SIGFISS(); }


  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using FISS = FissionCrossSectionBlock;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
