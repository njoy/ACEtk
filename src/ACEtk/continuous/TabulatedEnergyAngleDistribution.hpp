#ifndef NJOY_ACETK_CONTINUOUS_TABULATEDENERGYANGLEDISTRIBUTION
#define NJOY_ACETK_CONTINUOUS_TABULATEDENERGYANGLEDISTRIBUTION

// system includes
#include <variant>

// other includes
#include "ACEtk/base/DistributionDataWithInterpolationType.hpp"
#include "ACEtk/continuous/TabulatedAngularDistributionWithProbability.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Tabulated outgoing energy and angle distribution data for a single
 *         incident energy
 *
 *  The TabulatedEnergyAngleDistribution class contains the
 *  tabulated angular distributions for a set of outgoing energy values and
 *  associated incident energy value. It is used in the
 *  OutgoingEnergyAngleDistributionData (ACE LAW 61) in the DLW block.
 */
class TabulatedEnergyAngleDistribution :
  protected base::DistributionDataWithInterpolationType<
                TabulatedEnergyAngleDistribution,
                TabulatedAngularDistributionWithProbability > {

  friend class base::DistributionDataWithInterpolationType<
                   TabulatedEnergyAngleDistribution,
                   TabulatedAngularDistributionWithProbability >;

  /* fields */
  double incident_ = 0.0;

  /* auxiliary functions */
  #include "ACEtk/continuous/TabulatedEnergyAngleDistribution/src/generateXSS.hpp"
  #include "ACEtk/continuous/TabulatedEnergyAngleDistribution/src/generateBlocks.hpp"

public:

  /* constructor */
  #include "ACEtk/continuous/TabulatedEnergyAngleDistribution/src/ctor.hpp"

  // generic function used internally
  double value() const { return this->incident_; }

  /**
   *  @brief Return the incident energy value
   */
  double incidentEnergy() const { return this->value(); }

  /**
   *  @brief Return the interpolation type
   */
  int interpolation() const {

    return DistributionDataWithInterpolationType::interpolation();
  }

  /**
   *  @brief Return the number of outgoing energy values
   */
  std::size_t NE() const {

    return DistributionDataWithInterpolationType::N();
  }

  /**
   *  @brief Return the number of outgoing energy values
   */
  std::size_t numberOutgoingEnergies() const {

    return DistributionDataWithInterpolationType::numberValues();
  }

  /**
   *  @brief Return the outgoing energy values
   */
  auto outgoingEnergies() const {

    return DistributionDataWithInterpolationType::values( 1 );
  }

  /**
   *  @brief Return the associated probability values
   */
  auto pdf() const {

    return DistributionDataWithInterpolationType::values( 2 );
  }

  /**
   *  @brief Return the associated cumulative probability values
   */
  auto cdf() const {

    return DistributionDataWithInterpolationType::values( 3 );
  }

  /**
   *  @brief Return the outgoing energy for a given index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  double outgoingEnergy( std::size_t index ) const {

    return DistributionDataWithInterpolationType::value( 1, index );
  }

  /**
   *  @brief Return the probability for a given index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  double probability( std::size_t index ) const {

    return DistributionDataWithInterpolationType::value( 2, index );
  }

  /**
   *  @brief Return the cumulative probability for a given index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  double cumulativeProbability( std::size_t index ) const {

    return DistributionDataWithInterpolationType::value( 3, index );
  }

  /**
   *  @brief Return the distribution locator for an outgoing energy index
   *
   *  This locator is the value as stored in the XSS array. It is relative to
   *  the beginning of the DLW block.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int LOCC( std::size_t index ) const {

    return DistributionDataWithInterpolationType::LOCC( index );
  }

  /**
   *  @brief Return the distribution locator for an outgoing energy index
   *
   *  This locator is the value as stored in the XSS array. It is relative to
   *  the beginning of the DLW block.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int distributionLocator( std::size_t index ) const {

    return DistributionDataWithInterpolationType::distributionLocator( index );
  }

  /**
   *  @brief Return the relative distribution locator for an outgoing energy
   *         index
   *
   *  This is the locator relative to the beginning of the current
   *  distribution block in the DLW block.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t relativeDistributionLocator( std::size_t index ) const {

    return DistributionDataWithInterpolationType::relativeDistributionLocator( index );
  }

  /**
   *  @brief Return the distributions
   */
  const std::vector< TabulatedAngularDistributionWithProbability >&
  distributions() const {

    return DistributionDataWithInterpolationType::distributions();
  }

  /**
   *  @brief Return the distribution for an outgoing energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const TabulatedAngularDistributionWithProbability&
  distribution( std::size_t index ) const {

    return DistributionDataWithInterpolationType::distribution( index );
  }

  using DistributionDataWithInterpolationType::empty;
  using DistributionDataWithInterpolationType::name;
  using DistributionDataWithInterpolationType::length;
  using DistributionDataWithInterpolationType::XSS;
  using DistributionDataWithInterpolationType::begin;
  using DistributionDataWithInterpolationType::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
