#ifndef NJOY_ACETK_MULTIGROUP_TOTALCROSSSECTIONBLOCK
#define NJOY_ACETK_MULTIGROUP_TOTALCROSSSECTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup TOT block with the total cross section for each group
 *
 *  The TotalCrossSectionBlock class contains 1 array 
 *    - the total cross section for each group
 *
 *  The size the array (the total number of energy groups) is stored in NXS(5).
 */
class TotalCrossSectionBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  TotalCrossSectionBlock() = default;

  TotalCrossSectionBlock( const TotalCrossSectionBlock& ) = default;
  TotalCrossSectionBlock( TotalCrossSectionBlock&& ) = default;

  TotalCrossSectionBlock& operator=( const TotalCrossSectionBlock& ) = default;
  TotalCrossSectionBlock& operator=( TotalCrossSectionBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] totalCrossSection      the total cross section for each group
   */
  TotalCrossSectionBlock( std::vector< double > totalCrossSection ) :
    ArrayData( "TOT", std::vector< std::vector< double > >{ std::move( totalCrossSection ) } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the TOT block in the XSS array
   *  @param[in] end     the end iterator of the TOT block in the XSS array
   *  @param[in] ngrp     the number of energy groups
   */
  TotalCrossSectionBlock( Iterator begin, Iterator end, unsigned int ngrp ) :
    ArrayData( "TOT", begin, end, ngrp, 1 ) {}

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
   *  @brief Return the total cross section values
   */
  auto SIGTOT() const { return this->darray( 1 ); }

  /**
   *  @brief Return the total cross section values
   */
  auto totalCrossSection() const { return this->SIGTOT(); }


  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using TOT = TotalCrossSectionBlock;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
