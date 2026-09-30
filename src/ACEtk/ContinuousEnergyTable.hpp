#ifndef NJOY_ACETK_CONTINUOUSENERGYTABLE
#define NJOY_ACETK_CONTINUOUSENERGYTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/continuous/PrincipalCrossSectionBlock.hpp"
#include "ACEtk/continuous/FissionMultiplicityBlock.hpp"
#include "ACEtk/continuous/ReactionNumberBlock.hpp"
#include "ACEtk/continuous/ReactionQValueBlock.hpp"
#include "ACEtk/continuous/FrameAndMultiplicityBlock.hpp"
#include "ACEtk/continuous/CrossSectionBlock.hpp"
#include "ACEtk/continuous/AngularDistributionBlock.hpp"
#include "ACEtk/continuous/EnergyDistributionBlock.hpp"
#include "ACEtk/continuous/PhotonProductionBlock.hpp"
#include "ACEtk/continuous/MultiplicityReactionNumberBlock.hpp"
#include "ACEtk/continuous/PhotonProductionCrossSectionBlock.hpp"
#include "ACEtk/continuous/DelayedNeutronPrecursorBlock.hpp"
#include "ACEtk/continuous/ProbabilityTableBlock.hpp"
#include "ACEtk/continuous/SecondaryParticleTypeBlock.hpp"
#include "ACEtk/continuous/SecondaryParticleInformationBlock.hpp"
#include "ACEtk/continuous/SecondaryParticleLocatorBlock.hpp"
#include "ACEtk/continuous/SecondaryParticleProductionBlock.hpp"
#include "ACEtk/continuous/SecondaryParticleProductionCrossSectionBlock.hpp"
#include "ACEtk/continuous/SecondaryParticleAngularDistributionBlock.hpp"
#include "ACEtk/continuous/SecondaryParticleEnergyDistributionBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The continuous energy ACE table
 *
 *  The ContinuousEnergyTable class represents the ACE table for continuous
 *  energy data for incident neutrons and charged particles.
 */
class ContinuousEnergyTable : protected Table {

  /* fields */

  continuous::ESZ esz_;
  std::optional< continuous::NU > nu_;
  continuous::MTR mtr_;
  continuous::LQR lqr_;
  continuous::TYR tyr_;
  continuous::SIG sig_;
  continuous::AND and_;
  continuous::DLW dlw_;

  std::optional< continuous::GPD > gpd_;
  std::optional< continuous::MTRP > mtrp_;
  std::optional< continuous::SIGP > sigp_;
  std::optional< continuous::ANDP > andp_;
  std::optional< continuous::DLWP > dlwp_;
  std::optional< continuous::YP > yp_;

  std::optional< continuous::UNR > unr_;

  std::optional< continuous::NU > dnu_;
  std::optional< continuous::BDD > bdd_;
  std::optional< continuous::DNED > dned_;

  std::optional< continuous::PTYPE > ptype_;
  std::optional< continuous::NTRO > ntro_;
  std::optional< continuous::IXS > ixs_;
  std::vector< continuous::HPD > hpd_;
  std::vector< continuous::MTRH > mtrh_;
  std::vector< continuous::TYRH > tyrh_;
  std::vector< continuous::SIGH > sigh_;
  std::vector< continuous::ANDH > andh_;
  std::vector< continuous::DLWH > dlwh_;
  std::vector< continuous::YH > yh_;

  /* auxiliary functions */

  void setSZA() {

    // check for S, Z, A in NXS(9), NXS(10) and NXS(11)
    // using MCNP rules
    if ( ( this->data().NXS(9) == 0 ) &&
         ( this->data().NXS(10) == 0 ) &&
         ( this->data().NXS(11) == 0 ) ) {

      std::string zaid = this->ZAID();
      unsigned int za = std::stoi( zaid.substr( 0, zaid.size() - 4 ) );
      unsigned int a = za % 1000;
      unsigned int z = ( za - a ) / 1000;
      unsigned int s = 0;
      if ( z > 999 ) {

        unsigned int sz = z;
        z = z % 1000;
        s = ( sz - z ) / 1000;
      }

      if ( z != 999 ) { // z = 999 is considered an unphysical z value in MCNP

        // MCNP uses this formula to approximate the value of the atomic mass
        unsigned int estimate =
        static_cast< unsigned int >( std::round((0.0064*z+2.0009)*z-0.281));

        if ( ( a > 400 ) && ( a > estimate + 40 ) ) {

          a -= 400;
          s = 1;
          while ( ( a > 100 ) && ( a > estimate + 40 ) ) {

            a -= 100;
            ++s;
          }
        }

        // exception for Am242 and Am242m1 (Am242m1 has historically been
        // associated with the 95242 zaid value)
        if ( ( z == 95 ) && ( a == 242 ) ) {

          if ( s < 2 ) {

            s = s == 0 ? 1 : 0;
          }
        }
      }

      this->data().NXS(9) = s;
      this->data().NXS(10) = z;
      this->data().NXS(11) = a;
    }
  }

  auto block( std::size_t index ) const {

    // assumption: blocks are stored in sequence!

    auto begin = this->data().XSS().begin();
    std::size_t start = this->data().JXS( index );

    std::size_t end = 0;
    if ( index != 32 ) {

      if ( start != 0 ) {

        // look for the first value that is larger than or equal to the start locator
        auto iter = std::find_if( this->data().JXS().begin() + index,
                                  this->data().JXS().end(),
                                  [start] ( auto&& value ) {

                                    return value >= static_cast< int64_t >( start );
                                  } );
        if ( iter != this->data().JXS().end() ) {

          // JXS(22) is not a locator, it points to the last value of the conventional
          // XSS array (i.e. before the secondary particle data)
          end = *iter != this->data().JXS(22) ? *iter : *iter + 1;

          // JXS(21) does not point to an actual block so set it to END + 1 instead
          if ( static_cast< int64_t >( end ) == this->data().JXS(21) ) {

            end = this->data().JXS(22) + 1;
          }
        }

        // verify if out of order blocks exist (delayed neutron data before photons)
        switch ( index ) {

          // DLW ends either at GPD or one of the blocks past JXS(22)
          case 11 : {

            iter = std::find_if( this->data().JXS().begin() + 22,
                                 this->data().JXS().end(),
                                 [start] ( auto&& value ) {

                                   return value >= static_cast< int64_t >( start );
                                 } );

            if ( iter != this->data().JXS().end() ) {

              auto next = *iter;
              if ( static_cast< int64_t >( end ) > next ) {

                end = next;
              }
            }
            break;
          }
          // DEND ends either at GPD or END
          case 27 : {

            if ( end == 0 ) {

              end = this->data().JXS(22) + 1;
            }

            auto gpd = this->data().JXS( 12 );
            if ( gpd != 0 ) {

              if ( static_cast< int64_t >( end ) > gpd ) {

                end = gpd;
              }
            }
            break;
          }
          default: break;
        }
      }
    }
    else {

      if ( this->NTYPE() != 0 ) {

        end = start + this->NTYPE() * 10 + 1;
      }
    }

    return std::make_pair(
               begin + ( start - 1 ),
               end != 0 ? begin + ( end - 1 ) : this->data().XSS().end() );
  }

