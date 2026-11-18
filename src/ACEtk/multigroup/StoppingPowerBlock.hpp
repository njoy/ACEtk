#ifndef NJOY_ACETK_MULTIGROUP_STOPPINGPOWERBLOCK
#define NJOY_ACETK_MULTIGROUP_STOPPINGPOWERBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup STOP block with the stopping powers for each group
 *
 *  The StoppingPowerBlock class contains 1 array 
 *    - the stopping powers for each group
 *
 *  The size the array (the total number of energy groups) is stored in NXS(5).
 */
class StoppingPowerBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */

  StoppingPowerBlock() = default;

  StoppingPowerBlock( const StoppingPowerBlock& ) = default;
  StoppingPowerBlock( StoppingPowerBlock&& ) = default;

  StoppingPowerBlock& operator=( const StoppingPowerBlock& ) = default;
  StoppingPowerBlock& operator=( StoppingPowerBlock&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] stoppingPower      the stopping powers for each group
   */
  StoppingPowerBlock( std::vector< double > stoppingPower ) :
    ArrayData( "STOP", std::vector< std::vector< double > >{ std::move( stoppingPower ) } ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the STOP block in the XSS array
   *  @param[in] end     the end iterator of the STOP block in the XSS array
   *  @param[in] ngrp     the number of energy groups
   */
  StoppingPowerBlock( Iterator begin, Iterator end, unsigned int ngrp ) :
    ArrayData( "STOP", begin, end, ngrp, 1 ) {}

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
   *  @brief Return the stopping power values
   */
  auto SPOW() const { return this->darray( 1 ); }

  /**
   *  @brief Return the stopping power values
   */
  auto stoppingPower() const { return this->SPOW(); }


  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using STOP = StoppingPowerBlock;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
