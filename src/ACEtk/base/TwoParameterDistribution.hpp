#ifndef NJOY_ACETK_BASE_TWOPARAMETERDISTRIBUTION
#define NJOY_ACETK_BASE_TWOPARAMETERDISTRIBUTION

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief Base class for a distribution using two parameters
 */
class TwoParameterDistribution : protected Base {

  /* fields */

  double emin_;
  double emax_;

  /* auxiliary functions */

  static void verifySize( Iterator begin, Iterator end ) {

    // there are at least 2 values in the block
    auto size = std::distance( begin, end );
    if ( size < 2 ) {

      Log::error( "The size of the XSS subrange should be at least 2 for a "
                  "two parameter distribution" );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

public:

  /* constructor */

  TwoParameterDistribution() = default;

  TwoParameterDistribution( const TwoParameterDistribution& ) = default;
  TwoParameterDistribution( TwoParameterDistribution&& ) = default;

  TwoParameterDistribution& operator=( const TwoParameterDistribution& ) = default;
  TwoParameterDistribution& operator=( TwoParameterDistribution&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] name    the name of the block
   *  @param[in] emin    the minimum energy for the distribution
   *  @param[in] emax    the maximum energy for the distribution
   *  @param[in] c1      the value of C1
   *  @param[in] c2      the value of C2
   */
  TwoParameterDistribution( std::string name, double emin, double emax,
                            double c1, double c2 ) :
    Base( std::move( name ), { c1, c2 } ),
    emin_( emin ), emax_( emax ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] name    the name of the block
   *  @param[in] begin   the begin iterator of the block
   *  @param[in] end     the end iterator of the block
   *  @param[in] emin    the minimum energy for the distribution
   *  @param[in] emax    the maximum energy for the distribution
   */
  TwoParameterDistribution( std::string name, Iterator begin, Iterator end,
                            double emin, double emax ) :
    Base( std::move( name ), begin, end ),
    emin_( emin ), emax_( emax ) {

    verifySize( this->begin(), this->end() );
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::LevelScattering;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::LevelScattering;
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
   *  @brief Return the value of C1
   */
  double C1() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the value of C2
   */
  double C2() const { return this->XSS( 2 ); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::IXSS;
  using Base::begin;
  using Base::end;
};

} // base namespace
} // ACEtk namespace
} // njoy namespace

#endif
