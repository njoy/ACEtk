#ifndef NJOY_ACETK_BASE_EVAPORATIONSPECTRUM
#define NJOY_ACETK_BASE_EVAPORATIONSPECTRUM

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/TabulatedData.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief A general evaporation spectrum from the DLW block for a single
 *         reaction
 */
class EvaporationSpectrum : protected Base {

  /* fields */

  TabulatedData tabulated_;
  EnergyDistributionType type_;

  /* auxiliary functions */

  static void verifySize( Iterator begin, Iterator end,
                          unsigned int nr, unsigned int ne ) {

    auto size = std::distance( begin, end );
    if ( size < 1 + 2 * nr + 1 + 2 * ne + 1 ) {

      Log::error( "The size of the XSS subrange in the equiprobable outgoing "
                  "energy data block should be at least 3 + 2 * NR + 2 * NE" );
      Log::info( "NR value: {}", nr );
      Log::info( "NE value: {}", ne );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  void generateBlocks() {

    std::size_t nr = static_cast< std::size_t >( this->IXSS( 1 ) );
    std::size_t ne = static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 ) );
    auto begin = this->begin();
    auto end = begin + 2 * nr + 2 * ne + 2;

    this->tabulated_ = base::TabulatedData( this->name(), begin, end );
  }

  static std::vector< double >
  generateXSS(
    std::vector< long >&& boundaries,
    std::vector< long >&& interpolants,
    std::vector< double >&& energies,
    std::vector< double >&& temperatures,
    double energy ) {

    // insert the tabulated data
    std::vector< double > xss;
    const TabulatedData table( "DLW::GeneralEvaporationSpectrum",
                               std::move( boundaries ),
                               std::move( interpolants ),
                               std::move( energies ),
                               std::move( temperatures ) );
    xss.insert( xss.end(), table.begin(), table.end() );

    // insert the restriction energy
    xss.push_back( energy );

    return xss;
  }

public:

  /* constructor */

  EvaporationSpectrum() = default;

  EvaporationSpectrum( const EvaporationSpectrum& base ) :
    Base( base ), tabulated_( base.tabulated_ ),
    type_( base.type_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  EvaporationSpectrum( EvaporationSpectrum&& base ) :
    Base( std::move( base ) ), tabulated_( std::move( base.tabulated_ ) ),
    type_( base.type_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] name            the name of the block
   *  @param[in] type            the energy distribution type
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] energies        the energy values
   *  @param[in] temperatures    the temperature values
   *  @param[in] energy          the restriction energy
   */
  EvaporationSpectrum( std::string name, EnergyDistributionType type,
                       std::vector< long > boundaries, std::vector< long > interpolants,
                       std::vector< double > energies, std::vector< double > temperatures,
                       double energy ) :
    Base( std::move( name ),
          generateXSS( std::move( boundaries ), std::move( interpolants ),
                       std::move( energies ), std::move( temperatures ),
                       energy ) ),
    type_( type ) {

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
  EvaporationSpectrum( std::string name, EnergyDistributionType type,
                       Iterator begin, Iterator end ) :
    Base( std::move( name ), begin, end ), type_( type ) {

    const auto nr = static_cast< std::size_t >( std::round( this->XSS( 1 ) ) );
    const auto ne = static_cast< std::size_t >( std::round( this->XSS( 1 + 2 * nr + 1 ) ) );
    verifySize( this->begin(), this->end(), nr, ne );
    this->generateBlocks();
  }

  EvaporationSpectrum& operator=( const EvaporationSpectrum& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->tabulated_ = base.tabulated_;
      this->type_ = base.type_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  EvaporationSpectrum& operator=( EvaporationSpectrum&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->tabulated_ = std::move( base.tabulated_ );
      this->type_ = base.type_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  /**
   *  @brief Return the distribution type
   */
  EnergyDistributionType LAW() const {

    return this->type_;
  }

  /**
   *  @brief Return the distribution type
   */
  EnergyDistributionType type() const {

    return this->LAW();
  }

  /**
   *  @brief Return the interpolation data
   */
  auto interpolationData() const {

    return this->tabulated_.interpolationData();
  }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return this->tabulated_.NB(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const {

    return this->tabulated_.numberInterpolationRegions();
  }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return this->tabulated_.NBT(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return this->tabulated_.boundaries(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return this->tabulated_.INT(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return this->tabulated_.interpolants(); }

  /**
   *  @brief Return the number of energy values
   */
  std::size_t NE() const { return this->tabulated_.N(); }

  /**
   *  @brief Return the number of energy values
   */
  std::size_t numberEnergyPoints() const { return this->NE(); }

  /**
   *  @brief Return the energy values
   */
  auto energies() const { return this->tabulated_.x(); }

  /**
   *  @brief Return the cross section values
   */
  auto temperatures() const { return this->tabulated_.y(); }

  /**
   *  @brief Return the minimum incident energy for the distribution
   */
  double minimumIncidentEnergy() const {

    return this->energies().front();
  }

  /**
   *  @brief Return the maximum incident energy for the distribution
   */
  double maximumIncidentEnergy() const {

    return this->energies().back();
  }

  /**
   *  @brief Return the restriction energy
   */
  double U() const { return *this->tabulated_.end(); }

  /**
   *  @brief Return the restriction energy
   */
  double restrictionEnergy() const { return this->U(); }

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
