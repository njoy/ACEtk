#ifndef NJOY_ACETK_BLOCK_TABULATEDANGULARDISTRIBUTIONWITHPROBABILITY
#define NJOY_ACETK_BLOCK_TABULATEDANGULARDISTRIBUTIONWITHPROBABILITY

// system includes

// other includes
#include "ACEtk/block/TabulatedAngularDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Tabulated angular distribution data for a single incident or outgoing
 *         energy
 *
 *  The TabulatedAngularDistributionWithProbability class contains the
 *  probability density function (PDF) and cumulative density function (CDF) as
 *  a function of cosine for the given energy. It is used in the
 *  OutgoingEnergyAngleDistributionData (ACE LAW 61) in the DLW block.
 */
class TabulatedAngularDistributionWithProbability :
  protected TabulatedAngularDistribution {

  /* fields */
  double pdf_;
  double cdf_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/TabulatedAngularDistributionWithProbability/src/ctor.hpp"

  using TabulatedAngularDistribution::energy;

  /**
   *  @brief Return the associated probability value
   */
  double probability() const { return this->pdf_; }

  /**
   *  @brief Return the associated cumulative probability value
   */
  double cumulativeProbability() const { return this->cdf_; }

  using TabulatedAngularDistribution::interpolation;
  using TabulatedAngularDistribution::numberCosines;
  using TabulatedAngularDistribution::cosines;
  using TabulatedAngularDistribution::pdf;
  using TabulatedAngularDistribution::cdf;
  using TabulatedAngularDistribution::empty;
  using TabulatedAngularDistribution::name;
  using TabulatedAngularDistribution::length;
  using TabulatedAngularDistribution::XSS;
  using TabulatedAngularDistribution::begin;
  using TabulatedAngularDistribution::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
