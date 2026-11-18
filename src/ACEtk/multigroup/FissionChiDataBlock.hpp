#ifndef NJOY_ACETK_MULTIGROUP_FISSIONCHIDATABLOCK
#define NJOY_ACETK_MULTIGROUP_FISSIONCHIDATABLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup CHI block with the fission fractions (PFNS) for each group
 *
 *  The FissionChiDataBlock class contains 1 array 
 *    - the fission fraction (PFNS) for each group
 *
 *  The PFNS values are normalized so that the overall sum is 1.
 *
 *  The size the array (the total number of energy groups) is stored in NXS(5).
 */
class FissionChiDataBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  FissionChiDataBlock() = default;

  FissionChiDataBlock( const FissionChiDataBlock& ) = default;
  FissionChiDataBlock( FissionChiDataBlock&& ) = default;

  FissionChiDataBlock& operator=( const FissionChiDataBlock& ) = default;
  FissionChiDataBlock& operator=( FissionChiDataBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] fissionFraction      the fission fraction (PFNS) for each group
   */
  FissionChiDataBlock( std::vector< double > fissionFraction ) :
    ArrayData( "CHI", std::vector< std::vector< double > >{ std::move( fissionFraction ) } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the CHI block in the XSS array
   *  @param[in] end     the end iterator of the CHI block in the XSS array
   *  @param[in] ngrp     the number of energy groups
   */
  FissionChiDataBlock( Iterator begin, Iterator end, unsigned int ngrp ) :
    ArrayData( "CHI", begin, end, ngrp, 1 ) {}

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
   *  @brief Return the fission fraction (PFNS) values
   */
  auto FISFR() const { return this->darray( 1 ); }

  /**
   *  @brief Return the fission fraction (PFNS) values
   */
  auto fissionFraction() const { return this->FISFR(); }


  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using CHI = FissionChiDataBlock;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