  auto block( std::size_t particle, std::size_t index ) const {

    // assumption: blocks are stored in sequence!

    auto begin = this->data().XSS().begin();
    std::size_t start = this->IXS()->LLOC( particle, index );

    // look for the first value that is larger then or equal to the start locator
    std::size_t end = 0;
    auto iter = std::find_if( this->IXS()->begin() + ( particle - 1 ) * 10 + index,
                              this->IXS()->end(),
                              [start] ( auto&& value ) { return value >= start; } );
    if ( iter != this->IXS()->end() ) {

      end = *iter;
    }

    return std::make_pair(
               begin + start - 1,
               end != 0 ? begin + end - 1 : this->data().XSS().end() );
  }

  void generateBlocks() {

    // reset optional blocks
    this->nu_ = std::nullopt;
    this->gpd_ = std::nullopt;
    this->mtrp_ = std::nullopt;
    this->sigp_ = std::nullopt;
    this->andp_ = std::nullopt;
    this->dlwp_ = std::nullopt;
    this->yp_ = std::nullopt;
    this->unr_ = std::nullopt;
    this->dnu_ = std::nullopt;
    this->bdd_ = std::nullopt;
    this->dned_ = std::nullopt;
    this->ptype_ = std::nullopt;
    this->ntro_ = std::nullopt;
    this->ixs_ = std::nullopt;

    // clear vectors
    this->hpd_.clear();
    this->mtrh_.clear();
    this->tyrh_.clear();
    this->sigh_.clear();
    this->andh_.clear();
    this->dlwh_.clear();
    this->yh_.clear();

    // principal cross section block
    auto iterators = block( 1 );
    this->esz_ = continuous::ESZ( iterators.first, iterators.second, this->NES() );

    // nubar for fissile isotopes
    bool present = ( this->data().JXS(2) > 0 );
    if ( present ) {

      iterators = block( 2 );
      this->nu_ = continuous::NU( iterators.first, iterators.second );
    }

    // reaction number block
    iterators = block( 3 );
    this->mtr_ = continuous::MTR( iterators.first, iterators.second, this->NTR() );

    // Q value block
    iterators = block( 4 );
    this->lqr_ = continuous::LQR( iterators.first, iterators.second, this->NTR() );

    // reference frame and multiplicity block
    iterators = block( 5 );
    this->tyr_ = continuous::TYR( iterators.first, iterators.second, this->NTR() );

    // cross section block
    auto locators = block( 6 );
    iterators = block( 7 );
    this->sig_ = continuous::SIG( locators.first, iterators.first, iterators.second,
                                  this->NTR() );

    // angular distribution block
    locators = block( 8 );
    iterators = block( 9 );
    this->and_ = continuous::AND( locators.first, iterators.first, iterators.second,
                                  this->NR() );

    // energy distribution block
    locators = block( 10 );
    iterators = block( 11 );
    this->dlw_ = continuous::DLW( locators.first, iterators.first, iterators.second,
                                  this->TYR(), this->NR() );

    // secondary photon data
    present = ( this->NTRP() > 0 );
    if ( present ) {

      // secondary photon data: total photon production cross section
      iterators = block( 12 );
      this->gpd_ = continuous::GPD( iterators.first, iterators.second, this->NES() );

      // secondary photon data: photon production reaction numbers
      iterators = block( 13 );
      this->mtrp_ = continuous::MTRP( iterators.first, iterators.second, this->NTRP() );

      // secondary photon data: photon production cross sections
      locators = block( 14 );
      iterators = block( 15 );
      this->sigp_ = continuous::SIGP( locators.first, iterators.first, iterators.second,
                                      this->NTRP() );

      // secondary photon data: photon angular distributions
      locators = block( 16 );
      iterators = block( 17 );
      this->andp_ = continuous::ANDP( locators.first, iterators.first, iterators.second,
                                      this->NTRP() );

      // secondary photon data: photon energy distributions
      locators = block( 18 );
      iterators = block( 19 );
      this->dlwp_ = continuous::DLWP( locators.first, iterators.first, iterators.second,
                                      this->NTRP() );

      // secondary photon data: photon yield data
      iterators = block( 20 );
      this->yp_ = continuous::YP( iterators.first, iterators.second );
    }

    // unresolved resonance tables
    present = ( this->data().JXS(23) > 0 );
    if ( present ) {

      iterators = block( 23 );
      this->unr_ = continuous::UNR( iterators.first, iterators.second );
    }

    // delayed neutron data: delayed nubar for fissile isotopes
    present = ( this->data().JXS(24) > 0 );
    if ( present ) {

      iterators = block( 24 );
      this->dnu_ = continuous::NU( iterators.first, iterators.second );
    }

    // delayed neutron data
    present = ( this->NPCR() > 0 );
    if ( present ) {

      // delayed neutron data: precursor data
      iterators = block( 25 );
      this->bdd_ = continuous::BDD( iterators.first, iterators.second, this->NPCR() );

      // delayed neutron data: spectra
      locators = block( 26 );
      iterators = block( 27 );
      this->dned_ = continuous::DNED( locators.first, iterators.first, iterators.second,
                                      this->NPCR() );
    }

    // secondary particle data
    present = ( this->NTYPE() > 0 );
    if ( present ) {

      // secondary particle data: available particle types
      iterators = block( 30 );
      this->ptype_ = continuous::PTYPE( iterators.first, iterators.second, this->NTYPE() );

      // secondary particle data: number of reactions per type
      iterators = block( 31 );
      this->ntro_ = continuous::NTRO( iterators.first, iterators.second, this->NTYPE() );

      // secondary particle data: number of reactions per type
      iterators = block( 32 );
      this->ixs_ = continuous::IXS( iterators.first, iterators.second, this->NTYPE() );

      // secondary particle data: data blocks
      for ( std::size_t index = 1; index <= this->NTYPE(); ++index ) {

        // secondary particle data: total production cross section
        iterators = block( index, 1 );
        this->hpd_.emplace_back( iterators.first, iterators.second );

        // secondary particle data: reaction numbers
        iterators = block( index, 2 );
        this->mtrh_.emplace_back( iterators.first, iterators.second,
                                  this->NTRO()->NP( index ) );

        // secondary particle data: reference frame and multiplicity
        iterators = block( index, 3 );
        this->tyrh_.emplace_back( iterators.first, iterators.second,
                                  this->NTRO()->NP( index ) );

        // secondary particle data: production cross section data
        locators = block( index, 4 );
        iterators = block( index, 5 );
        this->sigh_.emplace_back( locators.first, iterators.first, iterators.second,
                                  this->NTRO()->NP( index ) );

        // secondary particle data: angular distributions
        locators = block( index, 6 );
        iterators = block( index, 7 );
        this->andh_.emplace_back( locators.first, iterators.first, iterators.second,
                                  this->NTRO()->NP( index ) );

        // secondary particle data: energy distributions
        locators = block( index, 8 );
        iterators = block( index, 9 );
        this->dlwh_.emplace_back( locators.first, iterators.first, iterators.second,
                                  this->TYRH( index ), this->NTRO()->NP( index ) );

        // secondary particle data: multiplicity reaction numbers
        iterators = block( index, 10 );
        this->yh_.emplace_back( iterators.first, iterators.second );
      }
    }
  }

