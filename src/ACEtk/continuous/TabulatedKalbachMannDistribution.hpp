#ifndef NJOY_ACETK_CONTINUOUS_TABULATEDKALBACHMANNDISTRIBUTION
#define NJOY_ACETK_CONTINUOUS_TABULATEDKALBACHMANNDISTRIBUTION

// system includes

// other includes
#include "ACEtk/base/TabulatedProbabilityDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Tabulated Kalbach-Mann distribution data for a single incident energy
 *
 *  The TabulatedKalbachMannDistribution class contains the probability
 *  density function (PDF), the cumulative density function (CDF), the
 *  precompound fraction r and angular distribution slope a as a function
 *  of the outgoing energy for a single incident energy. It is
 *  used in the KalbachMannDistributionData (ACE LAW 44 for a given incident
 *  energy) in the DLW block.
 */
class TabulatedKalbachMannDistribution : protected base::TabulatedProbabilityDistribution {

  /* fields */

  double incident_ = 0.0;

  /* auxiliary functions */

public:

  /* constructor */

  TabulatedKalbachMannDistribution() = default;

  TabulatedKalbachMannDistribution( const TabulatedKalbachMannDistribution& ) = default;
  TabulatedKalbachMannDistribution( TabulatedKalbachMannDistribution&& ) = default;

  TabulatedKalbachMannDistribution& operator=( const TabulatedKalbachMannDistribution& ) = default;
  TabulatedKalbachMannDistribution& operator=( TabulatedKalbachMannDistribution&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] incident        the incident energy value
   *  @param[in] interpolation   the interpolation type
   *  @param[in] cosines         the cosine values (N values)
   *  @param[in] pdf             the pdf values (N values)
   *  @param[in] cdf             the cdf values (N values)
   *  @param[in] r               the precompound fraction values (N values)
   *  @param[in] a               the cdf values (N values)
   *  @param[in] discrete        the number discrete photon lines (defaults to 0)
   */
  TabulatedKalbachMannDistribution( double incident,
                                    int interpolation,
                                    std::vector< double > cosines,
                                    std::vector< double > pdf,
                                    std::vector< double > cdf,
                                    std::vector< double > r,
                                    std::vector< double > a,
                                    std::size_t discrete = 0 ) :
    TabulatedProbabilityDistribution(
          "TabulatedKalbachMannDistribution",
          discrete * 10 + interpolation, std::move( cosines ),
          std::move( pdf ), std::move( cdf ), { std::move( r ), std::move( a ) } ),
    incident_( incident ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] incident   the incident energy value
   *  @param[in] begin      the begin iterator of the tabulated distribution data
   *  @param[in] end        the end iterator of the tabulated distribution data
   */
  TabulatedKalbachMannDistribution( double incident, Iterator begin, Iterator end ) :
    TabulatedProbabilityDistribution( "TabulatedKalbachMannDistribution",
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
  TabulatedKalbachMannDistribution( double incident, std::size_t,
                                    Iterator begin, Iterator end ) :
    TabulatedKalbachMannDistribution( incident, begin, end ) {}

  // generic function used internally
  double value() const { return this->incident_; }

  /**
   *  @brief Return the incident energy value
   */
  double incidentEnergy() const { return this->incident_; }

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

  /**
   *  @brief Return the precompound fraction values
   */
  auto precompoundFractionValues() const {

    return this->column( 0 );
  }

  /**
   *  @brief Return the angular distribution slope values
   */
  auto angularDistributionSlopeValues() const {

    return this->column( 1 );
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
