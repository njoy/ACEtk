#ifndef NJOY_ACETK_BLOCK_TABULATEDOUTGOINGENERGYDISTRIBUTION
#define NJOY_ACETK_BLOCK_TABULATEDOUTGOINGENERGYDISTRIBUTION

// system includes

// other includes
#include "ACEtk/base/TabulatedProbabilityDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

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
class TabulatedEnergyDistribution :
  protected details::TabulatedProbabilityDistribution {

  /* fields */
  double incident_ = 0.0;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/TabulatedEnergyDistribution/src/ctor.hpp"

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

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