  static continuous::TYR generateTYR( const continuous::DLW& dlw, std::size_t ntr ) {

    auto entries = dlw.tyrMultiplicities();
    std::vector< ReferenceFrame > frames = dlw.referenceFrames();
    std::vector< unsigned int > multiplicities( entries.begin(),
                                                entries.begin() + dlw.NR() );
    for ( unsigned int i = dlw.NR(); i < ntr; ++i ) {

      frames.push_back( ReferenceFrame::Laboratory );
      multiplicities.push_back( 0 );
    }
    return { std::move( frames ), std::move( multiplicities ) };
  }

  static std::optional< std::vector< continuous::TYRH > >
  generateTYRH( const std::optional< std::vector< continuous::DLWH > >& dlwh ) {

    std::optional< std::vector< continuous::TYRH > > tyrh = std::nullopt;
    if ( dlwh.has_value() ) {

      tyrh = std::vector< continuous::TYRH >{};
      for ( const auto& element : dlwh.value() ) {

        std::vector< ReferenceFrame > frames;
        std::transform( element.referenceFrames().begin(),
                        element.referenceFrames().end(),
                        std::back_inserter( frames ),
                        [] ( auto&& optional ) -> ReferenceFrame
                           { return optional.value(); } );
        tyrh->emplace_back( frames );
      }
    }
    return tyrh;
  }

