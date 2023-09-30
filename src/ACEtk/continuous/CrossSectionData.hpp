#ifndef NJOY_ACETK_CONTINUOUS_CROSSSECTIONDATA
#define NJOY_ACETK_CONTINUOUS_CROSSSECTIONDATA

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Cross section data from the SIG block for a single reaction
 *
 *  The CrossSectionData class contains the index of the energy point
 *  corresponding to the first cross section value, the number of cross
 *  section values and the actual cross section values.
 */
class CrossSectionData : protected base::Base {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/continuous/CrossSectionData/src/generateXSS.hpp"
  #include "ACEtk/continuous/CrossSectionData/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/continuous/CrossSectionData/src/ctor.hpp"

  /**
   *  @brief Return the energy index
   */
  std::size_t energyIndex() const { return this->IXSS( 1 ); }

  /**
   *  @brief Return the number of cross section values
   */
  std::size_t numberValues() const { return this->IXSS( 2 ); }

  /**
   *  @brief Return the cross section values
   */
  auto crossSections() const { return this->XSS( 3, this->numberValues() ); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
