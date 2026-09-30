#ifndef NJOY_ACETK_CONTINUOUS_TABULATEDOUTGOINGANGLEENERGYDISTRIBUTION
#define NJOY_ACETK_CONTINUOUS_TABULATEDOUTGOINGANGLEENERGYDISTRIBUTION

// system includes
#include <variant>

// other includes
#include "ACEtk/base/DistributionDataWithInterpolationType.hpp"
#include "ACEtk/continuous/TabulatedEnergyDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Tabulated outgoing energy and angle distribution data for a single
 *         incident energy
 *
 *  The TabulatedAngleEnergyDistribution class contains the
 *  tabulated outgoing energy distributions for a set of cosine values and
 *  associated incident energy value. It is used in the
 *  AngleEnergyDistributionData (ACE LAW 67) in the DLW block.
 */
class TabulatedAngleEnergyDistribution :
  protected base::DistributionDataWithInterpolationType<
                TabulatedAngleEnergyDistribution,
                TabulatedEnergyDistribution > {

  friend class base::DistributionDataWithInterpolationType<
                   TabulatedAngleEnergyDistribution,
                   TabulatedEnergyDistribution >;

  /* fields */

  double incident_ = 0.0;

  /* auxiliary functions */

public:

  /* constructor */

  TabulatedAngleEnergyDistribution() = default;

  TabulatedAngleEnergyDistribution( const TabulatedAngleEnergyDistribution& ) = default;
  TabulatedAngleEnergyDistribution( TabulatedAngleEnergyDistribution&& ) = default;

  TabulatedAngleEnergyDistribution& operator=( const TabulatedAngleEnergyDistribution& ) = default;
  TabulatedAngleEnergyDistribution& operator=( TabulatedAngleEnergyDistribution&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] incident         the incident energy value
   *  @param[in] interpolation    the interpolation type
   *  @param[in] distributions    the distributions for each outgoing energy
   *  @param[in] locb             the starting xss index with respect to the superblock
   */
  TabulatedAngleEnergyDistribution(
      double incident,
      int interpolation,
      std::vector< TabulatedEnergyDistribution > distributions,
      std::size_t locb = 1 ) :
    DistributionDataWithInterpolationType( "TabulatedAngleEnergyDistribution",
                                           interpolation,
                                           std::move( distributions ), locb ),
    incident_( incident ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] incident   the incident energy value
   *  @param[in] locb       the starting xss index with respect to the superblock
   *  @param[in] sig        the begin iterator of the block in the XSS array
   *  @param[in] end        the end iterator of the block in the XSS array
   */
  TabulatedAngleEnergyDistribution( double incident, std::size_t locb,
                                    Iterator begin, Iterator end ) :
    DistributionDataWithInterpolationType( "TabulatedAngleEnergyDistribution",
                                           locb, begin, end ),
    incident_( incident ) {}

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
   *  @brief Return the number of cosine values
   */
  std::size_t NC() const {

    return DistributionDataWithInterpolationType::N();
  }

  /**
   *  @brief Return the number of outgoing cosine values
   */
  std::size_t numberCosines() const {

    return DistributionDataWithInterpolationType::numberValues();
  }

  /**
   *  @brief Return the outgoing cosine values
   */
  auto cosines() const {

    return DistributionDataWithInterpolationType::values( 1 );
  }

  /**
   *  @brief Return the cosine value for a given index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  double cosine( std::size_t index ) const {

    return DistributionDataWithInterpolationType::value( 1, index );
  }

  /**
   *  @brief Return the distribution locator for a cosine index
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
   *  @brief Return the distribution locator for a cosine index
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
   *  @brief Return the relative distribution locator for cosine index
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
  const std::vector< TabulatedEnergyDistribution >& distributions() const {

    return DistributionDataWithInterpolationType::distributions();
  }

  /**
   *  @brief Return the distribution for a cosine index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const TabulatedEnergyDistribution& distribution( std::size_t index ) const {

    return DistributionDataWithInterpolationType::distribution( index );
  }

  using DistributionDataWithInterpolationType::empty;
  using DistributionDataWithInterpolationType::name;
  using DistributionDataWithInterpolationType::length;
  using DistributionDataWithInterpolationType::XSS;
  using DistributionDataWithInterpolationType::begin;
  using DistributionDataWithInterpolationType::end;
};

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
