#ifndef NJOY_ACETK_BLOCK_PHOTONPRODUCTIONCROSSSECTIONDATA
#define NJOY_ACETK_BLOCK_PHOTONPRODUCTIONCROSSSECTIONDATA

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Secondary particle production cross section data from the SIGP block
 *         for a single reaction
 */
class PhotonProductionCrossSectionData : protected details::Base {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/block/PhotonProductionCrossSectionData/src/generateXSS.hpp"
  #include "ACEtk/block/PhotonProductionCrossSectionData/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/PhotonProductionCrossSectionData/src/ctor.hpp"

  /**
   *  @brief Return the representation type (should always be 13)
   */
  unsigned int MFTYPE() const {

    return static_cast< unsigned int >( this->XSS( 1 ) );
  }

  /**
   *  @brief Return the representation type (should always be 13)
   */
  unsigned int type() const { return this->MFTYPE(); }

  /**
   *  @brief Return the energy index
   */
  std::size_t energyIndex() const { return this->XSS( 2 ); }

  /**
   *  @brief Return the number of cross section values
   */
  std::size_t numberValues() const { return this->XSS( 3 ); }

  /**
   *  @brief Return the cross section values
   */
  auto crossSections() const {

    return this->XSS( 4, this->numberValues() );
  }

  using Base::empty;
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
