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
  #include "ACEtk/multigroup/StoppingPowerBlock/src/ctor.hpp"

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