  Data generateData( unsigned int z, unsigned int a, unsigned int s,
                     continuous::ESZ&& esz, std::optional< continuous::NU >&& nu,
                     continuous::MTR&& mtr, continuous::LQR&& lqr,
                     continuous::SIG&& sig, continuous::AND&& ang,
                     continuous::DLW&& dlw,
                     std::optional< continuous::GPD >&& gpd,
                     std::optional< continuous::MTRP >&& mtrp,
                     std::optional< continuous::SIGP >&& sigp,
                     std::optional< continuous::ANDP >&& andp,
                     std::optional< continuous::DLWP >&& dlwp,
                     std::optional< continuous::YP >&& yp,
                     std::optional< continuous::UNR >&& unr,
                     std::optional< continuous::DNU >&& dnu,
                     std::optional< continuous::BDD >&& bdd,
                     std::optional< continuous::DNED >&& dned,
                     std::optional< continuous::PTYPE >&& ptype,
                     std::optional< std::vector< continuous::HPD > >&& hpd,
                     std::optional< std::vector< continuous::MTRH > >&& mtrh,
                     std::optional< std::vector< continuous::SIGH > >&& sigh,
                     std::optional< std::vector< continuous::ANDH > >&& andh,
                     std::optional< std::vector< continuous::DLWH > >&& dlwh,
                     std::optional< std::vector< continuous::YH > >&& yh ) {

    std::array< int32_t, 16 > iz;
    std::array< double, 16 > aw;
    std::array< int64_t, 16 > nxs;
    std::array< int64_t, 32 > jxs;
    iz.fill( 0 );
    aw.fill( 0. );
    nxs.fill( 0 );
    jxs.fill( 0 );
    std::vector< double > xss;

    // some size values
    unsigned int ntr = mtr.NTR();
    unsigned int nr = ang.NR();
    unsigned int ntrp = mtrp ? mtrp->NTR() : 0;
    unsigned int ntype = ptype ? ptype->NTYPE() : 0;
    unsigned int npcr = bdd ? bdd->NPCR() : 0;

    // generate blocks we don't have yet
    continuous::TYR tyr = generateTYR( dlw, ntr );
    std::optional< std::vector< continuous::TYRH > > tyrh = generateTYRH( dlwh );

    // verify some stuff:
    //  - MTR, LQR, TYR and SIG have the same NTR
    //  - AND and DLW have the same NR
    //  - when fission is present, the NU block should be defined
    //  - when one of the photon production blocks is defined, all of them should be
    //  - ANDP and DLWP have the same NTRP
    //  - when delayed nubar is defined, it can only be tabulated
    //  - when one of the delayed neutron blocks is defined, all of them should be
    //  - BDD and DNED have the same NPCR
    //  - when one of the secondary particle blocks is defined, all of them should be
    //  - the number of secondary particle production blocks is correct
    if ( ( ntr != lqr.NTR() ) || ( ntr != tyr.NTR() ) ||
         ( ntr != sig.NTR() ) ) {

      Log::error( "Inconsistent NTR between the different blocks" );
      Log::info( "MTR NTR value = {}", mtr.NTR() );
      Log::info( "LQR NTR value = {}", lqr.NTR() );
      Log::info( "TYR NTR value = {}", tyr.NTR() );
      Log::info( "SIG NTR value = {}", sig.NTR() );
      throw std::exception();
    }
    if ( ( nr != ang.NR() ) || ( nr != dlw.NR() ) ) {

      Log::error( "Inconsistent NR between the different blocks" );
      Log::info( "AND NTR value = {}", ang.NR() );
      Log::info( "DLW NTR value = {}", dlw.NR() );
      throw std::exception();
    }
    if ( mtr.hasReactionNumber( 18 ) && !nu ) {

      Log::error( "The fission reaction is defined but the fission multiplicity "
                  "block is missing" );
      throw std::exception();
    }
    if ( ( gpd || mtrp || sigp || andp || dlwp || yp ) &&
         !( gpd && mtrp && sigp && andp && dlwp && yp ) ) {

      Log::error( "Not all photon production blocks are defined" );
      Log::info( gpd ? "GPD is defined" : "GPD is not defined" );
      Log::info( mtrp ? "MTRP is defined" : "MTRP is not defined" );
      Log::info( sigp ? "SIGP is defined" : "SIGP is not defined" );
      Log::info( andp ? "ANDP is defined" : "ANDP is not defined" );
      Log::info( dlwp ? "DLWP is defined" : "DLWP is not defined" );
      Log::info( yp ? "YP is defined" : "YP is not defined" );
      throw std::exception();
    }
    if ( gpd.has_value() ) {

      if ( ( ntrp != andp->NR() ) || ( ntrp != dlwp->NR() ) ) {

        Log::error( "Inconsistent NTRP between the different blocks" );
        Log::info( "ANDP NTRP value = {}", andp->NR() );
        Log::info( "DLWP NTRP value = {}", dlwp->NR() );
        throw std::exception();
      }
    }
    if ( dnu.has_value() ) {

      if ( dnu->hasPromptAndTotalFissionMultiplicity() ) {

        Log::error( "The delayed fission neutron multiplicity block has two "
                    "sets of multiplicity data which is not allowed" );
        throw std::exception();
      }
      unsigned int lnu = std::visit( [] ( const auto& nu ) { return nu.LNU(); },
                                     dnu->multiplicity() );
      if ( lnu != 2 ) {

        Log::error( "The delayed fission neutron multiplicity data is not given "
                    "as tabulated data" );
        Log::info( "Expected LNU = 2" );
        Log::info( "Found LNU = {}", lnu );
        throw std::exception();
      }
    }
    if ( ( dnu || bdd || dned ) && !( dnu && bdd && dned ) ) {

      Log::error( "Not all delayed neutron blocks are defined" );
      Log::info( dnu ? "DNU is defined" : "DNU is not defined" );
      Log::info( bdd ? "BDD is defined" : "BDD is not defined" );
      Log::info( dned ? "DNED is defined" : "DNED is not defined" );
      throw std::exception();
    }
    if ( bdd.has_value() ) {

      if ( ( npcr != bdd->NPCR() ) || ( npcr != dned->NR() ) ) {

        Log::error( "Inconsistent NPCR between the different blocks" );
        Log::info( "BDD NPCR value = {}", bdd->NPCR() );
        Log::info( "DNED NPCR value = {}", dned->NR() );
        throw std::exception();
      }
    }
    if ( ( ptype || hpd || mtrh || tyrh || sigh || andh || dlwh || yh ) &&
         !( ptype && hpd && mtrh && tyrh && sigh && andh && dlwh && yh ) ) {

      Log::error( "Not all secondary particle production blocks are defined" );
      Log::info( ptype ? "PTYPE is defined" : "PTYPE is not defined" );
      Log::info( hpd ? "HPD is defined" : "HPD is not defined" );
      Log::info( mtrh ? "MTRH is defined" : "MTRH is not defined" );
      Log::info( tyrh ? "TYRH is defined" : "TYRH is not defined" );
      Log::info( sigh ? "SIGH is defined" : "SIGH is not defined" );
      Log::info( andh ? "ANDH is defined" : "ANDH is not defined" );
      Log::info( dlwh ? "DLWH is defined" : "DLWH is not defined" );
      Log::info( dlwh ? "YH is defined" : "YH is not defined" );
      throw std::exception();
    }
    if ( ptype.has_value() ) {

      if ( ( ntype != hpd->size() ) || ( ntype != mtrh->size() ) ||
           ( ntype != tyrh->size() ) || ( ntype != sigh->size() ) ||
           ( ntype != andh->size() ) || ( ntype != dlwh->size() ) ||
           ( ntype != yh->size() ) ) {

        Log::error( "Inconsistent size between the different secondary "
                    "particle production blocks" );
        Log::info( "PTYPE NTRP value = {}", ntype );
        Log::info( "Number HPD blocks = {}", hpd->size() );
        Log::info( "Number MTRH blocks = {}", mtrh->size() );
        Log::info( "Number TYRH blocks = {}", tyrh->size() );
        Log::info( "Number SIGH blocks = {}", sigh->size() );
        Log::info( "Number ANDH blocks = {}", andh->size() );
        Log::info( "Number DLWH blocks = {}", dlwh->size() );
        Log::info( "Number YH blocks = {}", yh->size() );
        throw std::exception();
      }
    }

    // generate the xss array and set the locators in the jxs array as we go
    jxs[0] = 1;
    xss.insert( xss.end(), esz.begin(), esz.end() );
    if ( nu.has_value() ) {

      jxs[1] = xss.size() + 1;
      xss.insert( xss.end(), nu->begin(), nu->end() );
    }
    jxs[2] = xss.size() + 1;
    xss.insert( xss.end(), mtr.begin(), mtr.end() );
    jxs[3] = xss.size() + 1;
    xss.insert( xss.end(), lqr.begin(), lqr.end() );
    jxs[4] = xss.size() + 1;
    xss.insert( xss.end(), tyr.begin(), tyr.end() );
    jxs[5] = xss.size() + 1;
    jxs[6] = xss.size() + ntr + 1;
    xss.insert( xss.end(), sig.begin(), sig.end() );
    jxs[7] = xss.size() + 1;
    jxs[8] = xss.size() + ( nr + 1 ) + 1;
    xss.insert( xss.end(), ang.begin(), ang.end() );
    jxs[9] = xss.size() + 1;
    jxs[10] = xss.size() + nr + 1;
    xss.insert( xss.end(), dlw.begin(), dlw.end() );
    if ( unr ) {

      jxs[22] = xss.size() + 1;
      xss.insert( xss.end(), unr->begin(), unr->end() );
    }
    if ( dnu.has_value() ) {

      jxs[23] = xss.size() + 1;
      xss.insert( xss.end(), dnu->begin(), dnu->end() );
      jxs[24] = xss.size() + 1;
      xss.insert( xss.end(), bdd->begin(), bdd->end() );
      jxs[25] = xss.size() + 1;
      jxs[26] = xss.size() + npcr + 1;
      xss.insert( xss.end(), dned->begin(), dned->end() );
    }
    if ( gpd.has_value() ) {

      jxs[11] = xss.size() + 1;
      xss.insert( xss.end(), gpd->begin(), gpd->end() );
      jxs[12] = xss.size() + 1;
      xss.insert( xss.end(), mtrp->begin(), mtrp->end() );
      jxs[13] = xss.size() + 1;
      jxs[14] = xss.size() + ntrp + 1;
      xss.insert( xss.end(), sigp->begin(), sigp->end() );
      jxs[15] = xss.size() + 1;
      jxs[16] = xss.size() + ntrp + 1;
      xss.insert( xss.end(), andp->begin(), andp->end() );
      jxs[17] = xss.size() + 1;
      jxs[18] = xss.size() + ntrp + 1;
      xss.insert( xss.end(), dlwp->begin(), dlwp->end() );
      jxs[19] = xss.size() + 1;
      xss.insert( xss.end(), yp->begin(), yp->end() );
    }
    if ( mtr.hasReactionNumber( 18 ) ) {

      jxs[20] = jxs[6] + sig.crossSectionLocator( mtr.index( 18 ) ) - 1;
    }
    jxs[21] = xss.size();
    if ( ptype.has_value() ) {

      std::vector< unsigned int > numbers;
      for ( const auto& element : mtrh.value() ) {

        numbers.push_back( element.NTR() );
      }
      continuous::NTRO ntro( std::move( numbers ) );

      jxs[29] = xss.size() + 1;
      xss.insert( xss.end(), ptype->begin(), ptype->end() );
      jxs[30] = xss.size() + 1;
      xss.insert( xss.end(), ntro.begin(), ntro.end() );
      jxs[31] = xss.size() + 1;

      auto size = ntype * 10;
      auto ixs_position = xss.size();
      std::vector< std::array< unsigned int, 10 > > ixs( ntype );

      for ( std::size_t index = 0; index < ntype; ++index ) {

        auto number = mtrh.value()[index].NTR();

        ixs[index][0] = xss.size() + size + 1;
        xss.insert( xss.end(), hpd.value()[index].begin(), hpd.value()[index].end() );
        ixs[index][1] = xss.size() + size + 1;
        xss.insert( xss.end(), mtrh.value()[index].begin(), mtrh.value()[index].end() );
        ixs[index][2] = xss.size() + size + 1;
        xss.insert( xss.end(), tyrh.value()[index].begin(), tyrh.value()[index].end() );
        ixs[index][3] = xss.size() + size + 1;
        ixs[index][4] = xss.size() + size + number + 1;
        xss.insert( xss.end(), sigh.value()[index].begin(), sigh.value()[index].end() );
        ixs[index][5] = xss.size() + size + 1;
        ixs[index][6] = xss.size() + size + number + 1;
        xss.insert( xss.end(), andh.value()[index].begin(), andh.value()[index].end() );
        ixs[index][7] = xss.size() + size + 1;
        ixs[index][8] = xss.size() + size + number + 1;
        xss.insert( xss.end(), dlwh.value()[index].begin(), dlwh.value()[index].end() );
        ixs[index][9] = xss.size() + size + 1;
        xss.insert( xss.end(), yh.value()[index].begin(), yh.value()[index].end() );
      }

      continuous::IXS locators( std::move( ixs ) );
      xss.insert( xss.begin() + ixs_position, locators.begin(), locators.end() );
    }

    // set the nxs values for the continuous energy table
    // NXS(1) = length
    // NXS(2) = za
    // NXS(3) = NES (number energies)
    // NXS(4) = NTR (total number of reactions)
    // NXS(5) = NR (number of reactions with angular and energy distribution data,
    //              excluding elastic)
    // NXS(6) = NTRP (number of photon production reactions)
    // NXS(7) = NTYPE (number of secondary particle types)
    // NXS(8) = NPCR (number of delayed precursor groups)
    // NXS(9) = s (isomeric state)
    // NXS(10) = z (atom number)
    // NXS(11) = a (mass number)
    nxs[0] = xss.size();
    nxs[1] = z * 1000 + a;
    nxs[2] = esz.energies().size();
    nxs[3] = ntr;
    nxs[4] = nr;
    nxs[5] = ntrp;
    nxs[6] = ntype;
    nxs[7] = npcr;
    nxs[8] = s;
    nxs[9] = z;
    nxs[10] = a;

    return { std::move( iz ), std::move( aw ),
             std::move( nxs ), std::move( jxs ), std::move( xss ) };
  }

