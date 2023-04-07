#ifndef NJOY_ACETK_BLOCK_ENERGYDISTRIBUTIONBLOCK
#define NJOY_ACETK_BLOCK_ENERGYDISTRIBUTIONBLOCK

// system includes
#include <variant>

// other includes
#include "ACEtk/block/details/Base.hpp"
#include "ACEtk/block/EquiprobableOutgoingEnergyBinData.hpp"
#include "ACEtk/block/DiscretePhotonDistribution.hpp"
#include "ACEtk/block/LevelScatteringDistribution.hpp"
#include "ACEtk/block/OutgoingEnergyDistributionData.hpp"
#include "ACEtk/block/GeneralEvaporationSpectrum.hpp"
#include "ACEtk/block/SimpleMaxwellianFissionSpectrum.hpp"
#include "ACEtk/block/EvaporationSpectrum.hpp"
#include "ACEtk/block/EnergyDependentWattSpectrum.hpp"
#include "ACEtk/block/KalbachMannDistributionData.hpp"
#include "ACEtk/block/NBodyPhaseSpaceDistribution.hpp"
#include "ACEtk/block/MultiDistributionData.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The continuous energy LDLW and DLW block with the energy
 *         distribution data
 *
 *  The EnergyDistributionBlock class contains energy distribution data,
 *  one for each the first NXS(5) reaction numbers on the MTR block. The order
 *  of the distribution data sets is the same as the order of the reaction
 *  numbers in the MTR block.
 *
 *  @todo verify if DiscretePhotonDistribution can appear here
 */
class EnergyDistributionBlock : protected details::Base {

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
                                         MultiDistributionData >;

private:

  /* fields */
  unsigned int nr_; // number of reactions that produce the projectile (excluding elastic)
  Iterator dlw_;    // the begin iterator of the DLW block

  /* auxiliary functions */
  #include "ACEtk/block/EnergyDistributionBlock/src/generateXSS.hpp"
  #include "ACEtk/block/EnergyDistributionBlock/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/EnergyDistributionBlock/src/ctor.hpp"

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
  unsigned int numberProjectileProductionReactions() const { return this->NR(); }

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
    this->verifyReactionIndex( index, 1, this->NR() );
    #endif
    return XSS( index );
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
   *  @brief Return the energy distribution data for a reaction index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  DistributionData energyDistributionData( std::size_t index ) const {

    // dlw : one-based index to the start of the DLW block
    // dlw + locator - 1 : one-based index to the start of distribution data
    const std::size_t dlw = std::distance( this->begin(), this->dlw_ ) + 1;
    const std::size_t locator = dlw + this->LDLW( index ) - 1;

    // left points to the LNW value - single law if zero
    unsigned int lnw = static_cast< unsigned int >( this->XSS( locator ) );
    if ( lnw == 0 ) {

      EnergyDistributionType law =
          static_cast< EnergyDistributionType >( this->XSS( locator + 1 ) );
      std::size_t idat = static_cast< std::size_t >( this->XSS( locator + 2 ) );
      std::size_t nr = static_cast< std::size_t >( this->XSS( locator + 3 ) );
      std::size_t ne = static_cast< std::size_t >( this->XSS( locator + 3 + 2 * nr + 1 ) );
      double emin = this->XSS( locator + 3 + 2 * nr + 1 + 1 );
      double emax = this->XSS( locator + 3 + 2 * nr + 1 + ne );

      // compute iterators into the xss array
      const auto left = this->iterator( dlw + idat - 1 );
      const auto right = index == this->NR()
                         ? this->end()
                         : this->iterator( dlw + this->LDLW( index + 1 ) - 1 );

      // switch on the law and return the appropriate data
      switch ( law ) {

        case EnergyDistributionType::DiscretePhoton : {

          return DiscretePhotonDistribution( left, right, emin, emax );
        }
        case EnergyDistributionType::LevelScattering : {

          return LevelScatteringDistribution( left, right, emin, emax );
        }
        case EnergyDistributionType::NBodyPhaseSpace : {

          return NBodyPhaseSpaceDistribution( left, right, emin, emax );
        }
        case EnergyDistributionType::TabulatedEnergy : {

          return OutgoingEnergyDistributionData( idat, left, right );
        }
        case EnergyDistributionType::KalbachMann : {

          return KalbachMannDistributionData( idat, left, right );
        }
        case EnergyDistributionType::Equiprobable : {

          return EquiprobableOutgoingEnergyBinData( left, right );
        }
        case EnergyDistributionType::GeneralEvaporation : {

          return GeneralEvaporationSpectrum( left, right );
        }
        case EnergyDistributionType::SimpleMaxwellianFission : {

          return SimpleMaxwellianFissionSpectrum( left, right );
        }
        case EnergyDistributionType::Evaporation : {

          return EvaporationSpectrum( left, right );
        }
        case EnergyDistributionType::Watt : {

          return EnergyDependentWattSpectrum( left, right );
        }
        default : {

          throw std::runtime_error( "DLW law currently not implemented: "
                                    + std::to_string( static_cast< short >( law ) ) );
        }
      }
    }
    else {

      // this is a multi-law - currently unimplemented
      throw std::runtime_error( "DLW multi-law - currently not implemented" );
    }
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

using DLW = EnergyDistributionBlock;

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
