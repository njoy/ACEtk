#ifndef NJOY_ACETK_CONTINUOUS_ANGULARDISTRIBUTIONDATA
#define NJOY_ACETK_CONTINUOUS_ANGULARDISTRIBUTIONDATA

// system includes
#include <algorithm>
#include <variant>

// other includes
#include "tools/overload.hpp"
#include "ACEtk/base/Base.hpp"
#include "ACEtk/continuous/EquiprobableAngularBins.hpp"
#include "ACEtk/continuous/TabulatedAngularDistribution.hpp"
#include "ACEtk/continuous/IsotropicAngularDistribution.hpp"
#include "ACEtk/AngularDistributionType.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief Angular distribution data
 *
 *  The AngularDistributionData class contains the angular distribution data
 *  energy distributions for a set of incident energy values. It is used in
 *  the AND block.
 */
class AngularDistributionData : protected base::Base {

public:

  /* type alias */

  using Distribution = std::variant< IsotropicAngularDistribution,
                                     EquiprobableAngularBins,
                                     TabulatedAngularDistribution >;

private:

  /* fields */

  std::size_t locb_ = 1;
  base::ColumnData values_;
  std::vector< Distribution > distributions_;

  /* auxiliary functions */

  static std::vector< double >
  generateXSS( std::vector< Distribution >&& distributions, std::size_t locb ) {

    const auto ne = distributions.size();
    std::vector< double > xss( 1 + 2 * ne );

    auto incidentEnergy = [] ( const auto& value )
                             { return value.energy(); };

    std::sort( distributions.begin(), distributions.end(),
               [=] ( const auto& left, const auto& right )
                   { return std::visit( incidentEnergy, left )
                            < std::visit( incidentEnergy, right ); } );
    xss[0] = ne;
    std::size_t index = 1;
    for ( const auto& distribution : distributions ) {

      // set the energy value
      xss[index] = std::visit( incidentEnergy, distribution );

      // set the LOCC locator
      if ( std::holds_alternative< IsotropicAngularDistribution >( distribution ) ) {

        // LOCC = 0 for an isotropic distribution
        xss[index + ne] = 0;
      }
      else {

        xss[index + ne] = xss.size() + locb;
        if ( std::holds_alternative< TabulatedAngularDistribution >( distribution ) ) {

          // LOCC is negative for a tabulated distribution
          xss[index + ne] *= -1;
        }
      }

      // insert the xss array
      std::visit( tools::overload{

                    [] ( const IsotropicAngularDistribution& ) {},
                    [&xss] ( const EquiprobableAngularBins& value )
                           { xss.insert( xss.end(),
                                         value.begin(), value.end() ); },
                    [&xss] ( const TabulatedAngularDistribution& value )
                           { xss.insert( xss.end(),
                                         value.begin(), value.end() ); }
                  },
                  distribution );

      // on to the next distribution
      ++index;
    }

    return xss;
  }

