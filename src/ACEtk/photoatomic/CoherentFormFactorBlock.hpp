#ifndef NJOY_ACETK_PHOTOATOMIC_COHERENTFORMFACTORBLOCK
#define NJOY_ACETK_PHOTOATOMIC_COHERENTFORMFACTORBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/base/ArrayData.hpp"
#include "tools/std20/views.hpp"

namespace njoy {
namespace ACEtk {
namespace photoatomic {

/**
 *  @class
 *  @brief The photoatomic JCOH block with the coherent form factors
 *
 *  The CoherentFormFactorBlock class contains one of the following
 *  representations of the form factor:
 *    - 55 values for the form factor and its integral form using a fixed
 *      momentum grid (mcplib version)
 *    - tabulated form factor and its integral form (eprdata version)
 */
class CoherentFormFactorBlock : protected base::ArrayData {

  /* fields */
  std::optional< std::vector< double > > momentum_;

  /* auxiliary functions */
  #include "ACEtk/photoatomic/CoherentFormFactorBlock/src/numberElements.hpp"
  #include "ACEtk/photoatomic/CoherentFormFactorBlock/src/numberArrays.hpp"
  #include "ACEtk/photoatomic/CoherentFormFactorBlock/src/generateArrays.hpp"

public:

  /* constructor */
  #include "ACEtk/photoatomic/CoherentFormFactorBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of values
   */
  unsigned int NM() const { return this->N(); }

  /**
   *  @brief Return the number of values
   */
  unsigned int numberValues() const { return NM(); }

  /**
   *  @brief Return the electron recoil momentum values
   */
  auto momentum() const {

    if ( this->momentum_.has_value() ) {

      return njoy::tools::std20::ranges::subrange( this->momentum_.value().begin(),
                                                   this->momentum_.value().end() );
    }
    else {

      return this->darray( 1 );
    }
  }

  /**
   *  @brief Return the integrated form factor values (tabulated on a grid of
   *         squared momentum values)
   */
  auto integratedFormFactors() const {

    return this->darray( this->momentum_.has_value() ? 1 : 2 );
  }

  /**
   *  @brief Return the form factor values (tabulated on a grid of momentum
   *         values)
   */
  auto formFactors() const {

    return this->darray( this->momentum_.has_value() ? 2 : 3 );
  }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using JCOH = CoherentFormFactorBlock;

} // photoatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
