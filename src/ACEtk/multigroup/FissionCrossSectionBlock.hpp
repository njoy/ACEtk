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
  #include "ACEtk/multigroup/FissionCrossSectionBlock/src/ctor.hpp"

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
