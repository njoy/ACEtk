#ifndef NJOY_ACETK_PHOTOATOMIC_INCOHERENTSCATTERINGFUNCTIONBLOCK
#define NJOY_ACETK_PHOTOATOMIC_INCOHERENTSCATTERINGFUNCTIONBLOCK

// system includes
#include <algorithm>

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace photoatomic {

/**
 *  @class
 *  @brief The photoatomic JINC block with the incoherent scattering function
 *
 *  The IncoherentScatteringFunctionBlock class contains one of the following
 *  representations of the scattering function:
 *    - 21 scattering function values using a fixed momentum grid (mcplib version)
 *    - tabulated momentum and scattering function values (eprdata version)
 *
 *  The interface abstracts away the distinction between the two representations.
 *
 *  The recoil electron momentum transfer values are given in inverse angstroms.
 */
class IncoherentScatteringFunctionBlock : protected base::ArrayData {

  /* fields */
  std::optional< std::vector< double > > momentum_;

  /* auxiliary functions */
  #include "ACEtk/photoatomic/IncoherentScatteringFunctionBlock/src/numberElements.hpp"
  #include "ACEtk/photoatomic/IncoherentScatteringFunctionBlock/src/numberArrays.hpp"
  #include "ACEtk/photoatomic/IncoherentScatteringFunctionBlock/src/generateArrays.hpp"

public:

  /* constructor */
  #include "ACEtk/photoatomic/IncoherentScatteringFunctionBlock/src/ctor.hpp"

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
   *  @brief Return the scattering function values
   */
  auto values() const {

    return this->darray( this->momentum_.has_value() ? 1 : 2 );
  }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using JINC = IncoherentScatteringFunctionBlock;

} // photoatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
