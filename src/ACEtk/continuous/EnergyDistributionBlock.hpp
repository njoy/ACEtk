#ifndef NJOY_ACETK_CONTINUOUS_ENERGYDISTRIBUTIONBLOCK
#define NJOY_ACETK_CONTINUOUS_ENERGYDISTRIBUTIONBLOCK

// system includes
#include <variant>

// other includes
#include "tools/overload.hpp"
#include "ACEtk/base/Base.hpp"
#include "ACEtk/continuous/FrameAndMultiplicityBlock.hpp"
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
#include "ACEtk/continuous/MultiDistributionData.hpp"
#include "ACEtk/continuous/UndefinedDistribution.hpp"
#include "ACEtk/continuous/TabulatedMultiplicity.hpp"
#include "ACEtk/ReferenceFrame.hpp"

namespace njoy {
namespace ACEtk {
namespace continuous {

/* type alias */

using EnergyDistributionData = std::variant< EquiprobableOutgoingEnergyBinData,
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
                                             AngleEnergyDistributionData,
                                             MultiDistributionData,
                                             UndefinedDistribution >;
using MultiplicityData = std::variant< unsigned int, TabulatedMultiplicity >;

/**
 *  @class
 *  @brief The continuous energy LDLW and DLW block with the energy
 *         distribution data
 *
 *  The EnergyDistributionBlock class contains energy distribution data,
 *  one for each the first NXS(5) reaction numbers on the MTR block. The order
 *  of the distribution data sets is the same as the order of the reaction
 *  numbers in the MTR block.
 */
class EnergyDistributionBlock : protected base::Base {

  /* fields */

  unsigned int nr_ = 0; // the number of reactions
  Iterator iterator_;   // the begin iterator of the data block
  continuous::TYR tyr_;      // the associated TYR block
  std::vector< EnergyDistributionData > data_;
  std::vector< MultiplicityData > multiplicities_;
  std::vector< ReferenceFrame > frames_;

  /* auxiliary functions */

  static std::pair< std::vector< double >, std::vector< unsigned int > >
  generateXSS( std::vector< EnergyDistributionData >&& distributions,
               std::vector< MultiplicityData >&& multiplicities ) {

    if ( distributions.size() != multiplicities.size() ) {

      Log::error( "The number of distributions and multiplicities should be the same" );
      Log::info( "distributions.size(): {}", distributions.size() );
      Log::info( "multiplicities.size(): {}", multiplicities.size() );
      throw std::exception();
    }

    const auto size = distributions.size();
    std::vector< double > xss( size );
    std::vector< unsigned int > tyr;
    std::size_t index = 0;
    for ( auto&& distribution : distributions ) {

      // current value of a locator into the xss array
      std::size_t locator = xss.size() - size + 1;

      // handle multiplicity
      std::visit(

        tools::overload{

          [ &xss, &tyr, &locator, size ] ( const TabulatedMultiplicity& value ) {

            tyr.insert( tyr.end(), static_cast< double >( 100 + locator ) );
            xss.insert( xss.end(), value.begin(), value.end() );
            locator = xss.size() - size + 1;
          },
          [ &tyr ] ( const unsigned int& value ) {

            tyr.insert( tyr.end(), static_cast< double >( value ) );
          }
        },
        multiplicities[index]
      );

      // set the locator for the current distribution
      xss[index] = locator;

      // multi-law data needs no dummy probabilities
      if ( std::holds_alternative< MultiDistributionData >( distribution ) ) {

        std::visit(

          tools::overload{

            [ &xss, locator ] ( const MultiDistributionData& value ) {

              // remake the internal xss array with the proper locators
              const MultiDistributionData temp(
                        std::move( value.probabilities() ),
                        std::move( value.distributions() ),
                        locator );
              xss.insert( xss.end(), temp.begin(), temp.end() );
            },
            [] ( const auto& ) { /* nothing to do here */ }
          },
          distribution
        );
      }
      else {

        // generate the xss array for this distribution
        std::size_t idat = 0;
        std::visit(

          tools::overload{

            [] ( const MultiDistributionData& ) { /* nothing to do here */ },
            [] ( const UndefinedDistribution& ) { /* nothing to do here */ },
            [ &xss, &idat, locator ] ( const auto& value ) {

              idat = locator + 3 + 1 + 5;
              xss.push_back( 0. );                                   // LNW
              xss.push_back( static_cast< double >( value.LAW() ) ); // LAW
              xss.push_back( static_cast< double >( idat ) );        // IDAT
              xss.push_back( 0. );                                   // NR
              xss.push_back( 2. );                                   // NE
              xss.push_back( value.minimumIncidentEnergy() );        // E[0]
              xss.push_back( value.maximumIncidentEnergy() );        // E[1]
              xss.push_back( 1. );                                   // P[0]
              xss.push_back( 1. );                                   // P[1]
            }
          },
          distribution
        );
        std::visit(

          tools::overload{

            [ &xss, idat ] ( const OutgoingEnergyDistributionData& value ) {

              // remake the internal xss array with the proper locators
              decltype(auto) boundaries = value.boundaries();
              decltype(auto) interpolants = value.interpolants();
              const OutgoingEnergyDistributionData temp(
                        { boundaries.begin(), boundaries.end() },
                        { interpolants.begin(), interpolants.end() },
                        std::move( value.distributions() ),
                        idat );
              xss.insert( xss.end(), temp.begin(), temp.end() );
            },
            [ &xss, idat ] ( const KalbachMannDistributionData& value ) {

              // remake the internal xss array with the proper locators
              decltype(auto) boundaries = value.boundaries();
              decltype(auto) interpolants = value.interpolants();
              const KalbachMannDistributionData temp(
                        { boundaries.begin(), boundaries.end() },
                        { interpolants.begin(), interpolants.end() },
                        std::move( value.distributions() ),
                        idat );
              xss.insert( xss.end(), temp.begin(), temp.end() );
            },
            [ &xss, idat ] ( const EnergyAngleDistributionData& value ) {

              // remake the internal xss array with the proper locators
              decltype(auto) boundaries = value.boundaries();
              decltype(auto) interpolants = value.interpolants();
              const EnergyAngleDistributionData temp(
                        { boundaries.begin(), boundaries.end() },
                        { interpolants.begin(), interpolants.end() },
                        std::move( value.distributions() ),
                        idat );
              xss.insert( xss.end(), temp.begin(), temp.end() );
            },
            [ &xss, idat ] ( const AngleEnergyDistributionData& value ) {

              // remake the internal xss array with the proper locators
              decltype(auto) boundaries = value.boundaries();
              decltype(auto) interpolants = value.interpolants();
              const AngleEnergyDistributionData temp(
                        { boundaries.begin(), boundaries.end() },
                        { interpolants.begin(), interpolants.end() },
                        std::move( value.distributions() ),
                        idat );
              xss.insert( xss.end(), temp.begin(), temp.end() );
            },
            [] ( const UndefinedDistribution& ) { /* nothing to do here */ },
            [ &xss ] ( const auto& value ) {

              xss.insert( xss.end(), value.begin(), value.end() );
            }
          },
          distribution
        );
      }

      ++index;
    }

    return { std::move( xss ), std::move( tyr ) };
  }

