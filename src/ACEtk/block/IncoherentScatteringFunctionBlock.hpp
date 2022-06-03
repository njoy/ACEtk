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
 *  @brief The incoherent scattering function values in photoatomic data
 *
 *  The IncoherentScatteringFunctionBlock class contains the scattering functions
 *  tabulated on a fixed grid of the recoil electron momentum (in inverse
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
   *  @brief Return the number of electron recoil momentum values
   */
  constexpr unsigned int NM() const { return 21; }

  /**
   *  @brief Return the number of electron recoil momentum values
   */
  constexpr unsigned int numberValues() const { return this->NM(); }

  /**
   *  @brief Return the electron recoil momentum values
   */
  constexpr std::array< double, 21 > momentum() const {

    return {{ 0., .005, .01, .05, .1, .15, .2,
              .3, .4, .5, .6, .7, .8, .9, 1., 1.5, 2., 3., 4., 5., 8. }};
  }

  /**
   *  @brief Return the scattering function values
   */
  auto values() const { return this->array( 1 ); }

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
