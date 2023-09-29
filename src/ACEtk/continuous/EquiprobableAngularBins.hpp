#ifndef NJOY_ACETK_CONTINUOUS_EQUIPROBABLEANGULARBINS
#define NJOY_ACETK_CONTINUOUS_EQUIPROBABLEANGULARBINS

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Equiprobable angular bin data for a single incident energy value
 *
 *  The EquiprobableAngularBins class contains the cosine values that make up
 *  the equiprobable bins (there are 33 values for defining 32 bins) for the
 *  assocoiated incident energy. It is used in the AND block. This
 *  format is only used in old ACE data.
 */
class EquiprobableAngularBins : protected base::Base {

  /* fields */
  double energy_ = 0.0;

  /* auxiliary functions */
  #include "ACEtk/continuous/EquiprobableAngularBins/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/continuous/EquiprobableAngularBins/src/ctor.hpp"

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
