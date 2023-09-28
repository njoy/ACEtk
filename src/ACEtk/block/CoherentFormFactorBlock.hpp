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
 *  The CoherentFormFactorBlock class contains one of the following
 *  representations of the form factor:
 *    - 55 values for the form factor and its integral form using a fixed 
 *      momentum grid (mcplib version)
 *    - tabulated form factor and its integral form (eprdata version)
 */
class CoherentFormFactorBlock : protected details::ArrayData {

  /* fields */
  std::optional< std::vector< double > > momentum_;

  /* auxiliary functions */
  #include "ACEtk/block/CoherentFormFactorBlock/src/numberElements.hpp"
  #include "ACEtk/block/CoherentFormFactorBlock/src/numberArrays.hpp"
  #include "ACEtk/block/CoherentFormFactorBlock/src/generateArrays.hpp"

public:

  /* constructor */
  #include "ACEtk/block/CoherentFormFactorBlock/src/ctor.hpp"

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

      return ranges::make_subrange( this->momentum_.value().begin(), 
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

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
