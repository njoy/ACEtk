#ifndef NJOY_ACETK_CONTINUOUS_MULTIDISTRIBUTIONDATA
#define NJOY_ACETK_CONTINUOUS_MULTIDISTRIBUTIONDATA

// system includes
#include <variant>

// other includes
#include "tools/overload.hpp"
#include "ACEtk/EnergyDistributionType.hpp"
#include "ACEtk/base/Base.hpp"
#include "ACEtk/continuous/EquiprobableOutgoingEnergyBinData.hpp"
#include "ACEtk/continuous/DiscretePhotonDistribution.hpp"
#include "ACEtk/continuous/LevelScatteringDistribution.hpp"
#include "ACEtk/continuous/OutgoingEnergyDistributionData.hpp"
#include "ACEtk/continuous/GeneralEvaporationSpectrum.hpp"
#include "ACEtk/continuous/SimpleMaxwellianFissionSpectrum.hpp"
#include "ACEtk/continuous/EvaporationSpectrum.hpp"
#include "ACEtk/continuous/EnergyDependentWattSpectrum.hpp"
#include "ACEtk/continuous/KalbachMannDistributionData.hpp"
#include "ACEtk/continuous/NBodyPhaseSpaceDistribution.hpp"
#include "ACEtk/continuous/TwoBodyTransferDistribution.hpp"
#include "ACEtk/continuous/EnergyAngleDistributionData.hpp"
#include "ACEtk/continuous/AngleEnergyDistributionData.hpp"
#include "ACEtk/continuous/DistributionProbability.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/**
 *  @class
 *  @brief The distribution is a combination of multiple distributions
 *
 *  The MultiDistributionData class contains a set of distributions and
 *  associated probabilities to represent the particle's distribution data.
 *  This type of distribution is rarely used, and when it happens it is often
 *  used for higher chance fission spectra. It is used in the DLW block (there
 *  is no ACE LAW associated to this distribution type, but internally in ACEtk
 *  we refer to it as ACE LAW 666 because it is evil).
 */
class MultiDistributionData : protected base::Base {

public:

  /* type alias */

  using DistributionData = std::variant< EquiprobableOutgoingEnergyBinData,
                                         DiscretePhotonDistribution,
                                         LevelScatteringDistribution,
                                         OutgoingEnergyDistributionData,
                                         GeneralEvaporationSpectrum,
                                         SimpleMaxwellianFissionSpectrum,
                                         EvaporationSpectrum,
                                         EnergyDependentWattSpectrum,
                                         KalbachMannDistributionData,
                                         NBodyPhaseSpaceDistribution,
                                         TwoBodyTransferDistribution,
                                         EnergyAngleDistributionData,
                                         AngleEnergyDistributionData >;

private:

  /* fields */

  std::size_t locb_ = 1;
  std::vector< DistributionProbability > probabilities_;
  std::vector< DistributionData > distributions_;

  /* auxiliary functions */

