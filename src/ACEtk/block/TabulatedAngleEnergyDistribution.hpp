#ifndef NJOY_ACETK_BLOCK_TABULATEDOUTGOINGANGLEENERGYDISTRIBUTION
#define NJOY_ACETK_BLOCK_TABULATEDOUTGOINGANGLEENERGYDISTRIBUTION

// system includes
#include <variant>

// other includes
#include "ACEtk/block/details/BaseDistributionData.hpp"
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
  protected details::BaseDistributionData< TabulatedEnergyDistribution > {

  /* fields */
  double incident_;

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
   *  @brief Return the interpolation data
   */
  auto interpolationData() const {

    return BaseDistributionData::interpolationData();
  }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return BaseDistributionData::NB(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const {

    return BaseDistributionData::numberInterpolationRegions();
  }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return BaseDistributionData::NBT(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return BaseDistributionData::boundaries(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return BaseDistributionData::INT(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return BaseDistributionData::interpolants(); }

  /**
   *  @brief Return the number of cosine values
   */
  std::size_t NC() const { return BaseDistributionData::N(); }

  /**
   *  @brief Return the number of outgoing cosine values
   */
  std::size_t numberCosines() const {

    return BaseDistributionData::numberValues();
  }

  /**
   *  @brief Return the outgoing cosine values
   */
  auto cosines() const {

    return BaseDistributionData::values();
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

    return BaseDistributionData::value( index );
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

    return BaseDistributionData::LOCC( index );
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

    return BaseDistributionData::distributionLocator( index );
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

    return BaseDistributionData::relativeDistributionLocator( index );
  }

  /**
   *  @brief Return the distributions
   */
  const std::vector< TabulatedEnergyDistribution >& distributions() const {

    return BaseDistributionData::distributions();
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

    return BaseDistributionData::distribution( index );
  }

  using BaseDistributionData::empty;
  using BaseDistributionData::name;
  using BaseDistributionData::length;
  using BaseDistributionData::XSS;
  using BaseDistributionData::begin;
  using BaseDistributionData::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
