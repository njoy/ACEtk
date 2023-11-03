#ifndef NJOY_ACETK_CONTINUOUS_ANGLEENERGYDISTRIBUTIONDATA
#define NJOY_ACETK_CONTINUOUS_ANGLEENERGYDISTRIBUTIONDATA

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/DistributionData.hpp"
#include "ACEtk/continuous/TabulatedAngleEnergyDistribution.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Correlated outgoing energy-angle distribution data using tabulated
 *         distributions ordered as E, mu, E'
 *
 *  The AngleEnergyDistributionData class contains the energy-angle distributions
 *  for a set of incident energy values. It is used in the DLW block as ACE LAW 67.
 */
class AngleEnergyDistributionData :
  protected base::DistributionData< AngleEnergyDistributionData,
                                    TabulatedAngleEnergyDistribution > {

  friend class base::DistributionData< AngleEnergyDistributionData,
                                       TabulatedAngleEnergyDistribution >;

  /* fields */

protected:

  /* auxiliary functions */
  #include "ACEtk/continuous/AngleEnergyDistributionData/src/generateXSS.hpp"

public:

  /* constructor */
  #include "ACEtk/continuous/AngleEnergyDistributionData/src/ctor.hpp"

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::TabulatedEnergyAngle;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::TabulatedEnergyAngle;
  }

  /**
   *  @brief Return the interpolation data
   */
  auto interpolationData() const {

    return DistributionData::interpolationData();
  }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return DistributionData::NB(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const {

    return DistributionData::numberInterpolationRegions();
  }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return DistributionData::NBT(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return DistributionData::boundaries(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return DistributionData::INT(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return DistributionData::interpolants(); }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t NE() const { return DistributionData::N(); }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t numberIncidentEnergies() const {

    return DistributionData::numberValues();
  }

  /**
   *  @brief Return the incident energy values
   */
  auto incidentEnergies() const {

    return DistributionData::values( 1 );
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

    return DistributionData::value( 1, index );
  }

  /**
   *  @brief Return the minimum incident energy for the distribution
   */
  double minimumIncidentEnergy() const {

    return this->incidentEnergy( 1 );
  }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const {

    return this->incidentEnergy( this->NE() );
  }

  /**
   *  @brief Return the distribution locator for an incident energy index
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

    return DistributionData::LOCC( index );
  }

  /**
   *  @brief Return the distribution locator for an incident energy index
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

    return DistributionData::distributionLocator( index );
  }

  /**
   *  @brief Return the relative distribution locator for an incident energy
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

    return DistributionData::relativeDistributionLocator( index );
  }

  /**
   *  @brief Return the distributions
   */
  const std::vector< TabulatedAngleEnergyDistribution >& distributions() const {

    return DistributionData::distributions();
  }

  /**
   *  @brief Return the distribution for an incident energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const TabulatedAngleEnergyDistribution& distribution( std::size_t index ) const {

    return DistributionData::distribution( index );
  }

  using DistributionData::empty;
  using DistributionData::name;
  using DistributionData::length;
  using DistributionData::XSS;
  using DistributionData::begin;
  using DistributionData::end;
};

using ACELAW67 = AngleEnergyDistributionData;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
