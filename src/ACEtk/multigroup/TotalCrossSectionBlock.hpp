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
  #include "ACEtk/multigroup/TotalCrossSectionBlock/src/ctor.hpp"

  /* methods */

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
