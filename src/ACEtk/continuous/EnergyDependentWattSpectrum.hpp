#ifndef NJOY_ACETK_CONTINUOUS_ENERGYDEPENDENTWATTSPECTRUM
#define NJOY_ACETK_CONTINUOUS_ENERGYDEPENDENTWATTSPECTRUM

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/continuous/ParameterData.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief An energy dependent Watt spectrum
 *
 *  The EnergyDependentWattSpectrum class contains the tabulated values for the
 *  energy dependent a and b parameters as well as the restriction energy U used
 *  to describe the Watt spectrum. It is used in the DLW block as ACE LAW 11.
 */
class EnergyDependentWattSpectrum : protected base::Base {

  /* fields */

  ParameterData a_;
  ParameterData b_;

  /* auxiliary functions */

  static void verifySize( Iterator begin, Iterator end,
                          unsigned int nra, unsigned int nea,
                          unsigned int nrb, unsigned int neb ) {

    auto size = std::distance( begin, end );
    if ( size < 1 + 2 * nra + 1 + 2 * nea +
                1 + 2 * nrb + 1 + 2 * neb +
                1 ) {

      Log::error( "The size of the XSS subrange in the Watt spectrum data block "
                  "should be at least 3 + 2 * ( NRA + NRB ) + 2 * ( NEA + NEB )" );
      Log::info( "NRA value: {}", nra );
      Log::info( "NEA value: {}", nea );
      Log::info( "NRB value: {}", nrb );
      Log::info( "NEB value: {}", neb );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  void generateBlocks() {

    std::size_t nr = static_cast< std::size_t >( this->IXSS( 1 ) );
    std::size_t ne = static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 ) );
    auto begina = this->begin();
    auto beginb = begina + 2 * nr + 2 * ne + 2;
    std::size_t distance = std::distance( begina, beginb );
    nr = static_cast< std::size_t >( this->IXSS( distance + 1 ) );
    ne = static_cast< std::size_t >( this->IXSS( distance + 1 + 2 * nr + 1 ) );
    auto end = beginb + 2 * nr + 2 * ne + 2;

    this->a_ = continuous::ParameterData( begina, beginb );
    this->b_ = continuous::ParameterData( beginb, end );
  }

  static std::vector< double >
  generateXSS( ParameterData&& a, ParameterData&& b, double energy ) {

    std::vector< double > xss;
    xss.insert( xss.end(), a.begin(), a.end() );
    xss.insert( xss.end(), b.begin(), b.end() );
    xss.push_back( energy );

    return xss;
  }

public:

  /* constructor */

  EnergyDependentWattSpectrum() = default;

  EnergyDependentWattSpectrum( const EnergyDependentWattSpectrum& base ) :
    Base( base ), a_( base.a_ ), b_( base.b_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  EnergyDependentWattSpectrum( EnergyDependentWattSpectrum&& base ) :
    Base( std::move( base ) ),
    a_( std::move( base.a_ ) ),
    b_( std::move( base.b_ ) ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  EnergyDependentWattSpectrum& operator=( const EnergyDependentWattSpectrum& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->a_ = base.a_;
      this->b_ = base.b_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  EnergyDependentWattSpectrum& operator=( EnergyDependentWattSpectrum&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->a_ = std::move( base.a_ );
      this->b_ = std::move( base.b_ );
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] a         the data for the a parameter
   *  @param[in] b         the data for the b parameter
   *  @param[in] energy    the restriction energy
   */
  EnergyDependentWattSpectrum(
      ParameterData a,
      ParameterData b,
      double energy ) :
    Base( "EnergyDependentWattSpectrum",
          generateXSS( std::move( a ), std::move( b ), energy ) ) {

    this->generateBlocks();
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] name     the name of the block
   *  @param[in] type     the energy distribution type
   *  @param[in] begin    the begin iterator of the block in the XSS array
   *  @param[in] end      the end iterator of the block in the XSS array
   */
  EnergyDependentWattSpectrum( Iterator begin, Iterator end ) :
    Base( "EnergyDependentWattSpectrum", begin, end ) {

    std::size_t nra = static_cast< std::size_t >( this->IXSS( 1 ) );
    std::size_t nea = static_cast< std::size_t >( this->IXSS( 1 + 2 * nra + 1 ) );
    std::size_t size = 2 + 2 * nra + 2 * nea;
    std::size_t nrb = static_cast< std::size_t >( this->IXSS( size + 1 ) );
    std::size_t neb = static_cast< std::size_t >( this->IXSS( size + 1 + 2 * nrb + 1 ) );
    verifySize( this->begin(), this->end(), nra, nea, nrb, neb );
    this->generateBlocks();
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::Watt;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::Watt;
  }

  /**
   *  @brief Return the data for the a parameter
   */
  const ParameterData& a() const { return this->a_; }

  /**
   *  @brief Return the data for the b parameter
   */
  const ParameterData& b() const { return this->b_; }

  /**
   *  @brief Return the minimum incident energy for the distribution
   */
  double minimumIncidentEnergy() const {

    return this->a().energies().front();
  }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const {

    return this->a().energies().back();
  }

  /**
   *  @brief Return the restriction energy
   */
  double U() const { return *this->b_.end(); }

  /**
   *  @brief Return the restriction energy
   */
  double restrictionEnergy() const { return this->U(); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