  void verifyType() {

    char type = this->ZAID().back();
    if ( ( type != 'c' ) && ( type != 'h' ) && ( type != 'o' ) &&
         ( type != 'r' ) && ( type != 's' ) && ( type != 'a' ) ) {

      Log::error( "The ZAID given in the ACE table ({}) does not appear to be a "
                  "continuous energy type (c, h, o, r, s, a)", this->ZAID() );
      throw std::exception();
    }
  }

public:

  /**
   *  @brief Copy constructor using a generic table
   *
   *  @param[in] table    the generic table to be copied
   */
  ContinuousEnergyTable( const Table& table ): Table( table ) {

    this->verifyType();
    this->setSZA();
    this->generateBlocks();
  }

  /**
   *  @brief Move constructor using a generic table
   *
   *  @param[in] table    the generic table to be moved
   */
  ContinuousEnergyTable( Table&& table ): Table( std::move( table ) ) {

    this->verifyType();
    this->setSZA();
    this->generateBlocks();
  }

  /**
   *  @brief Copy constructor using a continuous energy table
   *
   *  @param[in] table    the continuous energy table to be copied
   */
  ContinuousEnergyTable( const ContinuousEnergyTable& table ) :
    Table( table ) {

    this->verifyType();
    this->setSZA();
    this->generateBlocks();
  }

