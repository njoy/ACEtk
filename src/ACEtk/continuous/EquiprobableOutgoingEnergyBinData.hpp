#ifndef NJOY_ACETK_CONTINUOUS_EQUIPROBABLEOUTGOINGENERGYBINDATA
#define NJOY_ACETK_CONTINUOUS_EQUIPROBABLEOUTGOINGENERGYBINDATA

// system includes
#include <algorithm>

// other includes
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/Base.hpp"
#include "ACEtk/base/ColumnData.hpp"
#include "ACEtk/continuous/InterpolationData.hpp"
#include "ACEtk/continuous/EquiprobableOutgoingEnergyBins.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Equiprobable outgoing energy bin data
 *
 *  The EquiprobableOutgoingEnergyBinData class contains the equiprobable bins
 *  for a set of incident energy values. It is used in the AND block. This
 *  format is only used in old ACE data. It is used in the DLW block as ACE LAW 1.
 */
class EquiprobableOutgoingEnergyBinData : protected base::Base {

  /* fields */

  InterpolationData interpolation_;
  base::ColumnData energies_;
  std::vector< EquiprobableOutgoingEnergyBins > bins_;

  /* auxiliary functions */

  static void verifySize( Iterator begin, Iterator end,
                          unsigned int nr, unsigned int ne, unsigned int net ) {

    auto size = std::distance( begin, end );
    if ( size < 1 + 2 * nr + 1 + ne + 1 + ne * net ) {

      Log::error( "The size of the XSS subrange in the equiprobable outgoing "
                  "energy data block should be at least 3 + 2 * NR + NE * ( NET + 1 )" );
      Log::info( "NR value: {}", nr );
      Log::info( "NE value: {}", ne );
      Log::info( "NET value: {}", net );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  void verifyIncidentEnergyIndex( const std::size_t index ) const {

    if ( ( index < 1 ) || ( index > this->numberIncidentEnergies() ) ) {

      Log::error( "Illegal incident energy index argument into {} block",
                  this->name() );
      Log::info( "Index value: {}", index );
      Log::info( "{} accepts an incident energy index between 1 and {} inclusively",
                 this->name(), this->numberIncidentEnergies() );
      throw std::out_of_range( this->name() );
    }
  }

  void generateBlocks() {

    this->bins_.clear();

    std::size_t nr = static_cast< std::size_t >( this->IXSS( 1 ) );
    std::size_t ne = static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 ) );
    auto begin = this->begin();
    auto incident = begin + 2 * nr + 1;
    auto bins = incident + ne + 1;

    this->interpolation_ = continuous::InterpolationData( this->name(),
                                                          begin, incident );
    this->energies_ = base::ColumnData( this->name(), incident, bins, 1 );

    for ( unsigned int index = 1; index <= ne; ++index ) {

      this->bins_.emplace_back( this->incidentEnergy( index ),
                                bins + 1 + this->NET() * ( index - 1 ),
                                bins + 1 + this->NET() * index );
    }
  }

  static std::vector< double >
  generateXSS(
    std::vector< long >&& boundaries,
    std::vector< long >&& interpolants,
    std::vector< EquiprobableOutgoingEnergyBins >&& distributions ) {

    // reserve size in the vector
    const auto nr = boundaries.size();
    const auto ne = distributions.size();
    std::vector< double > xss( 2 + ne ); // NE, list of energies, NET

    // sort distributions
    std::sort( distributions.begin(), distributions.end(),
               [=] ( const auto& left, const auto& right )
                   { return left.incidentEnergy() < right.incidentEnergy(); } );

    // insert the interpolation data
    const InterpolationData interpolation( "EquiprobableOutgoingEnergyBinData",
                                           std::move( boundaries ),
                                           std::move( interpolants ) );
    xss.insert( xss.begin(), interpolation.begin(), interpolation.end() );

    // insert the bin data
    xss[ 1 + 2 * nr ] = static_cast< double >( ne );
    xss[ 2 + 2 * nr + ne ] = static_cast< double >( distributions.front().numberBins() + 1 );
    std::size_t index = 2 + 2 * nr;
    for ( const auto& distribution : distributions ) {

      xss[index] = distribution.incidentEnergy();
      xss.insert( xss.end(), distribution.begin(), distribution.end() );
      ++index;
    }

    return xss;
  }

public:

  /* constructor */

  EquiprobableOutgoingEnergyBinData() = default;

