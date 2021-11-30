#ifndef NJOY_ACETK_BLOCK_EQUIPROBABLEANGULARBINS
#define NJOY_ACETK_BLOCK_EQUIPROBABLEANGULARBINS

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Equiprobable angular bin data from the AND block for a single
 *         reaction and incident energy
 *
 *  The EquiprobableAngularBins class contains the cosine values that make up
 *  the equiprobable bins (there are 33 values for defining 32 bins).
 */
class EquiprobableAngularBins : protected details::Base {

  /* fields */
  double energy_;

  /* auxiliary functions */
  #include "ACEtk/block/EquiprobableAngularBins/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/EquiprobableAngularBins/src/ctor.hpp"

  /**
   *  @brief Return the associated energy value
   */
  double energy() const { return this->energy_; }

  /**
   *  @brief Return the number of equiprobable angular bins
   */
  static constexpr int numberBins() { return 32; }

  /**
   *  @brief Return the cosine values
   */
  auto cosines() const {

    return this->XSS( 1, this->numberBins() + 1 );
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
