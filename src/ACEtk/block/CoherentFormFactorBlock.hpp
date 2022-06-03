#ifndef NJOY_ACETK_BLOCK_COHERENTFORMFACTORBLOCK
#define NJOY_ACETK_BLOCK_COHERENTFORMFACTORBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The photoatomic JCOH block with the coherent form factors
 *
 *  The CoherentFormFactorBlock class contains coherent form factors that are
 *  used to modify the differential Thomson cross sectiontabulated on a fixed
 *  grid of the recoil electron momentum transfer (in inverse angstroms).
 */
class CoherentFormFactorBlock : protected details::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/CoherentFormFactorBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of values
   */
  constexpr unsigned int NM() const { return 55; }

  /**
   *  @brief Return the number of values
   */
  constexpr unsigned int numberValues() const { return this->NM(); }

  /**
   *  @brief Return the electron recoil momentum values
   */
  constexpr std::array< double, 55 > momentum() const {

    return {{ 0., .01, .02, .03, .04, .05, .06, .08, .10, .12, .15,
              .18, .20, .25, .30, .35, .40, .45, .50, .55, .60, .70,
              .80, .90, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8,
              1.9, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8,
              4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 5.2, 5.4, 5.6, 5.8, 6.0 }};
  }

  /**
   *  @brief Return the integrated form factor values (tabulated on a grid of
   *         squared momentum values)
   */
  auto integratedFormFactors() const { return this->array( 1 ); }

  /**
   *  @brief Return the form factor values (tabulated on a grid of momentum
   *         values)
   */
  auto formFactors() const { return this->array( 2 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using JCOH = CoherentFormFactorBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