  EquiprobableOutgoingEnergyBinData( const EquiprobableOutgoingEnergyBinData& base ) :
    Base( base ), interpolation_( base.interpolation_ ),
    energies_( base.energies_ ),
    bins_( base.bins_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  EquiprobableOutgoingEnergyBinData( EquiprobableOutgoingEnergyBinData&& base ) :
    Base( std::move( base ) ), interpolation_( std::move( base.interpolation_ ) ),
    energies_( std::move( base.energies_ ) ),
    bins_( std::move( base.bins_ ) ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  EquiprobableOutgoingEnergyBinData& operator=( const EquiprobableOutgoingEnergyBinData& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->interpolation_ = base.interpolation_;
      this->energies_ = base.energies_;
      this->bins_ = base.bins_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  EquiprobableOutgoingEnergyBinData& operator=( EquiprobableOutgoingEnergyBinData&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->interpolation_ = std::move( base.interpolation_ );
      this->energies_ = std::move( base.energies_ );
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
   *  @param[in] boundaries       the interpolation range boundaries
   *  @param[in] interpolants     the interpolation types for each range
   *  @param[in] distributions    the distributions for each incident energy
   */
  EquiprobableOutgoingEnergyBinData(
      std::vector< long > boundaries,
      std::vector< long > interpolants,
      std::vector< EquiprobableOutgoingEnergyBins > distributions ) :
    Base( "EquiprobableOutgoingEnergyBinData",
          generateXSS( std::move( boundaries ), std::move( interpolants ),
                       std::move( distributions ) ) ) {

    this->generateBlocks();
  }

  /**
   *  @brief Constructor without interpolation data
   *
   *  @param[in] distributions    the distributions for each incident energy
   */
  EquiprobableOutgoingEnergyBinData(
      std::vector< EquiprobableOutgoingEnergyBins >&& distributions ) :
    EquiprobableOutgoingEnergyBinData( {}, {}, std::move( distributions ) ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] locb    the starting xss index with respect to the superblock
   *  @param[in] sig     the begin iterator of the block in the XSS array
   *  @param[in] end     the end iterator of the block in the XSS array
   */
  EquiprobableOutgoingEnergyBinData( Iterator begin, Iterator end ) :
    Base( "EquiprobableOutgoingEnergyBinData", begin, end ) {

    std::size_t nr = static_cast< std::size_t >( this->IXSS( 1 ) );
    std::size_t ne = static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 ) );
    std::size_t nb = static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 + ne + 1 ) );
    verifySize( this->begin(), this->end(), nr, ne, nb );
    this->generateBlocks();
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::Equiprobable;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::Equiprobable;
  }

  /**
   *  @brief Return the interpolation data
   */
  auto interpolationData() const { return this->interpolation_; }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t NB() const { return this->interpolationData().NB(); }

  /**
   *  @brief Return the number of interpolation regions
   */
  std::size_t numberInterpolationRegions() const { return this->NB(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto NBT() const { return this->interpolationData().NBT(); }

  /**
   *  @brief Return the interpolation boundaries
   */
  auto boundaries() const { return this->NBT(); }

  /**
   *  @brief Return the interpolants
   */
  auto INT() const { return this->interpolationData().INT(); }

  /**
   *  @brief Return the interpolants
   */
  auto interpolants() const { return this->INT(); }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t NE() const { return this->energies_.N(); }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the incident energy values
   */
  auto incidentEnergies() const { return this->energies_.column( 1 ); }

  /**
   *  @brief Return the incident energy for a given index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  double incidentEnergy( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIncidentEnergyIndex( index );
    #endif
    return this->energies_.value( 1, index );
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
   *  @brief Return the number of outgoing energy values for each incident energy
   */
  std::size_t NET() const {

    std::size_t nr = this->NB();
    std::size_t ne = this->NE();
    return static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 + ne + 1 ) );
  }

  /**
   *  @brief Return the number of equiprobable outgoing energy bins
   */
  std::size_t numberBins() const { return this->NET() - 1; }

  /**
   *  @brief Return the distributions
   */
  const std::vector< EquiprobableOutgoingEnergyBins >& distributions() const {

    return this->bins_;
  }

  /**
   *  @brief Return the distribution for an incident energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const EquiprobableOutgoingEnergyBins& distribution( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIncidentEnergyIndex( index );
    #endif
    return this->bins_[ index - 1 ];
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using ACELAW1 = EquiprobableOutgoingEnergyBinData;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
