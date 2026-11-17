#ifndef NJOY_ACETK_PHOTONUCLEARTABLE
#define NJOY_ACETK_PHOTONUCLEARTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/photonuclear/PrincipalCrossSectionBlock.hpp"
#include "ACEtk/continuous/ReactionNumberBlock.hpp"
#include "ACEtk/continuous/ReactionQValueBlock.hpp"
#include "ACEtk/continuous/CrossSectionBlock.hpp"
#include "ACEtk/photonuclear/SecondaryParticleLocatorBlock.hpp"
#include "ACEtk/continuous/CrossSectionData.hpp"
#include "ACEtk/continuous/FrameAndMultiplicityBlock.hpp"
#include "ACEtk/continuous/SecondaryParticleProductionCrossSectionBlock.hpp"
#include "ACEtk/continuous/SecondaryParticleAngularDistributionBlock.hpp"
#include "ACEtk/continuous/SecondaryParticleEnergyDistributionBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The photonuclear ACE table
 *
 *  The PhotonuclearTable class represents the ACE table for the photonuclear data.
 */
class PhotonuclearTable : protected Table {

  /* fields */

  photonuclear::ESZU eszu_;
  continuous::MTR mtr_;
  continuous::LQR lqr_;
  continuous::SIG sig_;

  std::optional< photonuclear::IXSU > ixsu_;
  std::vector< continuous::CrossSectionData > pxs_;
  std::vector< continuous::CrossSectionData > phn_;
  std::vector< continuous::MTRH > mtrh_;
  std::vector< continuous::TYRH > tyrh_;
  std::vector< continuous::SIGH > sigh_;
  std::vector< continuous::ANDH > andh_;
  std::vector< continuous::DLWH > dlwh_;

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
    if ( start != 0 ) {

      // look for the first value that is larger than or equal to the start locator
      auto iter = std::find_if( this->data().JXS().begin() + index,
                                this->data().JXS().end(),
                                [start] ( auto&& value ) {

                                  return value >= static_cast< int64_t >( start );
                                } );
      if ( iter != this->data().JXS().end() ) {

        end = *iter;
      }
    }

