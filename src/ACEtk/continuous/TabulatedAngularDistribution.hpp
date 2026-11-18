#ifndef NJOY_ACETK_CONTINUOUS_TABULATEDANGULARDISTRIBUTION
#define NJOY_ACETK_CONTINUOUS_TABULATEDANGULARDISTRIBUTION

// system includes

// other includes
#include "ACEtk/base/TabulatedProbabilityDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Tabulated angular distribution data for a single incident or outgoing
 *         energy
 *
 *  The TabulatedAngularDistribution class contains the probability density
 *  function (PDF) and cumulative density function (CDF) as a function of
 *  cosine for the given energy. It is used in the AND block.
 */
class TabulatedAngularDistribution : protected base::TabulatedProbabilityDistribution {

  /* fields */

  double energy_ = 0.0;

  /* auxiliary functions */

public:

  /* constructor */

  TabulatedAngularDistribution() = default;

  TabulatedAngularDistribution( const TabulatedAngularDistribution& ) = default;
  TabulatedAngularDistribution( TabulatedAngularDistribution&& ) = default;

  TabulatedAngularDistribution& operator=( const TabulatedAngularDistribution& ) = default;
  TabulatedAngularDistribution& operator=( TabulatedAngularDistribution&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] energy          the associated energy value
   *  @param[in] interpolation   the interpolation type
   *  @param[in] cosines         the cosine values (N values)
   *  @param[in] pdf             the pdf values (N values)
   *  @param[in] cdf             the cdf values (N values)
   */
  TabulatedAngularDistribution( double energy,
                                int interpolation,
                                std::vector< double > cosines,
                                std::vector< double > pdf,
                                std::vector< double > cdf ) :
    TabulatedProbabilityDistribution(
          "TabulatedAngularDistribution",
          interpolation, std::move( cosines ),
          std::move( pdf ), std::move( cdf ), {} ),
    energy_( energy ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] energy     the associated energy value
   *  @param[in] begin      the begin iterator of the tabulated distribution data
   *  @param[in] end        the end iterator of the tabulated distribution data
   */
  TabulatedAngularDistribution( double energy, Iterator begin, Iterator end ) :
    TabulatedProbabilityDistribution( "TabulatedAngularDistribution",
                                      begin, end ),
    energy_( energy ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] energy     the associated energy value
   *  @param[in] locb       the starting xss index with respect to the superblock
   *  @param[in] begin      the begin iterator of the tabulated distribution data
   *  @param[in] end        the end iterator of the tabulated distribution data
   */
  TabulatedAngularDistribution( double energy, std::size_t,
                                Iterator begin, Iterator end ) :
    TabulatedAngularDistribution( energy, begin, end ) {}

  // generic function used internally
  double value() const { return this->energy_; }

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

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