  void generateBlocks() {

    this->probabilities_.clear();
    this->distributions_.clear();

    std::size_t locator = 1; // this->locb_ - ( this->locb_ - 1 )
    std::size_t lnw = 0;
    do {

      // lnw, law and idat from xss array (one based index starting at locb)
      lnw = static_cast< std::size_t >( this->IXSS( locator ) );
      EnergyDistributionType law =
          static_cast< EnergyDistributionType >( this->IXSS( locator + 1 ) );
      std::size_t idat = static_cast< std::size_t >( this->IXSS( locator + 2 ) );

      // iterators into the xss array (zero based index into internal xss array)
      auto pbegin = this->begin() + locator + 3 - 1;
      auto dbegin = this->begin() + idat - ( this->locb_ - 1 ) - 1;
      auto end = lnw ? this->begin() + lnw - ( this->locb_ - 1 ) - 1 : this->end();

      // add the probabilities to the xss array
      this->probabilities_.emplace_back( pbegin, dbegin );
      double emin = this->probabilities_.back().energies().front();
      double emax = this->probabilities_.back().energies().back();

      // add the actual distribution
      switch ( law ) {

        case EnergyDistributionType::DiscretePhoton : {

          this->distributions_.emplace_back(
              DiscretePhotonDistribution( dbegin, end, emin, emax ) );
          break;
        }
        case EnergyDistributionType::LevelScattering : {

          this->distributions_.emplace_back(
              LevelScatteringDistribution( dbegin, end, emin, emax ) );
          break;
        }
        case EnergyDistributionType::NBodyPhaseSpace : {

          this->distributions_.emplace_back(
              NBodyPhaseSpaceDistribution( dbegin, end, emin, emax ) );
          break;
        }
        case EnergyDistributionType::TwoBodyTransfer : {

          this->distributions_.emplace_back(
              TwoBodyTransferDistribution( dbegin, end, emin, emax ) );
          break;
        }
        case EnergyDistributionType::TabulatedEnergy : {

          this->distributions_.emplace_back(
              OutgoingEnergyDistributionData( idat, dbegin, end ) );
          break;
        }
        case EnergyDistributionType::KalbachMann : {

          this->distributions_.emplace_back(
              KalbachMannDistributionData( idat, dbegin, end ) );
          break;
        }
        case EnergyDistributionType::TabulatedEnergyAngle : {

          this->distributions_.emplace_back(
            EnergyAngleDistributionData( idat, dbegin, end ) );
          break;
        }
        case EnergyDistributionType::TabulatedAngleEnergy : {

          this->distributions_.emplace_back(
            AngleEnergyDistributionData( idat, dbegin, end ) );
        }
        case EnergyDistributionType::Equiprobable : {

          this->distributions_.emplace_back(
              EquiprobableOutgoingEnergyBinData( dbegin, end ) );
          break;
        }
        case EnergyDistributionType::GeneralEvaporation : {

          this->distributions_.emplace_back(
              GeneralEvaporationSpectrum( dbegin, end ) );
          break;
        }
        case EnergyDistributionType::SimpleMaxwellianFission : {

          this->distributions_.emplace_back(
              SimpleMaxwellianFissionSpectrum( dbegin, end ) );
          break;
        }
        case EnergyDistributionType::Evaporation : {

          this->distributions_.emplace_back(
              EvaporationSpectrum( dbegin, end ) );
          break;
        }
        case EnergyDistributionType::Watt : {

          this->distributions_.emplace_back(
              EnergyDependentWattSpectrum( dbegin, end ) );
          break;
        }
        default : {

          throw std::runtime_error( "DLW law currently not implemented: "
                                    + std::to_string( static_cast< short >( law ) ) );
        }
      }

      locator = lnw - ( this->locb_ - 1 );
    }
    while ( lnw != 0 );
  }

  void verifyDistributionIndex( const std::size_t index ) const {

    if ( ( index < 1 ) || ( index > this->numberDistributions() ) ) {

      Log::error( "Illegal distribution index argument into {} block",
                  this->name() );
      Log::info( "Index value: {}", index );
      Log::info( "{} accepts a distribution index between 1 and {} inclusively",
                 this->name(), this->numberDistributions() );
      throw std::out_of_range( this->name() );
    }
  }

