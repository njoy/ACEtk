#ifndef NJOY_ACETK_CONTINUOUS_NBODYPHASESPACEDISTRIBUTION
#define NJOY_ACETK_CONTINUOUS_NBODYPHASESPACEDISTRIBUTION

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/Base.hpp"
#include "ACEtk/base/ColumnData.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief The energy distribution uses the N-body phase space formalism
 *
 *  The NBodyPhaseSpaceDistribution class contains two parameter values that
 *  determine the distribution: the number of particles in the system and the
 *  total mass ratio. It is used in the DLW block as ACE LAW 66.
 */
class NBodyPhaseSpaceDistribution : protected base::Base {

  /* fields */

  double emin_ = 0.0;
  double emax_ = 0.0;

  /* auxiliary functions */

  static std::vector< double > generateXSS( unsigned int npsx, double ap,
                                            unsigned int interpolation,
                                            std::vector< double >&& values,
                                            std::vector< double >&& pdf,
                                            std::vector< double >&& cdf ) {

    std::vector< double > xss = { static_cast< double >( npsx ), ap,
                                  static_cast< double >( interpolation ) };
    xss.reserve( 5 + 3 * values.size() );
    const base::ColumnData columns( "NBodyPhaseSpaceDistribution",
                                    std::move( values ),
                                    std::move( pdf ),
                                    std::move( cdf ) );
    xss.insert( xss.end(), columns.begin(), columns.end() );

    return xss;
  }

  static void verifySize( Iterator begin, Iterator end ) {

    // there are at least 2 values in the block
    auto size = std::distance( begin, end );
    if ( size < 2 ) {

      Log::error( "The size of the XSS subrange in the DLW block should be at "
                  "least 2 for an N-body phase space distribution" );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

public:

  /* constructor */

  NBodyPhaseSpaceDistribution() = default;

  NBodyPhaseSpaceDistribution( const NBodyPhaseSpaceDistribution& ) = default;
  NBodyPhaseSpaceDistribution( NBodyPhaseSpaceDistribution&& ) = default;

  NBodyPhaseSpaceDistribution& operator=( const NBodyPhaseSpaceDistribution& ) = default;
  NBodyPhaseSpaceDistribution& operator=( NBodyPhaseSpaceDistribution&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] emin             the minimum energy for the distribution
   *  @param[in] emax             the maximum energy for the distribution
   *  @param[in] npsx             the number of particles in the system
   *  @param[in] ap               the total mass ratio
   *  @param[in] interpolation    the interpolation flag
   *  @param[in] values           the xi values
   *  @param[in] pdf              the pdf values
   *  @param[in] cdf              the cdf values
   */
  NBodyPhaseSpaceDistribution( double emin, double emax,
                               unsigned int npsx, double ap,
                               unsigned int interpolation,
                               std::vector< double > values,
                               std::vector< double > pdf,
                               std::vector< double > cdf ) :
    Base( "NBodyPhaseSpaceDistribution",
          generateXSS( npsx, ap, interpolation, std::move( values ),
                       std::move( pdf ), std::move( cdf ) ) ),
    emin_( emin ), emax_( emax ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] begin   the begin iterator of the block
   *  @param[in] end     the end iterator of the block
   *  @param[in] emin    the minimum energy for the distribution
   *  @param[in] emax    the maximum energy for the distribution
   */
  NBodyPhaseSpaceDistribution( Iterator begin, Iterator end,
                               double emin, double emax ) :
    Base( "NBodyPhaseSpaceDistribution", begin, end ),
    emin_( emin ), emax_( emax ) {

    verifySize( this->begin(), this->end() );
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::NBodyPhaseSpace;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::NBodyPhaseSpace;
  }

  /**
   *  @brief Return the minimum incident energy for the distribution
   */
  double minimumIncidentEnergy() const { return this->emin_; }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const { return this->emax_; }

  /**
   *  @brief Return the number of particles in the system
   */
  unsigned int NPSX() const { return this->IXSS( 1 ); }

  /**
   *  @brief Return the number of particles in the system
   */
  unsigned int numberParticles() const { return this->NPSX(); }

  /**
   *  @brief Return the total mass ratio of the particles
   */
  double AP() const { return this->XSS( 2 ); }

  /**
   *  @brief Return the total mass ratio of the particles
   */
  double totalMassRatio() const { return this->AP(); }

  /**
   *  @brief Return the interpolation flag
   */
  int interpolation() const { return this->IXSS( 3 ); }

  /**
   *  @brief Return the number of normalised energy values
   */
  std::size_t numberValues() const { return this->IXSS( 4 ); }

  /**
   *  @brief Return the normalised energy values
   */
  auto values() const {

    return this->XSS( 5, this->numberValues() );
  }

  /**
   *  @brief Return the pdf values
   */
  auto pdf() const {

    return this->XSS( 5 + this->numberValues(), this->numberValues() );
  }

  /**
   *  @brief Return the cdf values
   */
  auto cdf() const {

    return this->XSS( 5 + 2 * this->numberValues(), this->numberValues() );
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using ACELAW66 = NBodyPhaseSpaceDistribution;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
