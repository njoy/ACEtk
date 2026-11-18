#ifndef NJOY_ACETK_CONTINUOUS_GENERALEVAPORATIONSPECTRUM
#define NJOY_ACETK_CONTINUOUS_GENERALEVAPORATIONSPECTRUM

// system includes

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/Base.hpp"
#include "ACEtk/base/ColumnData.hpp"
#include "ACEtk/base/TabulatedData.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief A general evaporation spectrum
 *
 *  The GeneralEvaporationSpectrum class contains the tabulated energy and
 *  temperature values as well as the bin data used to describe the
 *  general evaporation spectrum. It is used in the DLW block as ACE LAW 5.
 */
class GeneralEvaporationSpectrum : protected base::Base {

  /* fields */

  base::TabulatedData tabulated_;
  base::ColumnData bins_;

  /* auxiliary functions */

  static void verifySize( Iterator begin, Iterator end,
                          unsigned int nr, unsigned int ne, unsigned int net ) {

    auto size = std::distance( begin, end );
    if ( size < 1 + 2 * nr + 1 + 2 * ne + 1 + net ) {

      Log::error( "The size of the XSS subrange in the equiprobable outgoing "
                  "energy data block should be at least 3 + 2 * NR + 2 * NE + NET" );
      Log::info( "NR value: {}", nr );
      Log::info( "NE value: {}", ne );
      Log::info( "NET value: {}", net );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  void generateBlocks() {

    std::size_t nr = static_cast< std::size_t >( this->IXSS( 1 ) );
    std::size_t ne = static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 ) );
    auto begin = this->begin();
    auto bins = begin + 2 * nr + 2 * ne + 2;
    auto end = this->end();

    this->tabulated_ = base::TabulatedData( this->name(), begin, bins );
    this->bins_ = base::ColumnData( this->name(), bins, end, 1 );
  }

  static std::vector< double >
  generateXSS(
    std::vector< long >&& boundaries,
    std::vector< long >&& interpolants,
    std::vector< double >&& energies,
    std::vector< double >&& temperatures,
    std::vector< double >&& bins ) {

    // insert the tabulated data
    std::vector< double > xss;
    const base::TabulatedData table( "GeneralEvaporationSpectrum",
                                     std::move( boundaries ),
                                     std::move( interpolants ),
                                     std::move( energies ),
                                     std::move( temperatures ) );
    xss.insert( xss.end(), table.begin(), table.end() );

    // insert the bin data
    xss.push_back( bins.size() );
    xss.insert( xss.end(), bins.begin(), bins.end() );

    return xss;
  }

public:

  /* constructor */

  GeneralEvaporationSpectrum() = default;

  GeneralEvaporationSpectrum( const GeneralEvaporationSpectrum& base ) :
    Base( base ),
    tabulated_( base.tabulated_ ), bins_( base.bins_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  GeneralEvaporationSpectrum( GeneralEvaporationSpectrum&& base ) :
    Base( std::move( base ) ),
    tabulated_( std::move( base.tabulated_ ) ), bins_( std::move( base.bins_ ) ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  GeneralEvaporationSpectrum& operator=( const GeneralEvaporationSpectrum& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->tabulated_ = base.tabulated_;
      this->bins_ = base.bins_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  GeneralEvaporationSpectrum& operator=( GeneralEvaporationSpectrum&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->tabulated_ = std::move( base.tabulated_ );
      this->bins_ = std::move( base.bins_ );
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] boundaries      the interpolation range boundaries
   *  @param[in] interpolants    the interpolation types for each range
   *  @param[in] energies        the energy values
   *  @param[in] temperatures    the temperature values
   *  @param[in] bins            the x bin values
   */
  GeneralEvaporationSpectrum(
      std::vector< long > boundaries,
      std::vector< long > interpolants,
      std::vector< double > energies,
      std::vector< double > temperatures,
      std::vector< double > bins ) :
    Base( "GeneralEvaporationSpectrum",
          generateXSS( std::move( boundaries ), std::move( interpolants ),
                       std::move( energies ), std::move( temperatures ),
                       std::move( bins ) ) ) {

    this->generateBlocks();
  }

  /**
   *  @brief Constructor without interpolation data
   *
   *  @param[in] energies        the energy values
   *  @param[in] temperatures    the temperature values
   *  @param[in] bins            the x bin values
   */
  GeneralEvaporationSpectrum(
      std::vector< double > energies,
      std::vector< double > temperatures,
      std::vector< double > bins ) :
    GeneralEvaporationSpectrum( {}, {},
                                std::move( energies ), std::move( temperatures ),
                                std::move( bins ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] locb    the starting xss index with respect to the superblock
   *  @param[in] sig     the begin iterator of the block in the XSS array
   *  @param[in] end     the end iterator of the block in the XSS array
   */
  GeneralEvaporationSpectrum( Iterator begin, Iterator end ) :
    Base( "GeneralEvaporationSpectrum", begin, end ) {

    std::size_t nr = static_cast< std::size_t >( this->IXSS( 1 ) );
    std::size_t ne = static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 ) );
    std::size_t nb = static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 + 2 * ne + 1 ) );
    verifySize( this->begin(), this->end(), nr, ne, nb );
    this->generateBlocks();
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::GeneralEvaporation;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::GeneralEvaporation;
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
   *  @brief Return the number of x values
   */
  int NET() const { return this->bins_.N(); }

  /**
   *  @brief Return the number of equiprobable outgoing x bins
   */
  int numberBins() const { return this->NET() - 1; }

  /**
   *  @brief Return the equiprobable x bins
   */
  auto bins() const { return this->bins_.column( 1 ); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using ACELAW5 = GeneralEvaporationSpectrum;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
