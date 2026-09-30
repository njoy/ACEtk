#ifndef NJOY_ACETK_CONTINUOUS_TABULATEDANGULARDISTRIBUTIONWITHPROBABILITY
#define NJOY_ACETK_CONTINUOUS_TABULATEDANGULARDISTRIBUTIONWITHPROBABILITY

// system includes

// other includes
#include "ACEtk/continuous/TabulatedAngularDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

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
class TabulatedAngularDistributionWithProbability : protected TabulatedAngularDistribution {

  /* fields */

  double pdf_ = 0.0;
  double cdf_ = 0.0;

  /* auxiliary functions */

public:

  /* constructor */

  TabulatedAngularDistributionWithProbability() = default;

  TabulatedAngularDistributionWithProbability( const TabulatedAngularDistributionWithProbability& ) = default;
  TabulatedAngularDistributionWithProbability( TabulatedAngularDistributionWithProbability&& ) = default;

  TabulatedAngularDistributionWithProbability& operator=( const TabulatedAngularDistributionWithProbability& ) = default;
  TabulatedAngularDistributionWithProbability& operator=( TabulatedAngularDistributionWithProbability&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energy          the associated energy value
   *  @param[in] probability     the associated probability value
   *  @param[in] cumulative      the associated cumulative probability value
   *  @param[in] interpolation   the interpolation type
   *  @param[in] cosines         the cosine values (N values)
   *  @param[in] pdf             the pdf values (N values)
   *  @param[in] cdf             the cdf values (N values)
   */
  TabulatedAngularDistributionWithProbability( double energy,
                                               double probability,
                                               double cumulative,
                                               int interpolation,
                                               std::vector< double > cosines,
                                               std::vector< double > pdf,
                                               std::vector< double > cdf ) :
    TabulatedAngularDistribution( energy, interpolation, std::move( cosines ),
                                  std::move( pdf ), std::move( cdf ) ),
    pdf_( probability ), cdf_( cumulative ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] energy         the associated energy value
   *  @param[in] probability    the associated probability value
   *  @param[in] cumulative     the associated cumulative probability value
   *  @param[in] begin          the begin iterator of the tabulated distribution data
   *  @param[in] end            the end iterator of the tabulated distribution data
   */
  TabulatedAngularDistributionWithProbability( double energy,
                                               double probability,
                                               double cumulative,
                                               Iterator begin,
                                               Iterator end ) :
    TabulatedAngularDistribution( energy, begin, end ),
    pdf_( probability ), cdf_( cumulative ) {}

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

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
