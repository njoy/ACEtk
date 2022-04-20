#ifndef NJOY_ACETK_BLOCK_THERMALSCATTERINGEQUIPROBABLEANGULARBINS
#define NJOY_ACETK_BLOCK_THERMALSCATTERINGEQUIPROBABLEANGULARBINS

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Equiprobable angular bin data for a single outgoing energy value used
 *         in thermal scattering secondary particle distributions
 *
 *  The ThermalScatteringEquiprobableAngularBins class contains the outgoing
 *  energy value and the cosine values that make up the equiprobable bins
 *  (contrary to the AND block, the number of bins is not fixed and can vary).
 *  It is used in the ITXE block (for inelastic thermal scattering data).
 */
class ThermalScatteringEquiprobableAngularBins : protected details::Base {

  /* fields */
  std::size_t nbins_;

  /* auxiliary functions */
  #include "ACEtk/block/ThermalScatteringEquiprobableAngularBins/src/verifySize.hpp"
  #include "ACEtk/block/ThermalScatteringEquiprobableAngularBins/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/block/ThermalScatteringEquiprobableAngularBins/src/ctor.hpp"

  /**
   *  @brief Return the outgoing energy value
   */
  double energy() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the number of equiprobable angular bins
   */
  std::size_t numberBins() const { return this->nbins_; }

  /**
   *  @brief Return the cosine values
   */
  auto cosines() const {

    return this->XSS( 2, this->numberBins() + 1 );
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
