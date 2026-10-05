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

  static std::vector< double >
  generateXSS( const std::string& name,
               std::vector< long >&& boundaries,
               std::vector< long >&& interpolants,
               std::vector< TabulatedAngleEnergyDistribution >&& distributions,
               std::size_t locb ) {

    // add the distribution data to the xss array
    const auto nr = boundaries.size();
    const auto ne = distributions.size();
    std::vector< double > xss( 1 + 2 * ne );
    xss[0] = ne;
    std::size_t index = 1;
    const auto offset = 1 + 2 * nr + locb;
    for ( const auto& distribution : distributions ) {

      // set the associated value
      xss[index] = distribution.value();

      // set the locator
      xss[index + ne] = xss.size() + offset;

      // remake the internal xss array with the proper locators
      const TabulatedAngleEnergyDistribution temp(
                distribution.value(),
                distribution.interpolation(),
                std::move( distribution.distributions() ),
                xss[index + ne] );
      xss.insert( xss.end(), temp.begin(), temp.end() );

      // on to the next distribution
      ++index;
    }

    // insert the interpolation data in the front
    InterpolationData interpolation( std::string( name ),
                                     std::move( boundaries ),
                                     std::move( interpolants ) );
    xss.insert( xss.begin(), interpolation.begin(), interpolation.end() );

    return xss;
  }

public:

  /* constructor */

  AngleEnergyDistributionData() = default;

  AngleEnergyDistributionData( const AngleEnergyDistributionData& ) = default;
  AngleEnergyDistributionData( AngleEnergyDistributionData&& ) = default;

  AngleEnergyDistributionData& operator=( const AngleEnergyDistributionData& ) = default;
  AngleEnergyDistributionData& operator=( AngleEnergyDistributionData&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] boundaries       the interpolation range boundaries
   *  @param[in] interpolants     the interpolation types for each range
   *  @param[in] distributions    the distributions for each incident energy
   *  @param[in] locb             the starting xss index with respect to the superblock
   */
  AngleEnergyDistributionData(
      std::vector< long > boundaries,
      std::vector< long > interpolants,
      std::vector< TabulatedAngleEnergyDistribution > distributions,
      std::size_t locb = 1 ) :
    DistributionData( "AngleEnergyDistributionData",
                      std::move( boundaries ), std::move( interpolants ),
                      std::move( distributions ), locb ) {}

  /**
   *  @brief Constructor without interpolation data
   *
   *  @param[in] distributions    the distributions for each incident energy
   *  @param[in] locb             the starting xss index with respect to the superblock
   */
  AngleEnergyDistributionData(
      std::vector< TabulatedAngleEnergyDistribution > distributions,
      std::size_t locb = 1 ) :
    AngleEnergyDistributionData( {}, {}, std::move( distributions ), locb ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] locb    the starting xss index with respect to the superblock
   *  @param[in] sig     the begin iterator of the block in the XSS array
   *  @param[in] end     the end iterator of the block in the XSS array
   */
  AngleEnergyDistributionData( std::size_t locb, Iterator begin, Iterator end ) :
    DistributionData( "AngleEnergyDistributionData", locb, begin, end ) {}

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
