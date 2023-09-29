#ifndef NJOY_ACETK_CONTINUOUS_FISSIONMULTIPLICITYBLOCK
#define NJOY_ACETK_CONTINUOUS_FISSIONMULTIPLICITYBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/base/Base.hpp"
#include "ACEtk/continuous/PolynomialFissionMultiplicity.hpp"
#include "ACEtk/continuous/TabulatedFissionMultiplicity.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy NU block with the fission multiplicity data
 */
class FissionMultiplicityBlock : protected base::Base {

public:

  /* type aliases */
  using FissionMultiplicityData = std::variant< PolynomialFissionMultiplicity,
                                                TabulatedFissionMultiplicity >;

private:

  /* fields */
  FissionMultiplicityData prompt_;
  std::optional< FissionMultiplicityData > total_;

  /* auxiliary functions */
  #include "ACEtk/continuous/FissionMultiplicityBlock/src/generateXSS.hpp"
  #include "ACEtk/continuous/FissionMultiplicityBlock/src/generateBlocks.hpp"

public:

  /* constructor */
  #include "ACEtk/continuous/FissionMultiplicityBlock/src/ctor.hpp"

  /* methods */

  /**
   *  @brief Return whether or not prompt and total fission multiplicity are
   *         present
   */
  bool hasPromptAndTotalFissionMultiplicity() const {

    return this->total_.has_value();
  }

  /**
   *  @brief Return the multiplicity
   *
   *  This returns the prompt fission multiplicity when both prompt and total
   *  are given or just the available multiplicity data if only one of these is
   *  given (the ACE format does not indicate which is present).
   */
  const FissionMultiplicityData& multiplicity() const {

    return this->prompt_;
  }

  /**
   *  @brief Return the total fission multiplicity
   *
   *  This returns the total fission multiplicity when both prompt and total
   *  are given or just the available multiplicity data if only one of these is
   *  given (the ACE format does not indicate which is present).
   */
  const std::optional< FissionMultiplicityData >& totalFissionMultiplicity() const {

    return this->total_;
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using NU = FissionMultiplicityBlock;
using DNU = FissionMultiplicityBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