  void generateBlocks() {

    this->distributions_.clear();

    std::size_t ne = static_cast< std::size_t >( this->IXSS( 1 ) );
    auto begin = this->begin();
    auto end = this->iterator( 2 * ne + 2 );

    this->values_ = base::ColumnData( this->name(), begin, end, 2 );
    for ( unsigned int index = 1; index <= this->numberIncidentEnergies(); ++index ) {

      const auto type = this->distributionType( index );
      const double incident = this->incidentEnergy( index );
      if ( type == AngularDistributionType::Isotropic ) {

        this->distributions_.emplace_back( IsotropicAngularDistribution( incident ) );
      }
      else {

        const auto locator = this->relativeDistributionLocator( index );
        const auto left = this->iterator( locator );
        auto right = this->end();
        for ( auto next = index + 1; next <= this->numberIncidentEnergies(); ++next ) {

          auto nextlocator = this->relativeDistributionLocator( next );
          if ( nextlocator > locator ) {

            right = this->iterator( nextlocator );
            break;
          }
        }
        if ( type == AngularDistributionType::Tabulated ) {

          this->distributions_.emplace_back( TabulatedAngularDistribution( incident, left, right ) );
        }
        else {

          this->distributions_.emplace_back( EquiprobableAngularBins( incident, left, right ) );
        }
      }
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

  static void verifySize( Iterator begin, Iterator end, unsigned int ne ) {

    // there are at least 1 + 2 * ne values in the angular distribution data block
    auto size = std::distance( begin, end );
    if ( size < 1 + 2 * ne ) {

      Log::error( "The size of the XSS subrange in the angular distribution data "
                  "block should be at least 1 + 2 * NE" );
      Log::info( "NE value: {}", ne );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

public:

  /* constructor */

  AngularDistributionData() = default;

  AngularDistributionData( const AngularDistributionData& base ) :
    Base( base ), locb_( base.locb_ ),
    values_( base.values_ ),
    distributions_( base.distributions_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  AngularDistributionData( AngularDistributionData&& base ) :
    Base( std::move( base ) ), locb_( base.locb_ ),
    values_( std::move( base.values_ ) ),
    distributions_( std::move( base.distributions_ ) ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  AngularDistributionData& operator=( const AngularDistributionData& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->locb_ = base.locb_;
      this->values_ = base.values_;
      this->distributions_ = base.distributions_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  AngularDistributionData& operator=( AngularDistributionData&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->locb_ = base.locb_;
      this->values_ = std::move( base.values_ );
      this->distributions_ = std::move( base.distributions_ );
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] distributions    the angular distributions for each incident energy
   *  @param[in] locb             the starting xss index with respect to the AND block
   */
  AngularDistributionData( std::vector< Distribution > distributions,
                           std::size_t locb = 1 ) :
    Base( "AngularDistributionData",
          generateXSS( std::move( distributions ), locb ) ),
    locb_( locb ) {

    this->generateBlocks();
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] locb    the starting xss index with respect to the AND block
   *  @param[in] begin   the begin iterator of the block in the XSS array
   *  @param[in] end     the end iterator of the block in the XSS array
   */
  AngularDistributionData( std::size_t locb, Iterator begin, Iterator end ) :
    Base( "AngularDistributionData", begin, end ), locb_( locb ) {

    this->generateBlocks();
    verifySize( this->begin(), this->end(), this->numberIncidentEnergies() );
  }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t NE() const { return this->values_.N(); }

  /**
   *  @brief Return the number of incident energy values
   */
  std::size_t numberIncidentEnergies() const { return this->NE(); }

  /**
   *  @brief Return the incident energy values
   */
  auto incidentEnergies() const {

    return this->values_.column( 1 );
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

    #ifndef NDEBUG
    this->verifyIncidentEnergyIndex( index );
    #endif
    return this->values_.value( 1, index );
  }

  /**
   *  @brief Return the angular distribution locator for an incident
   *         energy index
   *
   *  This locator is the value as stored in the XSS array. It is relative to
   *  the beginning of the AND block. The distribution type is determined from
   *  the sign of the locator:
   *    - when the value if negative, it is a tabulated distribution
   *    - when the value if positive, it is an equiprobable distribution
   *    - when the value if zero, it is an isotropic distribution
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int LOCC( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIncidentEnergyIndex( index );
    #endif
    return this->values_.value( 2, index );
  }

  /**
   *  @brief Return the angular distribution locator for an incident
   *         energy index
   *
   *  This locator is the value as stored in the XSS array. It is relative to
   *  the beginning of the AND block. The distribution type is determined from
   *  the sign of the locator:
   *    - when the value if negative, it is a tabulated distribution
   *    - when the value if positive, it is an equiprobable distribution
   *    - when the value if zero, it is an isotropic distribution
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int distributionLocator( std::size_t index ) const {

    return this->LOCC( index );
  }

  /**
   *  @brief Return the relative angular distribution locator for an incident
   *         energy index
   *
   *  This is the locator relative to the beginning of the current angular
   *  distribution block in the AND block. It is always positive.
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  std::size_t relativeDistributionLocator( std::size_t index ) const {

    const int locator = this->LOCC( index );
    return locator == 0 ? locator : std::abs( locator ) - this->locb_ + 1;
  }

  /**
   *  @brief Return the angular distribution type for an incident energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  AngularDistributionType distributionType( std::size_t index ) const {

    const auto locator = this->distributionLocator( index );
    return locator == 0
           ? AngularDistributionType::Isotropic
           : locator < 0 ? AngularDistributionType::Tabulated
                         : AngularDistributionType::Equiprobable;
  }

  /**
   *  @brief Return the distributions
   */
  const std::vector< Distribution >& distributions() const {

    return this->distributions_;
  }

  /**
   *  @brief Return the angular distribution data for an incident energy index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const Distribution& distribution( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIncidentEnergyIndex( index );
    #endif
    return this->distributions_[ index - 1 ];
  }

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
