#ifndef NJOY_ACETK_BLOCK_PHOTONPRODUCTIONBLOCK
#define NJOY_ACETK_BLOCK_PHOTONPRODUCTIONBLOCK

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"

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
class PhotonProductionBlock : protected details::Base {

  /* fields */
  unsigned int nes_;

  /* auxiliary functions */
  #include "ACEtk/block/PhotonProductionBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/PhotonProductionBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NES() const { return this->nes_; }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NES(); }

  /**
   *  @brief Return the total photon production cross section values
   */
  auto totalProduction() const { return this->XSS( 1, this->nes_ ); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using GPD = PhotonProductionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
