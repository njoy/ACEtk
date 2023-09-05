#ifndef NJOY_ACETK_BLOCK_TABULATEDKALBACHMANNDISTRIBUTION
#define NJOY_ACETK_BLOCK_TABULATEDKALBACHMANNDISTRIBUTION

// system includes

// other includes
#include "ACEtk/block/details/TabulatedProbabilityDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

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
class TabulatedKalbachMannDistribution :
  protected details::TabulatedProbabilityDistribution {

  /* fields */
  double incident_ = 0.0;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/TabulatedKalbachMannDistribution/src/ctor.hpp"

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

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