  /**
   *  @brief Move constructor using a continuous energy table
   *
   *  @param[in] table    the continuous energy table to be moved
   */
  ContinuousEnergyTable( ContinuousEnergyTable&& table ) :
    Table( std::move( table ) ) {

    this->verifyType();
    this->setSZA();
    this->generateBlocks();
  }

  /**
   *  @brief Copy assignment using a continuous energy table
   *
   *  @param[in] table    the continuous energy table to be copied
   */
  ContinuousEnergyTable& operator=( const ContinuousEnergyTable& base ) {

    if ( this != &base ) {

      Table::operator=( base );
      this->verifyType();
      this->setSZA();
      this->generateBlocks();
    }
    return *this;
  }

  /**
   *  @brief Move assignment using a continuous energy table
   *
   *  @param[in] table    the continuous energy table to be moved
   */
  ContinuousEnergyTable& operator=( ContinuousEnergyTable&& base ) {

    if ( this != &base ) {

      Table::operator=( std::move( base ) );
      this->verifyType();
      this->setSZA();
      this->generateBlocks();
    }
    return *this;
  }

  /**
   *  @brief Constructor (from scratch)
   *
   *  @param[in] z         the Z number of the target
   *  @param[in] a         the A number of the target
   *  @param[in] s         the S number of the target
   *  @param[in] header    the header for the table
   *  @param[in] esz       the principal cross section block
   *  @param[in] nu        the optional fission neutron multiplicity block
   *  @param[in] dnu       the optional delayed fission neutron multiplicity block
   *  @param[in] mtr       the reaction number block
   *  @param[in] lqr       the reaction Q value block
   *  @param[in] sig       the cross section data block
   *  @param[in] ang       the angular distribution data block
   *  @param[in] dlw       the energy distribution data block
   *  @param[in] bdd       the delayed fission neutron precursor data block
   *  @param[in] dned      the delayed fission neutron energy distribution data block
   *  @param[in] gpd       the photon production block
   *  @param[in] mtrp      the photon production reaction number block
   *  @param[in] sigp      the photon production cross section data block
   *  @param[in] angp      the photon production angular distribution data block
   *  @param[in] dlwp      the photon production energy distribution data block
   *  @param[in] yp        the photon multiplicity reaction number block
   *  @param[in] unr       the unresolved resonance probability table block
   *  @param[in] ptype     the secondary particle type block
   *  @param[in] hpd       the secondary particle production blocks
   *  @param[in] mtrh      the secondary particle production reaction number blocks
   *  @param[in] sigh      the secondary particle production cross section data blocks
   *  @param[in] andh      the secondary particle angular distribution data blocks
   *  @param[in] dlwh      the secondary particle energy distribution data blocks
   *  @param[in] yh        the secondary particle multiplicity reaction number blocks
   */
  ContinuousEnergyTable( unsigned int z, unsigned int a, unsigned int s,
                         HeaderVariant header,
                         continuous::ESZ esz, std::optional< continuous::NU > nu,
                         std::optional< continuous::DNU > dnu,
                         continuous::MTR mtr, continuous::LQR lqr,
                         continuous::SIG sig, continuous::AND ang,
                         continuous::DLW dlw,
                         std::optional< continuous::BDD > bdd,
                         std::optional< continuous::DNED > dned,
                         std::optional< continuous::GPD > gpd,
                         std::optional< continuous::MTRP > mtrp,
                         std::optional< continuous::SIGP > sigp,
                         std::optional< continuous::ANDP > andp,
                         std::optional< continuous::DLWP > dlwp,
                         std::optional< continuous::YP > yp,
                         std::optional< continuous::UNR > unr,
                         std::optional< continuous::PTYPE > ptype,
                         std::optional< std::vector< continuous::HPD > > hpd,
                         std::optional< std::vector< continuous::MTRH > > mtrh,
                         std::optional< std::vector< continuous::SIGH > > sigh,
                         std::optional< std::vector< continuous::ANDH > > andh,
                         std::optional< std::vector< continuous::DLWH > > dlwh,
                         std::optional< std::vector< continuous::YH > > yh ) :
    ContinuousEnergyTable(
        Table( std::move( header ),
               generateData( z, a, s, std::move( esz ), std::move( nu ),
                             std::move( mtr ), std::move( lqr ),
                             std::move( sig ),
                             std::move( ang ), std::move( dlw ),
                             std::move( gpd ), std::move( mtrp ),
                             std::move( sigp ), std::move( andp ),
                             std::move( dlwp ), std::move( yp ),
                             std::move( unr ), std::move( dnu ),
                             std::move( bdd ), std::move( dned ),
                             std::move( ptype ), std::move( hpd ),
                             std::move( mtrh ),
                             std::move( sigh ), std::move( andh ),
                             std::move( dlwh ), std::move( yh ) ) ) ) {}

  using Table::header;
  using Table::data;
  using Table::print;

  //! @todo projectile() function
  //! @todo target() function

