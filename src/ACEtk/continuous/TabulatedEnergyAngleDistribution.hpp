#ifndef NJOY_ACETK_CONTINUOUS_TABULATEDENERGYANGLEDISTRIBUTION
#define NJOY_ACETK_CONTINUOUS_TABULATEDENERGYANGLEDISTRIBUTION

// system includes
#include <variant>

// other includes
#include "ACEtk/base/DistributionDataWithInterpolationType.hpp"
#include "ACEtk/continuous/TabulatedAngularDistributionWithProbability.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

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

  static std::vector< double >
  generateXSS( const std::string&,
               unsigned int interpolation,
               std::vector< TabulatedAngularDistributionWithProbability >&& distributions,
               std::size_t locb ) {

    // add the distribution data to the xss array
    const auto ne = distributions.size();
    std::vector< double > xss( 1 + 4 * ne );
    xss[0] = static_cast< double >( ne );
    std::size_t index = 1;
    const auto offset = 1 + locb;
    for ( const auto& distribution : distributions ) {

      // set the associated energy, probability and cumulative probability value
      xss[index] = distribution.energy();
      xss[index + ne] = distribution.probability();
      xss[index + 2 * ne] = distribution.cumulativeProbability();

      // set the locator
      xss[index + 3 * ne] = static_cast< double >( xss.size() + offset );

      // insert the xss array
      xss.insert( xss.end(), distribution.begin(), distribution.end() );

      // on to the next distribution
      ++index;
    }

    // insert the interpolation data in the front
    xss.insert( xss.begin(), static_cast< double >( interpolation ) );

    return xss;
  }

  void generateBlocks() {

    this->distributions_.clear();

    std::size_t ne = static_cast< std::size_t >( this->IXSS( 2 ) );
    auto data = this->begin() + 1;
    auto end = data + 4 * ne + 1;

    this->values_ = base::ColumnData( std::string( this->name() ), data, end, 4 );
    for ( unsigned int index = 1; index <= this->values_.N(); ++index ) {

      const double energy = this->values_.value( 1, index );
      const double probability = this->values_.value( 2, index );
      const double cumulative = this->values_.value( 3, index );
      const auto locator = this->relativeDistributionLocator( index );
      const auto left = std::next( this->begin(), locator - 1 );
      const auto right = index == this->numberValues()
                         ? this->end()
                         : std::next( this->begin(),
                           this->relativeDistributionLocator( index + 1 ) - 1 );
      this->distributions_.emplace_back( energy, probability,
                                         cumulative, left, right );
    }
  }

public:

  /* constructor */

  TabulatedEnergyAngleDistribution() = default;

  TabulatedEnergyAngleDistribution( const TabulatedEnergyAngleDistribution& ) = default;
  TabulatedEnergyAngleDistribution( TabulatedEnergyAngleDistribution&& ) = default;

  TabulatedEnergyAngleDistribution& operator=( const TabulatedEnergyAngleDistribution& ) = default;
  TabulatedEnergyAngleDistribution& operator=( TabulatedEnergyAngleDistribution&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] incident         the incident energy value
   *  @param[in] interpolation    the interpolation type
   *  @param[in] distributions    the distributions for each outgoing energy
   *  @param[in] locb             the starting xss index with respect to the superblock
   */
  TabulatedEnergyAngleDistribution(
      double incident,
      int interpolation,
      std::vector< TabulatedAngularDistributionWithProbability > distributions,
      std::size_t locb = 1 ) :
    DistributionDataWithInterpolationType( "TabulatedEnergyAngleDistribution",
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
  TabulatedEnergyAngleDistribution( double incident, std::size_t locb,
                                    Iterator begin, Iterator end ) :
    DistributionDataWithInterpolationType( "TabulatedEnergyAngleDistribution",
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

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
