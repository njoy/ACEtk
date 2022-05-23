#ifndef NJOY_ACETK_BLOCK_THERMALSCATTERINGDISCRETECOSINES
#define NJOY_ACETK_BLOCK_THERMALSCATTERINGDISCRETECOSINES

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Discrete cosines for a single outgoing energy value used
 *         in thermal scattering secondary particle distributions
 *
 *  The ThermalScatteringDiscreteCosines class contains an outgoing
 *  energy value and the associated discrete cosine values. It is used in the
 *  ITXE block (for inelastic thermal scattering data) when IFENG = 0 or 1.
 */
class ThermalScatteringDiscreteCosines : protected details::Base {

  /* fields */
  std::size_t ncosines_;

  /* auxiliary functions */
  #include "ACEtk/block/ThermalScatteringDiscreteCosines/src/verifySize.hpp"
  #include "ACEtk/block/ThermalScatteringDiscreteCosines/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/block/ThermalScatteringDiscreteCosines/src/ctor.hpp"

  /**
   *  @brief Return the outgoing energy value
   */
  double energy() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the number of discrete cosines
   */
  std::size_t NC() const { return this->ncosines_; }

  /**
   *  @brief Return the number of discrete cosines
   */
  std::size_t numberDiscreteCosines() const { return this->NC(); }

  /**
   *  @brief Return the discrete cosine values
   */
  auto cosines() const {

    return this->XSS( 2, this->numberDiscreteCosines() );
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
