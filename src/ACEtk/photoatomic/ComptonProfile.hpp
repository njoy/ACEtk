#ifndef NJOY_ACETK_PHOTOATOMIC_COMPTONPROFILE
#define NJOY_ACETK_PHOTOATOMIC_COMPTONPROFILE

// system includes

// other includes
#include "ACEtk/base/TabulatedProbabilityDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace photoatomic {

/**
 *  @class
 *  @brief Tabulated Compton profile data for a given electron shell
 *
 *  The ComptonProfile class contains the probability density
 *  function (PDF) and cumulative density function (CDF) as a function of
 *  momentum. It is used in the LSWD block.
 */
class ComptonProfile : protected base::TabulatedProbabilityDistribution {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/photoatomic/ComptonProfile/src/ctor.hpp"

  /**
   *  @brief Return the interpolation flag
   */
  int interpolation() const {

    return TabulatedProbabilityDistribution::interpolation();
  }

  /**
   *  @brief Return the number of values
   */
  std::size_t numberValues() const {

    return TabulatedProbabilityDistribution::numberValues();
  }

  /**
   *  @brief Return the momentum values
   */
  auto momentum() const {

    return TabulatedProbabilityDistribution::values();
  }

  /**
   *  @brief Return the pdf values
   */
  auto pdf() const {

    return TabulatedProbabilityDistribution::pdf();
  }

  /**
   *  @brief Return the cdf values
   */
  auto cdf() const {

    return TabulatedProbabilityDistribution::cdf();
  }

  using TabulatedProbabilityDistribution::empty;
  using TabulatedProbabilityDistribution::name;
  using TabulatedProbabilityDistribution::length;
  using TabulatedProbabilityDistribution::XSS;
  using TabulatedProbabilityDistribution::begin;
  using TabulatedProbabilityDistribution::end;
};

} // photoatomic namespace
} // ACEtk namespace
} // njoy namespace

#endif
