#ifndef NJOY_ACETK_MULTIGROUP_MOMENTUMTRANSFERBLOCK
#define NJOY_ACETK_MULTIGROUP_MOMENTUMTRANSFERBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace multigroup {

/**
 *  @class
 *  @brief The multigroup MOMblock with the stopping powers for each group
 *
 *  The MomentumTransferBlock class contains 1 array 
 *    - the stopping powers for each group
 *
 *  The size the array (the total number of energy groups) is stored in NXS(5).
 */
class MomentumTransferBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/multigroup/MomentumTransferBlock/src/ctor.hpp"

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
   *  @brief Return the momentum transfer values
   */
  auto MOMTR() const { return this->darray( 1 ); }

  /**
   *  @brief Return the momentum transfer values
   */
  auto momentumTransfer() const { return this->MOMTR(); }


  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using MOM= MomentumTransferBlock;

} // multigroup namespace
} // ACEtk namespace
} // njoy namespace

#endif