    return std::make_pair(
               begin + start - 1,
               end != 0 ? begin + end - 1
                        : start != 0 ? this->data().XSS().end()
                                     : begin + end - 1 );
  }

  auto block( std::size_t particle, std::size_t index ) const {

    // assumption: blocks are stored in sequence!

    auto begin = this->data().XSS().begin();
    std::size_t start = this->IXS()->LLOC( particle, index );

    // look for the first value that is larger than or equal to the start locator
    std::size_t end = 0;
    auto iter = std::find_if( this->IXS()->begin() + ( particle - 1 ) * 12 + index,
                              this->IXS()->end(),
                              [start] ( auto&& value ) {

                                return value >= static_cast< int64_t >( start );
                              } );
    if ( iter != this->IXS()->end() ) {

      end = *iter;
    }

    return std::make_pair(
               begin + start - 1,
               end != 0 ? begin + end - 1 : this->data().XSS().end() );
  }

  void generateBlocks() {

    // reset optional blocks
    this->ixsu_ = std::nullopt;

    // clear vectors
    this->pxs_.clear();
    this->phn_.clear();
    this->mtrh_.clear();
    this->tyrh_.clear();
    this->sigh_.clear();
    this->andh_.clear();
    this->dlwh_.clear();

    // principal cross section block
    unsigned int size = 3;
    if ( this->data().JXS(4) != 0 ) {

      size += 1;
    }
    auto locators = block( 1 );
    auto iterators = block( 6 );
    this->eszu_ = photonuclear::ESZU( locators.first, iterators.first, this->NES(), size );

    // reaction number block
    iterators = block( 6 );
    this->mtr_ = continuous::MTR( iterators.first, iterators.second, this->NTR() );

    // Q value block
    iterators = block( 7 );
    this->lqr_ = continuous::LQR( iterators.first, iterators.second, this->NTR() );

    // cross section block
    locators = block( 8 );
    iterators = block( 9 );
    this->sig_ = continuous::SIG( locators.first, iterators.first, iterators.second,
                                  this->NTR() );

    // secondary particles
    bool present = ( this->NTYPE() > 0 );
    if ( present ) {

      // secondary particle information and locator block
      iterators = block( 10 );
      this->ixsu_ = photonuclear::IXSU( iterators.first, iterators.second, this->NTYPE() );

      // secondary particle data: data blocks
      for ( std::size_t index = 1; index <= this->NTYPE(); ++index ) {

        // secondary particle data: total production cross section
        iterators = block( index, 3 );
        this->pxs_.emplace_back( iterators.first, iterators.second );

        // secondary particle data: average heating cross section
        iterators = block( index, 4 );
        this->phn_.emplace_back( iterators.first, iterators.second );

        // secondary particle data: reaction numbers
        iterators = block( index, 5 );
        this->mtrh_.emplace_back( iterators.first, iterators.second,
                                  this->IXS()->NP( index ) );

        // secondary particle data: reference frame and multiplicity
        iterators = block( index, 6 );
        this->tyrh_.emplace_back( iterators.first, iterators.second,
                                  this->IXS()->NP( index ) );

        // secondary particle data: production cross section data
        locators = block( index, 7 );
        iterators = block( index, 8 );
        this->sigh_.emplace_back( locators.first, iterators.first, iterators.second,
                                  this->IXS()->NP( index ) );

        // secondary particle data: angular distributions
        locators = block( index, 9 );
        iterators = block( index, 10 );
        this->andh_.emplace_back( locators.first, iterators.first, iterators.second,
                                  this->IXS()->NP( index ) );

        // secondary particle data: energy distributions
        locators = block( index, 11 );
        iterators = block( index, 12 );
        this->dlwh_.emplace_back( locators.first, iterators.first, iterators.second,
                                  this->TYRH( index ), this->IXS()->NP( index ) );
      }
    }
  }

  std::optional< std::vector< continuous::TYRH > >
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
                     photonuclear::ESZU&& eszu,  continuous::MTR&& mtr,
                     continuous::LQR&& lqr, continuous::SIG&& sig,
                     std::optional< std::vector< unsigned int > > ptype,
                     std::optional< std::vector< continuous::CrossSectionData > > pxs,
                     std::optional< std::vector< continuous::CrossSectionData > > phn,
                     std::optional< std::vector< continuous::MTRH > > mtrh,
                     std::optional< std::vector< continuous::SIGH > > sigh,
                     std::optional< std::vector< continuous::ANDH > > andh,
                     std::optional< std::vector< continuous::DLWH > > dlwh ) {

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
    unsigned int ntype = ptype ? ptype->size() : 0;

    // generate blocks we don't have yet
    std::optional< std::vector< continuous::TYRH > > tyrh = generateTYRH( dlwh );

    // verify some stuff:
    //  - MTR, LQR and SIG have the same NTR
    if ( ( ntr != lqr.NTR() ) || ( ntr != sig.NTR() ) ) {

      Log::error( "Inconsistent NTR between the different blocks" );
      Log::info( "MTR NTR value = {}", mtr.NTR() );
      Log::info( "LQR NTR value = {}", lqr.NTR() );
      Log::info( "SIG NTR value = {}", sig.NTR() );
      throw std::exception();
    }

    // generate the xss array and set the locators in the jxs array as we go
    jxs[0] = 1;
    jxs[1] = eszu.NES() + 1;
    jxs[2] = eszu.elastic().empty() ? jxs[1] : 0;
    jxs[3] = eszu.elastic().empty() ? 0 : 2 * eszu.NES() + 1;
    jxs[4] = eszu.elastic().empty() ? 2 * eszu.NES() + 1 : 3 * eszu.NES() + 1;
    xss.insert( xss.end(), eszu.begin(), eszu.end() );
    jxs[5] = xss.size() + 1;
    xss.insert( xss.end(), mtr.begin(), mtr.end() );
    jxs[6] = xss.size() + 1;
    xss.insert( xss.end(), lqr.begin(), lqr.end() );
    jxs[7] = xss.size() + 1;
    jxs[8] = xss.size() + ntr + 1;
    xss.insert( xss.end(), sig.begin(), sig.end() );
    if ( ptype.has_value() ) {

      std::vector< unsigned int > numbers;
      for ( const auto& element : mtrh.value() ) {

        numbers.push_back( element.NTR() );
      }

      auto size = ntype * 12;
      auto ixs_position = xss.size();
      std::vector< std::array< unsigned int, 10 > > ixs( ntype );

      jxs[9] = xss.size() + 1;
      jxs[10] = xss.size() + size + 1;

      for ( std::size_t index = 0; index < ntype; ++index ) {

        auto number = mtrh.value()[index].NTR();

        ixs[index][0] = xss.size() + size + 1;
        xss.insert( xss.end(), pxs.value()[index].begin(), pxs.value()[index].end() );
        ixs[index][1] = xss.size() + size + 1;
        xss.insert( xss.end(), phn.value()[index].begin(), phn.value()[index].end() );
        ixs[index][2] = xss.size() + size + 1;
        xss.insert( xss.end(), mtrh.value()[index].begin(), mtrh.value()[index].end() );
        ixs[index][3] = xss.size() + size + 1;
        xss.insert( xss.end(), tyrh.value()[index].begin(), tyrh.value()[index].end() );
        ixs[index][4] = xss.size() + size + 1;
        ixs[index][5] = xss.size() + size + number + 1;
        xss.insert( xss.end(), sigh.value()[index].begin(), sigh.value()[index].end() );
        ixs[index][6] = xss.size() + size + 1;
        ixs[index][7] = xss.size() + size + number + 1;
        xss.insert( xss.end(), andh.value()[index].begin(), andh.value()[index].end() );
        ixs[index][8] = xss.size() + size + 1;
        ixs[index][9] = xss.size() + size + number + 1;
        xss.insert( xss.end(), dlwh.value()[index].begin(), dlwh.value()[index].end() );
      }

      photonuclear::IXSU locators( std::move( ptype.value() ), std::move( numbers ),
                                   std::move( ixs ) );
      xss.insert( xss.begin() + ixs_position, locators.begin(), locators.end() );
    }

    // set the nxs values for the photonuclear table
    // NXS(1) = length
    // NXS(2) = za
    // NXS(3) = NES (number energies)
    // NXS(4) = NTR (total number of reactions)
    // NXS(5) = NTYPE (number of secondary particle types)
    // NXS(6) = 2
    // NXS(7) = 12
    // NXS(9) = s (isomeric state)
    // NXS(10) = z (atom number)
    // NXS(11) = a (mass number)
    // NXS(16) = 1
    nxs[0] = xss.size();
    nxs[1] = z * 1000 + a;
    nxs[2] = eszu.NES();
    nxs[3] = ntr;
    nxs[4] = ntype;
    nxs[5] = 2;
    nxs[6] = 12;
    nxs[8] = s;
    nxs[9] = z;
    nxs[10] = a;
    nxs[15] = 1;

    return { std::move( iz ), std::move( aw ),
             std::move( nxs ), std::move( jxs ), std::move( xss ) };
  }

  void verifyType() {

    char type = this->ZAID().back();
    if ( ( type != 'u' ) ) {

      Log::error( "The ZAID given in the ACE table ({}) does not appear to be a "
                  "photonuclear type (u)", this->ZAID() );
      throw std::exception();
    }
  }

