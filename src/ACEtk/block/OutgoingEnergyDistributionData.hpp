#ifndef NJOY_ACETK_BLOCK_OUTGOINGENERGYDISTRIBUTIONDATA
#define NJOY_ACETK_BLOCK_OUTGOINGENERGYDISTRIBUTIONDATA

// system includes
#include <variant>

// other includes
#include "utility/overload.hpp"
#include "ACEtk/block/details/BaseDistributionData.hpp"
#include "ACEtk/block/TabulatedOutgoingEnergyDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Angular distribution data from the AND block for a single reaction
 */
class OutgoingEnergyDistributionData :
  protected details::BaseDistributionData< TabulatedOutgoingEnergyDistribution > {

  /* fields */

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/block/OutgoingEnergyDistributionData/src/ctor.hpp"

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t NE() const { return BaseDistributionData::NE(); }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t numberIncidentEnergies() const {

    return BaseDistributionData::numberIncidentEnergies();
  }

  /**
   *  @brief Return the incident energy values
   */
  auto incidentEnergies() const {

    return BaseDistributionData::incidentEnergies();
  }

  /**
   *  @brief Return the incident energy for a given index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  double incidentEnergy( std::size_t index ) const {

    return BaseDistributionData::incidentEnergy( index );
  }

  /**
   *  @brief Return the outgoing energy distribution locator for an incident
   *         energy index
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
   *  @brief Return the outgoing energy distribution locator for an incident
   *         energy index
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
   *  @brief Return the relative angular distribution locator for an incident
   *         energy index
   *
   *  This is the locator relative to the beginning of the current outgoing
   *  energy distribution block in the DLW block.
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
   *  @brief Return the angular distribution data for an incident energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  TabulatedOutgoingEnergyDistribution
  outgoingEnergyDistribution( std::size_t index ) const {

    return BaseDistributionData::distribution( index );
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
