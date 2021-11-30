#ifndef NJOY_ACETK_BLOCK_TABULATEDANGULARDISTRIBUTION
#define NJOY_ACETK_BLOCK_TABULATEDANGULARDISTRIBUTION

// system includes

// other includes
#include "ACEtk/block/details/TabulatedProbabilityDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Tabulated angular distirbution data from the AND block for a single
 *         reaction and incident energy
 *
 *  The TabulatedAngularDistribution class contains the probability density
 *  function (PDF) and cumulative density function (CDF) as a function of
 *  cosine for the given incident energy.
 */
class TabulatedAngularDistribution :
  protected details::TabulatedProbabilityDistribution {

  /* fields */
  double energy_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/TabulatedAngularDistribution/src/ctor.hpp"

  /**
   *  @brief Return the associated energy value
   */
  double energy() const { return this->energy_; }

  /**
   *  @brief Return the interpolation flag
   */
  int interpolation() const {

    return TabulatedProbabilityDistribution::interpolation();
  }

  /**
   *  @brief Return the number of cosine values
   */
  std::size_t numberCosines() const {

    return TabulatedProbabilityDistribution::numberValues();
  }

  /**
   *  @brief Return the cosine values
   */
  auto cosines() const {

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

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
