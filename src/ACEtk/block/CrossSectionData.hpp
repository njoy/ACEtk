#ifndef NJOY_ACETK_BLOCK_CROSSSECTIONDATA
#define NJOY_ACETK_BLOCK_CROSSSECTIONDATA

// system includes

// other includes
#include "ACEtk/block/Base.hpp"
#include "ACEtk/block/CrossSectionData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Cross section data from the SIG block for a single reaction
 *
 *  The CrossSectionData class contains the index of the energy point
 *  corresponding to the first cross section value, the number of cross
 *  section values and the actual cross section values.
 */
class CrossSectionData : protected Base {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/block/CrossSectionData/src/generateXSS.hpp"
  #include "ACEtk/block/CrossSectionData/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/CrossSectionData/src/ctor.hpp"

  /**
   *  @brief Return the energy index
   */
  std::size_t energyIndex() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the number of cross section values
   */
  std::size_t numberValues() const { return this->XSS( 2 ); }

  /**
   *  @brief Return the cross section values
   */
  auto crossSections() const {

    return this->XSS( 3, this->numberValues() );
  }

  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