  static EnergyDistributionData
  generateData( std::size_t locator, Iterator left, Iterator right ) {

    // left points to the LNW value - single law if zero
    unsigned int lnw = static_cast< unsigned int >( std::round( *left ) );
    if ( lnw == 0 ) {

      const EnergyDistributionType law = static_cast< EnergyDistributionType >( std::round( *( left + 1 ) ) );
      std::size_t idat = static_cast< std::size_t >( std::round( *( left + 2 ) ) );
      const std::size_t nr = static_cast< std::size_t >( std::round( *( left + 3 ) ) );
      const std::size_t ne = static_cast< std::size_t >( std::round( *( left + 3 + 2 * nr + 1 ) ) );
      double emin = *( left + 3 + 2 * nr + 1 + 1 );
      double emax = *( left + 3 + 2 * nr + 1 + ne );

      // compute iterators into the xss array
      const auto start = left + idat - locator;

      // switch on the law and return the appropriate data
      switch ( law ) {

        case EnergyDistributionType::DiscretePhoton : {

          return DiscretePhotonDistribution( start, right, emin, emax );
        }
        case EnergyDistributionType::LevelScattering : {

          return LevelScatteringDistribution( start, right, emin, emax );
        }
        case EnergyDistributionType::TwoBodyTransfer : {

          return TwoBodyTransferDistribution( start, right, emin, emax );
        }
        case EnergyDistributionType::NBodyPhaseSpace : {

          return NBodyPhaseSpaceDistribution( start, right, emin, emax );
        }
        case EnergyDistributionType::TabulatedEnergy : {

          return OutgoingEnergyDistributionData( idat, start, right );
        }
        case EnergyDistributionType::KalbachMann : {

          return KalbachMannDistributionData( idat, start, right );
        }
        case EnergyDistributionType::TabulatedEnergyAngle : {

          return EnergyAngleDistributionData( idat, start, right );
        }
        case EnergyDistributionType::TabulatedAngleEnergy : {

          return AngleEnergyDistributionData( idat, start, right );
        }
        case EnergyDistributionType::Equiprobable : {

          return EquiprobableOutgoingEnergyBinData( start, right );
        }
        case EnergyDistributionType::GeneralEvaporation : {

          return GeneralEvaporationSpectrum( start, right );
        }
        case EnergyDistributionType::SimpleMaxwellianFission : {

          return SimpleMaxwellianFissionSpectrum( start, right );
        }
        case EnergyDistributionType::Evaporation : {

          return EvaporationSpectrum( start, right );
        }
        case EnergyDistributionType::Watt : {

          return EnergyDependentWattSpectrum( start, right );
        }
        default : {

          throw std::runtime_error( "DLW law currently not implemented: "
                                    + std::to_string( static_cast< short >( law ) ) );
        }
      }
    }
    else {

      return MultiDistributionData( locator, left, right );
    }
  }

