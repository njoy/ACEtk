#ifndef NJOY_ACETK_BLOCK_INCOHERENTSCATTERINGFUNCTIONBLOCK
#define NJOY_ACETK_BLOCK_INCOHERENTSCATTERINGFUNCTIONBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/block/details/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The photoatomic JINC block with the incoherent scattering function values
 *
 *  The IncoherentScatteringFunctionBlock class contains the scattering functions
 *  tabulated on a fixed grid of the recoil electron momentum transfer (in inverse
 *  angstroms).
 */
class IncoherentScatteringFunctionBlock : protected details::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/IncoherentScatteringFunctionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of values
   */
  static constexpr unsigned int NM() { return 21; }

  /**
   *  @brief Return the number of values
   */
  static constexpr unsigned int numberValues() { return NM(); }

  /**
   *  @brief Return the electron recoil momentum values
   */
  static constexpr std::array< double, 21 > momentum() {

    return {{ 0., .005, .01, .05, .1, .15, .2,
              .3, .4, .5, .6, .7, .8, .9, 1., 1.5, 2., 3., 4., 5., 8. }};
  }

  /**
   *  @brief Return the scattering function values
   */
  auto values() const { return this->darray( 1 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using JINC = IncoherentScatteringFunctionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
