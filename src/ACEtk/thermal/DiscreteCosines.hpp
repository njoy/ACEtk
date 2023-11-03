#ifndef NJOY_ACETK_THERMAL_DISCRETECOSINES
#define NJOY_ACETK_THERMAL_DISCRETECOSINES

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace thermal {

/**
 *  @class
 *  @brief Discrete cosines for a single outgoing energy value used
 *         in thermal scattering secondary particle distributions
 *
 *  The DiscreteCosines class contains an outgoing energy value and the
 *  associated discrete cosine values. It is used in the ITXE block (for
 *  inelastic thermal scattering data) when IFENG = 0 or 1.
 */
class DiscreteCosines : protected base::Base {

  /* fields */
  std::size_t ncosines_ = 0;

  /* auxiliary functions */
  #include "ACEtk/thermal/DiscreteCosines/src/verifySize.hpp"
  #include "ACEtk/thermal/DiscreteCosines/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/thermal/DiscreteCosines/src/ctor.hpp"

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

} // thermal namespace
} // ACEtk namespace
} // njoy namespace

#endif