  void generateBlocks() {

    this->iterator_ = this->begin() + this->nr_;
    this->data_.clear();
    this->multiplicities_.clear();
    this->frames_.clear();

    for ( unsigned int index = 1; index <= this->NR(); ++index ) {

      // zero lcoators in the LDLW are not allowed
      std::size_t locator = this->LDLW( index );
      if ( locator == 0 ) {

        Log::error( "Detected a locator = 0 in the LDLW block for reaction with index "
                    "= {}", index );
        throw std::exception();
      }

      // data : one-based index to the start of the data block
      // data + locator - 1 : one-based index to the start of cross section data
      std::size_t data = std::distance( this->begin(), this->iter() ) + 1;
      std::size_t multiplicity = index == this->NR()
                                 ? 0
                                 : this->TYR().multiplicity( index + 1 );
      const auto left = this->iterator( data + locator - 1 );
      const auto right = index == this->NR()
                         ? this->end()
                         : multiplicity < 100
                             ? this->iterator( data + this->LDLW( index + 1 ) - 1 )
                             : this->iterator( data + multiplicity - 100 - 1 );
      this->data_.emplace_back( generateData( locator, left, right ) );
      multiplicity = this->TYR().multiplicity( index );
      if ( multiplicity > 100 ) {

        auto mleft = this->iterator( data + multiplicity - 100 - 1 );
        this->multiplicities_.emplace_back( TabulatedMultiplicity( mleft, left ) );
      }
      else {

        this->multiplicities_.emplace_back( static_cast< unsigned int >( multiplicity ) );
      }
    }
    this->frames_.insert( this->frames_.end(),
                          this->TYR().referenceFrames().begin(),
                          this->TYR().referenceFrames().begin() + this->NR() );
  }

  void verifyDataIndex( const std::size_t index ) const {

    if ( ( index < 1 ) || ( index > this->NR() ) ) {

      Log::error( "Illegal index argument into the {} block", this->name() );
      Log::info( "Index value: {}", index );
      Log::info( "{} accepts an index between 1 and {} inclusively",
                 this->name(), this->NR() );
      throw std::out_of_range( this->name() );
    }
  }

