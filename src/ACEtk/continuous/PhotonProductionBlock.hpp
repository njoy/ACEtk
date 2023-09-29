#ifndef NJOY_ACETK_CONTINUOUS_PHOTONPRODUCTIONBLOCK
#define NJOY_ACETK_CONTINUOUS_PHOTONPRODUCTIONBLOCK

// system includes

// other includes
#include "ACEtk/base/ArrayData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy GPD block with the total photon production
 *         cross section
 *
 *  The PhotonProductionBlock class contains the total photon production cross
 *  section, given on the same energy grid as defined in the principal cross
 *  section block. For older data files, this also contains the equiprobable
 *  energy bins.
 */
class PhotonProductionBlock : protected base::ArrayData {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/continuous/PhotonProductionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NES() const { return this->N(); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NES(); }

  /**
   *  @brief Return the total photon production cross section values
   */
  auto totalProduction() const { return this->darray( 1 ); }

  using ArrayData::empty;
  using ArrayData::name;
  using ArrayData::length;
  using ArrayData::XSS;
  using ArrayData::begin;
  using ArrayData::end;
};

using GPD = PhotonProductionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