  static std::vector< double >
  generateXSS( std::vector< DistributionProbability >&& probabilities,
               std::vector< DistributionData >&& distributions,
               std::size_t locb ) {

    std::vector< double > xss;
    const auto size = probabilities.size();
    if ( distributions.size() != size ) {

      Log::error( "The number of distributions and probabilities is not the same" );
      Log::info( "Found probabilities size = {}", size );
      Log::info( "Found distributions size = {}", distributions.size() );
      throw std::exception();
    }

    // add the probability and distribution pairs to the xss array
    // set lnw and idat appropriately
    for ( unsigned int i = 0; i < size; ++i ) {

      const auto offset = xss.size();
      xss.push_back( 0 ); // lnw
      std::visit(
          [ &xss ] ( const auto& value )
                   { xss.push_back( static_cast< double >( value.LAW() ) ); },
          distributions[i] );
      xss.push_back( 1. ); // idat
      xss.insert( xss.end(), probabilities[i].begin(), probabilities[i].end() );
      xss[ offset + 2 ] = static_cast< double >( xss.size() + locb ); // idat
      std::visit(

        tools::overload{

          [ &xss, offset ] ( const OutgoingEnergyDistributionData& value ) {

            // remake the internal xss array with the proper locators
            decltype(auto) boundaries = value.boundaries();
            decltype(auto) interpolants = value.interpolants();
            const OutgoingEnergyDistributionData temp(
                      { boundaries.begin(), boundaries.end() },
                      { interpolants.begin(), interpolants.end() },
                      std::move( value.distributions() ),
                      xss[ offset + 2 ] );
            xss.insert( xss.end(), temp.begin(), temp.end() );
          },
          [ &xss, offset ] ( const KalbachMannDistributionData& value ) {

            // remake the internal xss array with the proper locators
            decltype(auto) boundaries = value.boundaries();
            decltype(auto) interpolants = value.interpolants();
            const KalbachMannDistributionData temp(
                      { boundaries.begin(), boundaries.end() },
                      { interpolants.begin(), interpolants.end() },
                      std::move( value.distributions() ),
                      xss[ offset + 2 ] );
            xss.insert( xss.end(), temp.begin(), temp.end() );
          },
          [ &xss ] ( const auto& value ) {

            xss.insert( xss.end(), value.begin(), value.end() );
          }
        },
        distributions[i]
      );
      if ( i != size - 1 ) {

        xss[ offset ] = xss.size() + locb; // lnw
      }
    }

    return xss;
  }

public:

  /* constructor */

  MultiDistributionData() = default;

  MultiDistributionData( const MultiDistributionData& base ) :
    Base( base ), locb_( base.locb_ ),
    probabilities_( base.probabilities_ ),
    distributions_( base.distributions_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  MultiDistributionData( MultiDistributionData&& base ) :
    Base( std::move( base ) ), locb_( base.locb_ ),
    probabilities_( std::move( base.probabilities_ ) ),
    distributions_( std::move( base.distributions_ ) ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  MultiDistributionData& operator=( const MultiDistributionData& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->locb_ = base.locb_;
      this->probabilities_ = base.probabilities_;
      this->distributions_ = base.distributions_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  MultiDistributionData& operator=( MultiDistributionData&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->locb_ = base.locb_;
      this->probabilities_ = std::move( base.probabilities_ );
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
   *  @param[in] probabilities    the probabilities
   *  @param[in] distributions    the distributions
   *  @param[in] locb             the starting xss index with respect to the superblock
   */
  MultiDistributionData(
      std::vector< DistributionProbability > probabilities,
      std::vector< DistributionData > distributions,
      std::size_t locb = 1 ) :
    Base( "MultiDistributionData",
          generateXSS( std::move( probabilities ), std::move( distributions ),
                       locb ) ),
    locb_( locb ) {

    this->generateBlocks();
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] locb    the starting xss index with respect to the superblock
   *  @param[in] sig     the begin iterator of the block in the XSS array
   *  @param[in] end     the end iterator of the block in the XSS array
   */
  MultiDistributionData( std::size_t locb, Iterator begin, Iterator end ) :
    Base( "MultiDistributionData", begin, end ),
    locb_( locb ) {

    this->generateBlocks();
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType LAW() {

    return EnergyDistributionType::MultiDistribution;
  }

  /**
   *  @brief Return the distribution type
   */
  static constexpr EnergyDistributionType type() {

    return EnergyDistributionType::MultiDistribution;
  }

  /**
   *  @brief Return the number of distributions
   */
  std::size_t numberDistributions() const {

    return this->distributions_.size();
  }

  /**
   *  @brief Return the probability for each distribution
   */
  const std::vector< DistributionProbability >& probabilities() const {

    return this->probabilities_;
  }

  /**
   *  @brief Return the probability data for a distribution index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const DistributionProbability& probability( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDistributionIndex( index );
    #endif
    return this->probabilities_[ index - 1 ];
  }

  /**
   *  @brief Return the distributions
   */
  const std::vector< DistributionData >& distributions() const {

    return this->distributions_;
  }

  /**
   *  @brief Return the distribution data for a distribution index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const DistributionData& distribution( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDistributionIndex( index );
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
