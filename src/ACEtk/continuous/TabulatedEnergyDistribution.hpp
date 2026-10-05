#ifndef NJOY_ACETK_CONTINUOUS_TABULATEDOUTGOINGENERGYDISTRIBUTION
#define NJOY_ACETK_CONTINUOUS_TABULATEDOUTGOINGENERGYDISTRIBUTION

// system includes

// other includes
#include "ACEtk/base/TabulatedProbabilityDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Tabulated angular distribution data for a single incident energy or
 *         cosine value
 *
 *  The TabulatedEnergyDistribution class contains the probability
 *  density function (PDF) and cumulative density function (CDF) as a function
 *  of the outgoing energy for the given incident energy or cosine value. It is
 *  used in the OutgoingEnergyDistributionData (ACE LAW 4 for a given incident
 *  energy) and in the OutgoingAngleEnergyDistributionData (ACE LAW 67 for a
 *  given cosine) in the DLW block.
 */
class TabulatedEnergyDistribution : protected base::TabulatedProbabilityDistribution {

  /* fields */

  double incident_ = 0.0;

  /* auxiliary functions */

public:

  /* constructor */

  TabulatedEnergyDistribution() = default;

  TabulatedEnergyDistribution( const TabulatedEnergyDistribution& ) = default;
  TabulatedEnergyDistribution( TabulatedEnergyDistribution&& ) = default;

  TabulatedEnergyDistribution& operator=( const TabulatedEnergyDistribution& ) = default;
  TabulatedEnergyDistribution& operator=( TabulatedEnergyDistribution&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] incident        the incident energy or cosine value
   *  @param[in] interpolation   the interpolation type
   *  @param[in] outgoing        the outgoing energy values (N values)
   *  @param[in] pdf             the pdf values (N values)
   *  @param[in] cdf             the cdf values (N values)
   *  @param[in] discrete        the number discrete photon lines (defaults to 0)
   */
  TabulatedEnergyDistribution( double incident,
                               int interpolation,
                               std::vector< double > outgoing,
                               std::vector< double > pdf,
                               std::vector< double > cdf,
                               std::size_t discrete = 0 ) :
    TabulatedProbabilityDistribution(
          "TabulatedEnergyDistribution",
          discrete * 10 + interpolation, std::move( outgoing ),
          std::move( pdf ), std::move( cdf ), {} ),
    incident_( incident ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] incident   the incident energy value
   *  @param[in] begin      the begin iterator of the tabulated distribution data
   *  @param[in] end        the end iterator of the tabulated distribution data
   */
  TabulatedEnergyDistribution( double incident, Iterator begin, Iterator end ) :
    TabulatedProbabilityDistribution( "TabulatedEnergyDistribution",
                                      begin, end ),
    incident_( incident ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] incident   the incident energy value
   *  @param[in] locb       the starting xss index with respect to the superblock
   *  @param[in] begin      the begin iterator of the tabulated distribution data
   *  @param[in] end        the end iterator of the tabulated distribution data
   */
  TabulatedEnergyDistribution( double incident, std::size_t,
                               Iterator begin, Iterator end ) :
    TabulatedEnergyDistribution( incident, begin, end ) {}

  // generic function used internally
  double value() const { return this->incident_; }

  /**
   *  @brief Return the incident energy value
   */
  double energyOrCosine() const { return this->value(); }

  /**
   *  @brief Return the interpolation flag
   */
  unsigned int interpolation() const {

    // the INTT' value = 10 * ND + INTT
    return TabulatedProbabilityDistribution::interpolation() % 10;
  }

  /**
   *  @brief Return the number of discrete photon lines
   */
  std::size_t numberDiscretePhotonLines() const {

    // the INTT' value = 10 * ND + INTT
    return ( TabulatedProbabilityDistribution::interpolation() -
             this->interpolation() ) / 10;
  }

  /**
   *  @brief Return the number of cosine values
   */
  std::size_t numberOutgoingEnergies() const {

    return TabulatedProbabilityDistribution::numberValues();
  }

  /**
   *  @brief Return the outgoing energies values
   */
  auto outgoingEnergies() const {

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
