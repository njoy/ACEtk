#ifndef NJOY_ACETK_THERMAL_DISCRETECOSINESWITHPROBABILITY
#define NJOY_ACETK_THERMAL_DISCRETECOSINESWITHPROBABILITY

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
 *  The DiscreteCosinesWithProbability class contains an outgoing energy value,
 *  the corresponding pdf and cdf value and the associated discrete cosine
 *  values. It is used in the ITXE block (for inelastic thermal scattering data)
 *  when IFENG = 2. This is the current standard ACE format used in inelastic
 *  thermal scattering.
 */
class DiscreteCosinesWithProbability : protected block::details::Base {

  /* fields */
  std::size_t ncosines_ = 0;

  /* auxiliary functions */
  #include "ACEtk/thermal/DiscreteCosinesWithProbability/src/generateXSS.hpp"
  #include "ACEtk/thermal/DiscreteCosinesWithProbability/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/thermal/DiscreteCosinesWithProbability/src/ctor.hpp"

  /**
   *  @brief Return the outgoing energy value
   */
  double energy() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the pdf value
   */
  double pdf() const { return this->XSS( 2 ); }

  /**
   *  @brief Return the cdf value
   */
  double cdf() const { return this->XSS( 3 ); }

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

    return this->XSS( 4, this->numberDiscreteCosines() );
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