  /**
   *  @brief Return the full ZAID or SZAID of the table
   */
  const std::string& ZAID() const {

    return std::visit( [] ( const auto& header ) -> decltype(auto)
                          { return header.ZAID(); },
                       this->header() );
  }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double AWR() const {

    return std::visit( [] ( const auto& header ) -> decltype(auto)
                          { return header.AWR(); },
                       this->header() );
  }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double atomicWeightRatio() const { return this->AWR(); }

  /**
   *  @brief Return the temperature of the table
   */
  double TEMP() const {

    return std::visit( [] ( const auto& header ) -> decltype(auto)
                          { return header.TEMP(); },
                       this->header() );
  }

  /**
   *  @brief Return the temperature of the table
   */
  double temperature() const { return this->TEMP(); }

  /**
   *  @brief Return the date
   */
  const std::string& date() const {

    return std::visit( [] ( const auto& header ) -> decltype(auto)
                          { return header.date(); },
                       this->header() );
  }

  // NXS information

  /**
   *  @brief Return the total length of the XSS array
   */
  unsigned int length() const { return this->data().NXS(1); }

  /**
   *  @brief Return the ZA of the target
   */
  unsigned int ZA() const { return this->data().NXS(2); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NES() const { return this->data().NXS(3); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NES(); }

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int NTR() const { return this->data().NXS(4); }

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int numberReactions() const { return this->NTR(); }

  /**
   *  @brief Return the total number of available reactions (including elastic)
   */
  unsigned int totalNumberReactions() const { return this->NTR() + 1; }

  /**
   *  @brief Return the number of reactions that produce the projectile
   *         (excluding elastic )
   */
  unsigned int NR() const { return this->data().NXS(5); }

  /**
   *  @brief Return the number of reactions that produce the projectile
   *         (excluding elastic )
   */
  unsigned int numberProjectileProductionReactions() const { return this->NR(); }

  /**
   *  @brief Return the number of reactions that produce photons
   */
  unsigned int NTRP() const { return this->data().NXS(6); }

  /**
   *  @brief Return the number of reactions that produce photons
   */
  unsigned int numberPhotonProductionReactions() const { return this->NTRP(); }

  /**
   *  @brief Return the number of secondary particle types (excluding the
   *         projectile and photons)
   */
  unsigned int NTYPE() const { return this->data().NXS(7); }

  /**
   *  @brief Return the number of secondary particle types (excluding the
   *         projectile and photons)
   */
  unsigned int numberSecondaryParticleTypes() const { return this->NTYPE(); }

  /**
   *  @brief Return the number of delayed percursor families
   */
  unsigned int NPCR() const { return this->data().NXS(8); }

  /**
   *  @brief Return the number of delayed percursor families
   */
  unsigned int numberDelayedPrecursors() const { return this->NPCR(); }

  /**
   *  @brief Return the isomeric state of the target
   */
  unsigned int S() const { return this->data().NXS(9); }

  /**
   *  @brief Return the isomeric state of the target
   */
  unsigned int isomericState() const { return this->S(); }

  /**
   *  @brief Return the atom number of the target
   */
  unsigned int Z() const { return this->data().NXS(10); }

  /**
   *  @brief Return the atom number of the target
   */
  unsigned int atomNumber() const { return this->Z(); }

  /**
   *  @brief Return the mass number of the target
   */
  unsigned int A() const { return this->data().NXS(11); }

  /**
   *  @brief Return the mass number of the target
   */
  unsigned int massNumber() const { return this->A(); }

  // JXS information

  // XSS blocks

  /**
   *  @brief Return the principal cross section block
   */
  const continuous::ESZ& ESZ() const { return this->esz_; }

  /**
   *  @brief Return the principal cross section block
   */
  const continuous::ESZ& principalCrossSectionBlock() const { return this->ESZ(); }

  /**
   *  @brief Return the fission multiplicity block
   */
  const std::optional< continuous::NU >& NU() const { return this->nu_; }

  /**
   *  @brief Return the fission multiplicity block
   */
  const std::optional< continuous::NU >& fissionMultiplicityBlock() const {

    return this->NU();
  }

  /**
   *  @brief Return the reaction number block
   */
  const continuous::MTR& MTR() const { return this->mtr_; }

  /**
   *  @brief Return the reaction number block
   */
  const continuous::MTR& reactionNumberBlock() const { return this->MTR(); }

  /**
   *  @brief Return the reaction Q value block
   */
  const continuous::LQR& LQR() const { return this->lqr_; }

  /**
   *  @brief Return the reaction Q value block
   */
  const continuous::LQR& reactionQValueBlock() const { return this->LQR(); }

  /**
   *  @brief Return the reference frame and multiplicity block
   */
  const continuous::TYR& TYR() const { return this->tyr_; }

  /**
   *  @brief Return the reference frame and multiplicity block
   */
  const continuous::TYR& frameAndMultiplicityBlock() const { return this->TYR(); }

  /**
   *  @brief Return the cross section block
   */
  const continuous::SIG& SIG() const { return this->sig_; }

  /**
   *  @brief Return the cross section block
   */
  const continuous::SIG& crossSectionBlock() const { return this->SIG(); }

  /**
   *  @brief Return the angular distribution block
   */
  const continuous::AND& AND() const { return this->and_; }

  /**
   *  @brief Return the angular distribution block
   */
  const continuous::AND& angularDistributionBlock() const { return this->AND(); }

  /**
   *  @brief Return the energy distribution block
   */
  const continuous::DLW& DLW() const { return this->dlw_; }

  /**
   *  @brief Return the energy distribution block
   */
  const continuous::DLW& energyDistributionBlock() const { return this->DLW(); }

  /**
   *  @brief Return the photon production block
   */
  const std::optional< continuous::GPD >& GPD() const { return this->gpd_; }

  /**
   *  @brief Return the photon production block
   */
  const std::optional< continuous::GPD >& photonProductionBlock() const {

    return this->GPD();
  }

  /**
   *  @brief Return the photon production reaction number block
   */
  const std::optional< continuous::MTR >& MTRP() const { return this->mtrp_; }

  /**
   *  @brief Return the photon production reaction number block
   */
  const std::optional< continuous::MTR >& photonProductionReactionNumberBlock() const {

    return this->MTRP();
  }

  /**
   *  @brief Return the photon production cross section block
   */
  const std::optional< continuous::SIGP >& SIGP() const { return this->sigp_; }

  /**
   *  @brief Return the photon production cross section block
   */
  const std::optional< continuous::SIGP >& photonProductionCrossSectionBlock() const {

    return this->SIGP();
  }

  /**
   *  @brief Return the photon production angular distribution block
   */
  const std::optional< continuous::ANDP >& ANDP() const { return this->andp_; }

  /**
   *  @brief Return the photon production angular distribution block
   */
  const std::optional< continuous::ANDP >& photonProductionAngularDistributionBlock() const {

    return this->ANDP();
  }

  /**
   *  @brief Return the photon production energy distribution block
   */
  const std::optional< continuous::DLWP >& DLWP() const { return this->dlwp_; }

  /**
   *  @brief Return the photon production energy distribution block
   */
  const std::optional< continuous::DLWP >& photonProductionEnergyDistributionBlock() const {

    return this->DLWP();
  }

  /**
   *  @brief Return the photon multiplicity reaction number block
   */
  const std::optional< continuous::YP >& YP() const { return this->yp_; }

  /**
   *  @brief Return the photon multiplicity reaction number block
   */
  const std::optional< continuous::YP >& photonMultiplicityReactionNumberBlock() const {

    return this->YP();
  }

  /**
   *  @brief Return the unresoved probability table block
   */
  const std::optional< continuous::UNR >& UNR() const { return this->unr_; }

  /**
   *  @brief Return the unresoved probability table block
   */
  const std::optional< continuous::UNR >& probabilityTableBlock() const {

    return this->UNR();
  }

  /**
   *  @brief Return the delayed fission multiplicity block
   */
  const std::optional< continuous::NU >& DNU() const { return this->dnu_; }

  /**
   *  @brief Return the delayed fission multiplicity block
   */
  const std::optional< continuous::NU >& delayedFissionMultiplicityBlock() const {

    return this->DNU();
  }

  /**
   *  @brief Return the delayed neutron precursor block
   */
  const std::optional< continuous::BDD >& BDD() const { return this->bdd_; }

  /**
   *  @brief Return the delayed neutron precursor block
   */
  const std::optional< continuous::BDD >& delayedNeutronPrecursorBlock() const {

    return this->BDD();
  }

  /**
   *  @brief Return the delayed neutron energy distribution block
   */
  const std::optional< continuous::DNED >& DNED() const { return this->dned_; }

  /**
   *  @brief Return the delayed neutron energy distribution block
   */
  const std::optional< continuous::DNED >& delayedNeutronEnergyDistributionBlock() const {

    return this->DNED();
  }

  /**
   *  @brief Return the secondary particle type block
   */
  const std::optional< continuous::PTYPE >& PTYPE() const { return this->ptype_; }

  /**
   *  @brief Return the secondary particle type block
   */
  const std::optional< continuous::PTYPE >& secondaryParticleTypeBlock() const {

    return this->PTYPE();
  }

  /**
   *  @brief Return the secondary particle information block
   */
  const std::optional< continuous::NTRO >& NTRO() const { return this->ntro_; }

  /**
   *  @brief Return the secondary particle information block
   */
  const std::optional< continuous::NTRO >& secondaryParticleInformationBlock() const {

    return this->NTRO();
  }

  /**
   *  @brief Return the secondary particle locator block
   */
  const std::optional< continuous::IXS >& IXS() const { return this->ixs_; }

  /**
   *  @brief Return the secondary particle locator block
   */
  const std::optional< continuous::IXS >& secondaryParticleLocatorBlock() const {

    return this->IXS();
  }

  /**
   *  @brief Return the secondary particle production block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::HPD& HPD( std::size_t index ) const {

    return this->hpd_[ index - 1 ];
  }

  /**
   *  @brief Return secondary particle production block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::HPD& secondaryParticleProductionBlock( std::size_t index ) const {

    return this->HPD( index );
  }

  /**
   *  @brief Return the reaction number block for a secondary particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::MTRH& MTRH( std::size_t index ) const {

    return this->mtrh_[ index - 1 ];
  }

  /**
   *  @brief Return the reaction number block for a secondary particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::MTRH& secondaryParticleReactionNumberBlock( std::size_t index ) const {

    return this->MTRH( index );
  }

  /**
   *  @brief Return the multiplicity and reference frame block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::TYRH& TYRH( std::size_t index ) const {

    return this->tyrh_[ index - 1 ];
  }

  /**
   *  @brief Return the multiplicity and reference frame block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::TYRH& secondaryParticleFrameAndMultiplicityBlock( std::size_t index ) const {

    return this->TYRH( index );
  }

  /**
   *  @brief Return the production cross section block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::SIGH& SIGH( std::size_t index ) const {

    return this->sigh_[ index - 1 ];
  }

  /**
   *  @brief Return the production cross section block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::SIGH& secondaryParticleProductionCrossSectionBlock( std::size_t index ) const {

    return this->SIGH( index );
  }

  /**
   *  @brief Return the angular distribution block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::ANDH& ANDH( std::size_t index ) const {

    return this->andh_[ index - 1 ];
  }

  /**
   *  @brief Return the angular distribution block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::ANDH& secondaryParticleAngularDistributionBlock( std::size_t index ) const {

    return this->ANDH( index );
  }

  /**
   *  @brief Return the energy distribution block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::DLWH& DLWH( std::size_t index ) const {

    return this->dlwh_[ index - 1 ];
  }

  /**
   *  @brief Return the energy distribution block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::DLWH& secondaryParticleEnergyDistributionBlock( std::size_t index ) const {

    return this->DLWH( index );
  }

  /**
   *  @brief Return the multiplicity reaction number block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::YH& YH( std::size_t index ) const {

    return this->yh_[ index - 1 ];
  }

  /**
   *  @brief Return the multiplicity reaction number block for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::YH& secondaryParticleMultiplicityReactionNumberBlock( std::size_t index ) const {

    return this->YH( index );
  }
};

} // ACEtk namespace
} // njoy namespace

#endif