public:

  /**
   *  @brief Copy constructor using a generic table
   *
   *  @param[in] table    the generic table to be copied
   */
  PhotonuclearTable( const Table& table ): Table( table ) {

    this->verifyType();
    this->setSZA();
    this->generateBlocks();
  }

  /**
   *  @brief Move constructor using a generic table
   *
   *  @param[in] table    the generic table to be moved
   */
  PhotonuclearTable( Table&& table ): Table( std::move( table ) ) {

    this->verifyType();
    this->setSZA();
    this->generateBlocks();
  }

  /**
   *  @brief Copy constructor using a photonuclear table
   *
   *  @param[in] table    the photonuclear table to be copied
   */
  PhotonuclearTable( const PhotonuclearTable& table ) :
    Table( table ) {

    this->verifyType();
    this->setSZA();
    this->generateBlocks();
  }

  /**
   *  @brief Move constructor using a photonuclear table
   *
   *  @param[in] table    the photonuclear table to be moved
   */
  PhotonuclearTable( PhotonuclearTable&& table ) :
    Table( std::move( table ) ) {

    this->verifyType();
    this->setSZA();
    this->generateBlocks();
  }

  /**
   *  @brief Copy assignment using a photonuclear table
   *
   *  @param[in] table    the photonuclear table to be copied
   */
  PhotonuclearTable& operator=( const PhotonuclearTable& base ) {

    if ( this != &base ) {

      Table::operator=( base );
      this->verifyType();
      this->generateBlocks();
    }
    return *this;
  }

  /**
   *  @brief Move assignment using a photonuclear table
   *
   *  @param[in] table    the photonuclear table to be moved
   */
  PhotonuclearTable& operator=( PhotonuclearTable&& base ) {

    if ( this != &base ) {

      Table::operator=( std::move( base ) );
      this->verifyType();
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
   *  @param[in] eszu      the principal cross section block
   *  @param[in] mtr       the reaction number block
   *  @param[in] lqr       the reaction Q value block
   *  @param[in] sig       the cross section data block
   *  @param[in] ptype     the secondary particle types
   *  @param[in] pxs       the secondary particle production cross section data
   *  @param[in] phn       the secondary particle heating cross section data
   *  @param[in] mtrh      the secondary particle production reaction number blocks
   *  @param[in] sigh      the secondary particle production cross section data blocks
   *  @param[in] andh      the secondary particle angular distribution data blocks
   *  @param[in] dlwh      the secondary particle energy distribution data blocks
   */
  PhotonuclearTable( unsigned int z, unsigned int a, unsigned int s,
                     HeaderVariant header,
                     photonuclear::ESZU eszu, continuous::MTR mtr,
                     continuous::LQR lqr, continuous::SIG sig,
                     std::optional< std::vector< unsigned int > > ptype,
                     std::optional< std::vector< continuous::CrossSectionData > > pxs,
                     std::optional< std::vector< continuous::CrossSectionData > > phn,
                     std::optional< std::vector< continuous::MTRH > > mtrh,
                     std::optional< std::vector< continuous::SIGH > > sigh,
                     std::optional< std::vector< continuous::ANDH > > andh,
                     std::optional< std::vector< continuous::DLWH > > dlwh ) :
    PhotonuclearTable(
        Table( std::move( header ),
               generateData( z, a, s, std::move( eszu ),
                             std::move( mtr ), std::move( lqr ),
                             std::move( sig ),
                             std::move( ptype ),
                             std::move( pxs ), std::move( phn ),
                             std::move( mtrh ),
                             std::move( sigh ), std::move( andh ),
                             std::move( dlwh ) ) ) ) {}

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
   *  @brief Return the number of secondary particle types
   */
  unsigned int NTYPE() const { return this->data().NXS(5); }

  /**
   *  @brief Return the number of secondary particle types
   */
  unsigned int numberSecondaryParticleTypes() const { return this->NTYPE(); }

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
  const photonuclear::ESZU& ESZ() const { return this->eszu_; }

  /**
   *  @brief Return the principal cross section block
   */
  const photonuclear::ESZU& principalCrossSectionBlock() const { return this->ESZ(); }

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
   *  @brief Return the cross section block
   */
  const continuous::SIG& SIG() const { return this->sig_; }

  /**
   *  @brief Return the cross section block
   */
  const continuous::SIG& crossSectionBlock() const { return this->SIG(); }

  /**
   *  @brief Return the secondary particle information and locator block
   */
  const std::optional< photonuclear::IXSU >& IXS() const { return this->ixsu_; }

  /**
   *  @brief Return the secondary particle information and locator block
   */
  const std::optional< photonuclear::IXSU >& secondaryParticleLocatorBlock() const {

    return this->IXS();
  }

  /**
   *  @brief Return the secondary particle production cross section for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::CrossSectionData& PXS( std::size_t index ) const {

    return this->pxs_[ index - 1 ];
  }

  /**
   *  @brief Return the secondary particle production cross section for a secondary
   *         particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::CrossSectionData&
  secondaryParticleProductionCrossSection( std::size_t index ) const {

    return this->PXS( index );
  }

  /**
   *  @brief Return the secondary particle average heating cross section for a
   *         secondary particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::CrossSectionData& PHN( std::size_t index ) const {

    return this->phn_[ index - 1 ];
  }

  /**
   *  @brief Return the secondary particle average heating cross section for a
   *         secondary particle index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const continuous::CrossSectionData&
  secondaryParticleHeatingCrossSection( std::size_t index ) const {

    return this->PHN( index );
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
};

} // ACEtk namespace
} // njoy namespace

#endif
