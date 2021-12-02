#ifndef NJOY_ACETK_BLOCK_TABULATEDOUTGOINGENERGYANGLEDISTRIBUTION
#define NJOY_ACETK_BLOCK_TABULATEDOUTGOINGENERGYANGLEDISTRIBUTION

// system includes
#include <variant>

// other includes
#include "ACEtk/block/details/BaseDistributionData.hpp"
#include "ACEtk/block/TabulatedAngularDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Tabulated outgoing energy and angle distribution data for a single
 *         incident energy
 *
 *  The TabulatedOutgoingEnergyAngleDistribution class contains the
 *  tabulated angular distributions for a set of outgoing energy values and
 *  associated incident energy value. It is used in the
 *  OutgoingEnergyAngleDistributionData (ACE LAW 61) in the DLW block.
 */
class TabulatedOutgoingEnergyAngleDistribution :
  protected details::BaseDistributionData< TabulatedAngularDistribution > {

  /* fields */
  double incident_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/TabulatedOutgoingEnergyAngleDistribution/src/ctor.hpp"

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
   *  @brief Return the number of outgoing energy values
   */
  std::size_t NE() const { return BaseDistributionData::N(); }

  /**
   *  @brief Return the number of outgoing energy values
   */
  std::size_t numberOutgoingEnergies() const {

    return BaseDistributionData::numberValues();
  }

  /**
   *  @brief Return the outgoing energy values
   */
  auto outgoingEnergies() const {

    return BaseDistributionData::values();
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

    return BaseDistributionData::value( index );
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

    return BaseDistributionData::LOCC( index );
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

    return BaseDistributionData::distributionLocator( index );
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

    return BaseDistributionData::relativeDistributionLocator( index );
  }

  /**
   *  @brief Return the distributions
   */
  const std::vector< TabulatedAngularDistribution >& distributions() const {

    return BaseDistributionData::distributions();
  }

  /**
   *  @brief Return the distribution for an outgoing energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const TabulatedAngularDistribution& distribution( std::size_t index ) const {

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
