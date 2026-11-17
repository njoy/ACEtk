#ifndef NJOY_ACETK_CONTINUOUS_SECONDARYPARTICLEENERGYDISTRIBUTIONBLOCK
#define NJOY_ACETK_CONTINUOUS_SECONDARYPARTICLEENERGYDISTRIBUTIONBLOCK

// system includes
#include <variant>

// other includes
#include "tools/overload.hpp"
#include "ACEtk/base/BlockWithLocators.hpp"
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

/**
 *  @class
 *  @brief The continuous energy LDLWP, DLWP and LDLWH, DLWH blocks with the
 *         energy distribution data for secondary particles that are not the
 *         incident particle type
 *
 *  The SecondaryParticleAngularDistributionBlock class contains energy
 *  distribution data, one for each the NXS(6) reaction numbers on the MTRP
 *  block (for the LANDP, ANDP blocks) and each of the NTRO(ITYPE) reactions on
 *  the MTRH(ITYPE) block. The order of the distribution data sets is the same
 *  as the order of the reaction numbers in the corresponding MTR block.
 */
class SecondaryParticleEnergyDistributionBlock :
    protected base::BlockWithLocators< SecondaryParticleEnergyDistributionBlock,
                                       EnergyDistributionData > {

  friend class base::BlockWithLocators< SecondaryParticleEnergyDistributionBlock,
                                        EnergyDistributionData >;

  /* fields */

  std::optional< continuous::TYRH > tyrh_;
  std::vector< std::optional< ReferenceFrame > > frames_;

  /* auxiliary functions */

  static std::vector< double >
  generateXSS( std::vector< EnergyDistributionData >&& distributions, bool ) {

    const auto size = distributions.size();
    std::vector< double > xss( size );
    std::size_t index = 0;
    for ( auto&& distribution : distributions ) {

      // set the locator
      std::size_t offset = xss.size() - size + 1;
      xss[index] = offset;

      // multi-law data needs no dummy probabilities
      if ( std::holds_alternative< MultiDistributionData >( distribution ) ) {

        std::visit(

          tools::overload{

            [ &xss, offset ] ( const MultiDistributionData& value ) {

              // remake the internal xss array with the proper locators
              const MultiDistributionData temp(
                        std::move( value.probabilities() ),
                        std::move( value.distributions() ),
                        offset );
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
            [ &xss, &idat, offset ] ( const auto& value ) {

              idat = offset + 3 + 1 + 5;
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

    return xss;
  }

  static EnergyDistributionData
  generateData( std::size_t locator, Iterator left, Iterator right ) {

    // locators can be zero
    if ( locator == 0 ) {

      return UndefinedDistribution();
    }
    else {

      // left points to the LNW value - single law if zero
      unsigned int lnw = static_cast< unsigned int >( std::round( *left ) );
      if ( lnw == 0 ) {

        EnergyDistributionType law = static_cast< EnergyDistributionType >( std::round( *( left + 1 ) ) );
        std::size_t idat = static_cast< std::size_t >( std::round( *( left + 2 ) ) );
        std::size_t nr = static_cast< std::size_t >( std::round( *( left + 3 ) ) );
        std::size_t ne = static_cast< std::size_t >( std::round( *( left + 3 + 2 * nr + 1 ) ) );
        double emin = *( left + 3 + 2 * nr + 1 + 1 );
        double emax = *( left + 3 + 2 * nr + 1 + ne );

        // compute iterators into the xss array
        const auto start = left + ( idat - locator );

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

            throw std::runtime_error( "DLWH law currently not implemented: "
                                      + std::to_string( static_cast< short >( law ) ) );
          }
        }
      }
      else {

        return MultiDistributionData( locator, left, right );
      }
    }
  }

  void generateFrames() {

    this->frames_.clear();

    if ( this->TYRH().has_value() ) {

      this->frames_.insert( this->frames_.end(),
                            this->TYRH()->referenceFrames().begin(),
                            this->TYRH()->referenceFrames().begin() + this->NR() );
    }
    else {

      this->frames_ = { this->NR(), std::nullopt };
    }
  }

  /**
   *  @brief Return the associated TYRH block
   */
  const std::optional< continuous::TYRH >& TYRH() const { return this->tyrh_; }

public:

  /* constructor */

  SecondaryParticleEnergyDistributionBlock() = default;

  SecondaryParticleEnergyDistributionBlock(
      const SecondaryParticleEnergyDistributionBlock& base ) :
    BlockWithLocators( base ),
    tyrh_( base.tyrh_ ),
    frames_( base.frames_ ) {

    if ( Base::owner() ) {

      this->generateFrames();
    }
  }

  SecondaryParticleEnergyDistributionBlock(
      SecondaryParticleEnergyDistributionBlock&& base ) :
    BlockWithLocators( std::move( base ) ),
    tyrh_( std::move( base.tyrh_ ) ),
    frames_( std::move( base.frames_ ) ) {

    if ( Base::owner() ) {

      this->generateFrames();
    }
  }

  SecondaryParticleEnergyDistributionBlock& operator=( const SecondaryParticleEnergyDistributionBlock& base ) {

    if ( this != &base ) {

      BlockWithLocators::operator=( base );
      this->tyrh_ = base.tyrh_;
      this->frames_ = base.frames_;
      if ( Base::owner() ) {

        this->generateFrames();
      }
    }
    return *this;
  }

  SecondaryParticleEnergyDistributionBlock& operator=( SecondaryParticleEnergyDistributionBlock&& base ) {

    if ( this != &base ) {

      BlockWithLocators::operator=( std::move( base ) );
      this->tyrh_ = std::move( base.tyrh_ );
      this->frames_ = std::move( base.frames_ );
      if ( Base::owner() ) {

        this->generateFrames();
      }
    }
    return *this;
  }

  /**
   *  @brief Constructor (without reference frames for DLWH)
   *
   *  @param[in] distributions    the energy distribution data
   */
  SecondaryParticleEnergyDistributionBlock(
      std::vector< EnergyDistributionData > distributions ) :
    BlockWithLocators( "DLWH", std::move( distributions ) ), tyrh_( std::nullopt ) {

    this->generateFrames();
  }

  /**
   *  @brief Constructor (with reference frames for DLWH)
   *
   *  @param[in] distributions    the energy distribution data
   *  @param[in] frames           the reference frames
   */
  SecondaryParticleEnergyDistributionBlock(
      std::vector< EnergyDistributionData > distributions,
      std::vector< ReferenceFrame > frames ) :
    BlockWithLocators( "DLWH", std::move( distributions ) ), tyrh_( std::move( frames ) ) {

    this->generateFrames();
  }

  /**
   *  @brief Constructor (without reference frames for DLWH)
   *
   *  @param[in] ldlw    the begin iterator of the LDLW block in the XSS array
   *  @param[in] dlw     the begin iterator of the DLW block in the XSS array
   *  @param[in] end     the end iterator of the DLW block in the XSS array
   *  @param[in] nr      the number of reactions
   */
  SecondaryParticleEnergyDistributionBlock(
      Iterator lsig, Iterator sig, Iterator end, unsigned int nr ) :
    BlockWithLocators( "DLWH", lsig, sig, end, nr ), tyrh_( std::nullopt ) {

    this->generateFrames();
  }

  /**
   *  @brief Constructor (with reference frames for DLWH)
   *
   *  @param[in] ldlw    the begin iterator of the LDLW block in the XSS array
   *  @param[in] dlw     the begin iterator of the DLW block in the XSS array
   *  @param[in] end     the end iterator of the DLW block in the XSS array
   *  @param[in] tyrh    the associated DLW block
   *  @param[in] nr      the number of reactions
   */
  SecondaryParticleEnergyDistributionBlock(
      Iterator lsig, Iterator sig, Iterator end,
      continuous::TYRH tyrh, unsigned int nr ) :
    BlockWithLocators( "DLWH", lsig, sig, end, nr ), tyrh_( std::move( tyrh ) ) {

    this->generateFrames();
  }

  /* methods */

  /**
   *  @brief Return the number of reactions with energy distribution data
   */
  unsigned int NR() const { return BlockWithLocators::N(); }

  /**
   *  @brief Return the number of reactions with energy distribution data
   */
  unsigned int numberReactions() const {

    return BlockWithLocators::numberDataBlocks();
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
  int LDLW( std::size_t index ) const {

    return BlockWithLocators::LLOC( index );
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

    return BlockWithLocators::locator( index );
  }

  /**
   *  @brief Return all energy distribution data
   */
  const std::vector< EnergyDistributionData >& data() const {

    return BlockWithLocators::data();
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

    return BlockWithLocators::data( index );
  }

  /**
   *  @brief Return all reference frames
   */
  const std::vector< std::optional< ReferenceFrame > >& referenceFrames() const {

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
  const std::optional< ReferenceFrame >& referenceFrame( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyDataIndex( index );
    #endif
    return this->frames_[ index - 1 ];
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using DLWP = SecondaryParticleEnergyDistributionBlock;
using DNED = SecondaryParticleEnergyDistributionBlock;
using DLWH = SecondaryParticleEnergyDistributionBlock;

} // continuous namespace
} // ACEtk namespace
} // njoy namespace

#endif