  void verifySize( Iterator begin, Iterator data, Iterator, unsigned int nr ) {

    // there are at least nr values in the locator block
    auto size = std::distance( begin, data );
    if ( size < nr ) {

      Log::error( "The size of the XSS subrange in the locator part of the {} "
                  "block should be at least NR", this->name() );
      Log::info( "NR value: {}", nr );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }

  /**
   *  @brief Return the iterator to the start of the sig block
   */
  Iterator iter() const { return this->iterator_; }

  /**
   *  @brief Return the associated TYR block
   *
   *  Note: this TYR block may not be completely compatible with the normal TYR
   *        block since it only contains data for the first NR reactions (instead
   *        of NTR).
   */
  const continuous::TYR& TYR() const { return this->tyr_; }

  /* constructor */

  /**
   *  @brief Private constructor
   */
  EnergyDistributionBlock( std::pair< std::vector< double >,
                                      std::vector< unsigned int > >&& xss,
                           std::vector< ReferenceFrame >&& frames,
                           std::size_t nr ) :
    Base( "DLW", std::move( xss.first ) ),
    nr_( nr ),
    tyr_( std::move( frames ), std::move( xss.second ) ) {

    this->iterator_ = this->begin() + this->nr_;
    this->generateBlocks();
  }

  /**
   *  @brief Private constructor
   */
  EnergyDistributionBlock( std::vector< EnergyDistributionData >&& distributions,
                           std::vector< MultiplicityData >&& multiplicities,
                           std::vector< ReferenceFrame >&& frames,
                           std::size_t nr ) :
    EnergyDistributionBlock( generateXSS( std::move( distributions ),
                                          std::move( multiplicities ) ),
                             std::move( frames ), nr ) {}

public:

  /* constructor */

  EnergyDistributionBlock() = default;

  EnergyDistributionBlock( const EnergyDistributionBlock& base ) :
    Base( base ), nr_( base.nr_ ), iterator_( base.iterator_ ),
    tyr_( base.tyr_ ),
    data_( base.data_ ),
    multiplicities_( base.multiplicities_ ),
    frames_( base.frames_ ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  EnergyDistributionBlock( EnergyDistributionBlock&& base ) :
    Base( std::move( base ) ), nr_( base.nr_ ), iterator_( base.iterator_ ),
    tyr_( std::move( base.tyr_ ) ),
    data_( std::move( base.data_ ) ),
    multiplicities_( std::move( base.multiplicities_ ) ),
    frames_( std::move( base.frames_ ) ) {

    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }

  EnergyDistributionBlock& operator=( const EnergyDistributionBlock& base ) {

    if ( this != &base ) {

      Base::operator=( base );
      this->nr_ = base.nr_;
      this->iterator_ = base.iterator_;
      this->tyr_ = base.tyr_;
      this->data_ = base.data_;
      this->multiplicities_ = base.multiplicities_;
      this->frames_ = base.frames_;
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  EnergyDistributionBlock& operator=( EnergyDistributionBlock&& base ) {

    if ( this != &base ) {

      Base::operator=( std::move( base ) );
      this->nr_ = base.nr_;
      this->iterator_ = base.iterator_;
      this->tyr_ = std::move( base.tyr_ );
      this->data_ = std::move( base.data_ );
      this->multiplicities_ = std::move( base.multiplicities_ );
      this->frames_ = std::move( base.frames_ );
      if ( Base::owner() ) {

        this->generateBlocks();
      }
    }
    return *this;
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] distributions     the energy distribution data
   *  @param[in] multiplicities    the multiplicity data
   *  @param[in] frames            the reference frames
   */
  EnergyDistributionBlock( std::vector< EnergyDistributionData > distributions,
                           std::vector< MultiplicityData > multiplicities,
                           std::vector< ReferenceFrame > frames ) :
    EnergyDistributionBlock( std::move( distributions ),
                             std::move( multiplicities ),
                             std::move( frames ),
                             distributions.size() ) {}

  /**
   *  @brief Constructor
   *
   *  @param[in] ldlw    the begin iterator of the LDLW block in the XSS array
   *  @param[in] dlw     the begin iterator of the DLW block in the XSS array
   *  @param[in] end     the end iterator of the DLW block in the XSS array
   *  @param[in] nr      the number of reactions
   */
  EnergyDistributionBlock( Iterator loc, Iterator data, Iterator end,
                           continuous::TYR tyr, unsigned int nr ) :
    Base( "DLW", loc, end ), nr_( nr ), iterator_( data ),
    tyr_( std::move( tyr ) ) {

    verifySize( this->begin(), this->iterator_, this->end(), this->nr_ );
    this->generateBlocks();
  }

  /* methods */

  /**
   *  @brief Return the number of reactions that produce the projectile
   *         (excluding elastic )
   */
  unsigned int NR() const { return this->nr_; }

  /**
   *  @brief Return the number of reactions that produce the projectile
   *         (excluding elastic )
   */
  unsigned int numberReactions() const { return this->NR(); }

  /**
   *  @brief Return the relative energy distribution locator for a reaction
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int LDLW( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->IXSS( index );
  }

  /**
   *  @brief Return the relative energy distribution locator for a reaction
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  int energyDistributionLocator( std::size_t index ) const {

    return this->LDLW( index );
  }

  /**
   *  @brief Return all energy distribution data
   */
  const std::vector< EnergyDistributionData >& data() const {

    return this->data_;
  }

  /**
   *  @brief Return the energy distribution data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const EnergyDistributionData& energyDistributionData( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->data_[ index - 1 ];
  }

  /**
   *  @brief Return all multiplicity data
   */
  const std::vector< MultiplicityData >& multiplicities() const {

    return this->multiplicities_;
  }

  /**
   *  @brief Return the multiplicity data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const MultiplicityData& multiplicityData( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->multiplicities_[ index - 1 ];
  }

  /**
   *  @brief Return all reference frames
   */
  const std::vector< ReferenceFrame >& referenceFrames() const {

    return this->frames_;
  }

  /**
   *  @brief Return the reference frame for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const ReferenceFrame& referenceFrame( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->frames_[ index - 1 ];
  }

  /**
   *  @brief Return the associated TYR multiplicity entries (internal only)
   */
  auto tyrMultiplicities() const {

    return this->tyr_.multiplicities();
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using DLW = EnergyDistributionBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
