#ifndef NJOY_ACETK_BLOCK_TABULATEDOUTGOINGANGLEENERGYDISTRIBUTION
#define NJOY_ACETK_BLOCK_TABULATEDOUTGOINGANGLEENERGYDISTRIBUTION

// system includes
#include <variant>

// other includes
#include "ACEtk/block/details/BaseDistributionDataWithInterpolationType.hpp"
#include "ACEtk/block/TabulatedEnergyDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

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
  protected details::BaseDistributionDataWithInterpolationType<
                TabulatedAngleEnergyDistribution,
                TabulatedEnergyDistribution > {

  friend class details::BaseDistributionDataWithInterpolationType<
                   TabulatedAngleEnergyDistribution,
                  TabulatedEnergyDistribution >;

  /* fields */
  double incident_ = 0.0;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/TabulatedAngleEnergyDistribution/src/ctor.hpp"

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

    return BaseDistributionDataWithInterpolationType::interpolation();
  }

  /**
   *  @brief Return the number of cosine values
   */
  std::size_t NC() const {

    return BaseDistributionDataWithInterpolationType::N();
  }

  /**
   *  @brief Return the number of outgoing cosine values
   */
  std::size_t numberCosines() const {

    return BaseDistributionDataWithInterpolationType::numberValues();
  }

  /**
   *  @brief Return the outgoing cosine values
   */
  auto cosines() const {

    return BaseDistributionDataWithInterpolationType::values( 1 );
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

    return BaseDistributionDataWithInterpolationType::value( 1, index );
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

    return BaseDistributionDataWithInterpolationType::LOCC( index );
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

    return BaseDistributionDataWithInterpolationType::distributionLocator( index );
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

    return BaseDistributionDataWithInterpolationType::relativeDistributionLocator( index );
  }

  /**
   *  @brief Return the distributions
   */
  const std::vector< TabulatedEnergyDistribution >& distributions() const {

    return BaseDistributionDataWithInterpolationType::distributions();
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

    return BaseDistributionDataWithInterpolationType::distribution( index );
  }

  using BaseDistributionDataWithInterpolationType::empty;
  using BaseDistributionDataWithInterpolationType::name;
  using BaseDistributionDataWithInterpolationType::length;
  using BaseDistributionDataWithInterpolationType::XSS;
  using BaseDistributionDataWithInterpolationType::begin;
  using BaseDistributionDataWithInterpolationType::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
