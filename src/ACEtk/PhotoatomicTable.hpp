#ifndef NJOY_ACETK_PHOTOATOMICTABLE
#define NJOY_ACETK_PHOTOATOMICTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/photoatomic/PrincipalCrossSectionBlock.hpp"
#include "ACEtk/photoatomic/IncoherentScatteringFunctionBlock.hpp"
#include "ACEtk/photoatomic/CoherentFormFactorBlock.hpp"
#include "ACEtk/photoatomic/FluorescenceDataBlock.hpp"
#include "ACEtk/photoatomic/HeatingNumbersBlock.hpp"
#include "ACEtk/photoatomic/ComptonProfileBlock.hpp"
#include "ACEtk/photoatomic/PhotoelectricCrossSectionBlock.hpp"
#include "ACEtk/electroatomic/PrincipalCrossSectionBlock.hpp"
#include "ACEtk/electroatomic/ElasticCrossSectionBlock.hpp"
#include "ACEtk/electroatomic/ElectronShellBlock.hpp"
#include "ACEtk/electroatomic/ElectronSubshellBlock.hpp"
#include "ACEtk/electroatomic/SubshellTransitionDataBlock.hpp"
#include "ACEtk/electroatomic/ElasticAngularDistributionBlock.hpp"
#include "ACEtk/electroatomic/EnergyDistributionBlock.hpp"
#include "ACEtk/electroatomic/ExcitationBlock.hpp"
#include "ACEtk/electroatomic/BremsstrahlungBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The photoatomic ACE table
 *
 *  The PhotoatomicTable class represents the ACE table for the photoatomic data.
 */
class PhotoatomicTable : protected Table {

  /* fields */

  photoatomic::ESZG eszg_;
  photoatomic::JINC jinc_;
  photoatomic::JCOH jcoh_;
  std::optional< photoatomic::JFLO > jflo_;
  photoatomic::LHNM lhnm_;
  std::optional< electroatomic::EPS > eps_;
  std::optional< photoatomic::SWD > swd_;
  std::optional< electroatomic::SUBSH > subsh_;
  std::optional< photoatomic::SPHEL > sphel_;
  std::optional< electroatomic::XPROB > xprob_;
  std::optional< electroatomic::ESZE > esze_;
  std::optional< electroatomic::EXCIT > excit_;
  std::optional< electroatomic::ELAS > elas_;
  std::vector< electroatomic::EION > eion_;
  std::optional< electroatomic::BREME > breme_;
  std::optional< electroatomic::BREML > breml_;
  std::optional< electroatomic::SELAS > selas_;

  /* auxiliary functions */

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

  auto electroionisation_block( std::size_t index ) const {

    auto begin = this->data().XSS().begin();
    auto jxs23 = this->data().JXS( 23 );

    auto nssh = this->NSSH();
    auto n = *std::next( begin, jxs23 + index - 2 );
    auto start = std::next( begin, *std::next( begin, jxs23 + nssh + index - 2 ) - 1 );
    auto end = index != nssh
               ? std::next( begin, *std::next( begin, jxs23 + nssh + index - 1 ) - 1 )
               : std::next( begin, this->data().JXS( 24 ) - 1 );

    return std::make_tuple( start, end, n );
  }

  void generateBlocks() {

    // reset optional blocks
    this->jflo_ = std::nullopt;
    this->eps_ = std::nullopt;
    this->swd_ = std::nullopt;
    this->subsh_ = std::nullopt;
    this->sphel_ = std::nullopt;
    this->xprob_ = std::nullopt;
    this->esze_ = std::nullopt;
    this->excit_ = std::nullopt;
    this->elas_ = std::nullopt;
    this->breme_ = std::nullopt;
    this->breml_ = std::nullopt;
    this->selas_ = std::nullopt;

    // clear vectors
    eion_.clear();

    // principal cross section data
    auto iterators = block( 1 );
    this->eszg_ = photoatomic::ESZG( iterators.first, iterators.second, this->NES() );

    // incoherent scattering functions
    iterators = block( 2 );
    this->jinc_ = photoatomic::JINC( iterators.first, iterators.second );

    // coherent form factor
    iterators = block( 3 );
    this->jcoh_ = photoatomic::JCOH( iterators.first, iterators.second );

    // fluorescence data block
    bool present = ( this->NFLO() > 0 );
    if ( present ) {

      iterators = block( 4 );
      this->jflo_ = photoatomic::JFLO( iterators.first, iterators.second, this->NFLO() );
    }

    // heating numbers
    iterators = block( 5 );
    this->lhnm_ = photoatomic::LHNM( iterators.first, iterators.second, this->NES() );

    present = ( this->NSH() > 0 );
    if ( present ) {

      // electron shell block
      auto locators = block( 6 );
      iterators = block( 8 );
      this->eps_ = electroatomic::EPS( locators.first, iterators.second, this->NSH() );

      // compton profile block
      locators = block( 9 );
      iterators = block( 10 );
      this->swd_ = photoatomic::SWD( locators.first, iterators.first, iterators.second,
                                     this->NSH() );
    }

    present = ( this->NEPR() > 0 );
    if ( present ) {

      auto subsh = block( 11 );
      auto sphel = block( 16 );
      this->subsh_ = electroatomic::SUBSH( subsh.first, sphel.first, this->NSSH() );
      this->sphel_ = photoatomic::SPHEL( sphel.first, sphel.second, this->NSSH(), this->NES() );
      auto relo = block( 17 );
      auto xprob = block( 18 );
      this->xprob_ = electroatomic::XPROB( relo.first, xprob.first, xprob.second, this->NSSH() );
      auto esze = block( 19 );
      this->esze_ = electroatomic::ESZE( esze.first, esze.second, this->NSSH(), this->NE() );
      auto excit = block( 20 );
      this->excit_ = electroatomic::EXCIT( excit.first, excit.second, this->NXL() );
      auto elasi = block( 21 );
      auto elas = block( 22 );
      this->elas_ = electroatomic::ELAS( elasi.first, elas.second, this->NA() );

      // electronionisation
      for ( std::size_t index = 1; index <= this->NSSH(); ++index ) {

        auto eion = electroionisation_block( index );
        this->eion_.emplace_back( std::get< 0 >( eion ), std::get< 1 >( eion ),
                                  std::get< 2 >( eion ) );
      }

      auto bremi = block( 24 );
      auto breme = block( 25 );
      this->breme_ = electroatomic::BREME( bremi.first, breme.second, this->NB() );
      auto breml = block( 26 );
      this->breml_ = electroatomic::BREML( breml.first, breml.second, this->NBL() );

      present = ( this->NEPR() == 3 );
      if ( present ) {

        auto selas = block( 27 );
        this->selas_ = electroatomic::SELAS( selas.first, selas.second, this->NE() );
      }
    }
  }

  Data generateData( unsigned int z,
                     std::vector< unsigned int > za, std::vector< double > awr,
                     photoatomic::ESZG&& eszg, photoatomic::JINC&& jinc,
                     photoatomic::JCOH&& jcoh, photoatomic::LHNM&& lhnm,
                     std::optional< photoatomic::JFLO >&& jflo,
                     std::optional< electroatomic::EPS >&& eps,
                     std::optional< photoatomic::SWD >&& swd,
                     std::optional< electroatomic::SUBSH >&& subsh,
                     std::optional< photoatomic::SPHEL >&& sphel,
                     std::optional< electroatomic::XPROB >&& xprob,
                     std::optional< electroatomic::ESZE >&& esze,
                     std::optional< electroatomic::EXCIT >&& excit,
                     std::optional< electroatomic::ELAS >&& elas,
                     std::vector< electroatomic::EION >&& eion,
                     std::optional< electroatomic::BREME >&& breme,
                     std::optional< electroatomic::BREML >&& breml,
                     std::optional< electroatomic::SELAS >&& selas ) {

    std::array< int32_t, 16 > iz;
    std::array< double, 16 > aw;
    std::array< int64_t, 16 > nxs;
    std::array< int64_t, 32 > jxs;
    iz.fill( 0 );
    aw.fill( 0. );
    nxs.fill( 0 );
    jxs.fill( 0 );
    std::vector< double > xss;

    // assign za values
    for ( unsigned int i = 0; i < za.size(); ++i ) {

      iz[i] = za[i];
      aw[i] = awr[i];
    }

    // determine data type
    unsigned int nepr = ( subsh.has_value() ? ( selas.has_value() ? 3 : 1 ) : 0 );

    // some size values
    unsigned int nes = eszg.NES();
    unsigned int nsh = swd.has_value() ? swd->NSH() : 0;
    unsigned int nflo = jflo.has_value() ? jflo->NFLO() : 0;
    unsigned int nssh = nepr > 0 ? subsh->NSSH() : 0;
    unsigned int ne = nepr > 0 ? esze->NE() : 0;
    unsigned int nxl = nepr > 0 ? excit->NXL() : 0;
    unsigned int na = nepr > 0 ? elas->NA() : 0;
    unsigned int nb = nepr > 0 ? breme->NB() : 0;
    unsigned int nbl = nepr > 0 ? breml->NBL() : 0;
    unsigned int ninc = nepr > 1 ? jinc.NM() : 0;
    unsigned int ncoh = nepr > 1 ? jcoh.NM() : 0;

    // verify some stuff:
    //  - same number of ZA and atomic mass values
    //  - ESZG, LHNM and SPHEL use the same number of incident energy values
    //  - SWD and EPS use the same number of shells
    //  - SUBSH, XPROB, ESZE and EION use the same number of subshells for nepr > 0
    if ( za.size() != awr.size() ) {

      Log::error( "Inconsistent number of ZA and atomic mass values" );
      Log::info( "Number of ZA values = {}", za.size() );
      Log::info( "Number of atomic mass values = {}", awr.size() );
      throw std::exception();
    }
    bool sphelsize = sphel.has_value() ? nes != sphel->NES() : false;
    if ( ( nes != lhnm.NES() ) || sphelsize ) {

      Log::error( "Inconsistent NES between the different blocks" );
      Log::info( "ESZG NES value = {}", eszg.NES() );
      Log::info( "LHNM NES value = {}", lhnm.NES() );
      throw std::exception();
    }
    if ( eps.has_value() && swd.has_value() ) {

      if ( ( nsh != eps->NSH() ) || ( nsh != swd->NSH() ) ) {

        Log::error( "Inconsistent NSH between the different blocks" );
        Log::info( "EPS NSH value = {}", eps->NSH() );
        Log::info( "SWD NSH value = {}", swd->NSH() );
        throw std::exception();
      }
    }
    if ( nepr > 0 ) {

      if ( ( nssh != xprob->NSSH() ) || ( nssh != esze->NSSH() ) ||
           ( nssh != eion.size() ) ) {

        Log::error( "Inconsistent NSSH between the different blocks" );
        Log::info( "SUBSH NSSH value = {}", subsh->NSSH() );
        Log::info( "XPROB NSSH value = {}", xprob->NSSH() );
        Log::info( "ESZE NSSH value = {}", esze->NSSH() );
        Log::info( "EION NSSH value = {}", eion.size() );
        throw std::exception();
      }
    }
    if ( nepr == 3 ) {

      if ( ne != selas->NE() ) {

        Log::error( "Inconsistent NE between the different blocks" );
        Log::info( "ESZE NE value = {}", esze->NE() );
        Log::info( "SELAS NE value = {}", selas->NE() );
        throw std::exception();
      }
    }

    // generate the xss array and set the locators in the jxs array as we go
    jxs[0] = 1;
    xss.insert( xss.end(), eszg.begin(), eszg.end() );
    jxs[1] = xss.size() + 1;
    xss.insert( xss.end(), jinc.begin(), jinc.end() );
    jxs[2] = xss.size() + 1;
    xss.insert( xss.end(), jcoh.begin(), jcoh.end() );
    jxs[3] = xss.size() + 1;
    if ( jflo.has_value() ) {

      xss.insert( xss.end(), jflo->begin(), jflo->end() );
    }
    jxs[4] = xss.size() + 1;
    xss.insert( xss.end(), lhnm.begin(), lhnm.end() );
    if ( eps.has_value() ) {

      jxs[5] = xss.size() + 1;
      jxs[6] = xss.size() + nsh + 1;
      jxs[7] = xss.size() + 2 * nsh + 1;
      xss.insert( xss.end(), eps->begin(), eps->end() );
    }
    if ( swd.has_value() ) {

      jxs[8] = xss.size() + 1;
      jxs[9] = xss.size() + nsh + 1;
      xss.insert( xss.end(), swd->begin(), swd->end() );
    }
    if ( nepr > 0 ) {

      jxs[10] = xss.size() + 1;
      jxs[11] = jxs[10] + nssh;
      jxs[12] = jxs[11] + nssh;
      jxs[13] = jxs[12] + nssh;
      jxs[14] = jxs[13] + nssh;
      xss.insert( xss.end(), subsh->begin(), subsh->end() );
      jxs[15] = xss.size() + 1;
      xss.insert( xss.end(), sphel->begin(), sphel->end() );
      jxs[16] = xss.size() + 1;
      jxs[17] = jxs[16] + nssh;
      xss.insert( xss.end(), xprob->begin(), xprob->end() );
      jxs[18] = xss.size() + 1;
      xss.insert( xss.end(), esze->begin(), esze->end() );
      jxs[19] = xss.size() + 1;
      xss.insert( xss.end(), excit->begin(), excit->end() );
      jxs[20] = xss.size() + 1;
      jxs[21] = jxs[20] + 3 * na;
      xss.insert( xss.end(), elas->begin(), elas->end() );
      jxs[22] = xss.size() + 1;
      unsigned int l = xss.size();
      xss.insert( xss.end(), 3 * nssh, 0.0 );
      for ( auto&& block : eion ) {

        xss[l] = block.NB();
        xss[l + nssh] = xss.size() + 1;
        xss[l + 2 * nssh] = xss.size() + 3 * block.NB() + 1;
        xss.insert( xss.end(), block.begin(), block.end() );
        ++l;
      }
      jxs[23] = xss.size() + 1;
      jxs[24] = jxs[23] + 3 * nb;
      xss.insert( xss.end(), breme->begin(), breme->end() );
      jxs[25] = xss.size() + 1;
      xss.insert( xss.end(), breml->begin(), breml->end() );
      if ( nepr == 3 ) {

        jxs[26] = xss.size() + 1;
        xss.insert( xss.end(), selas->begin(), selas->end() );
      }
    }

    // set the nxs values for the continuous energy table
    // NXS(1) = length
    // NXS(2) = Z
    // NXS(3) = NES
    // NXS(4) = NFLO
    // NXS(5) = NSH
    // NXS(6) = NEPR
    // NXS(7) = NSSH
    // NXS(8) = NE
    // NXS(9) = NXL
    // NXS(10) = NA
    // NXS(11) = NB
    // NXS(12) = NBL
    // NXS(13) = NINC
    // NXS(14) = NCOH
    nxs[0] = xss.size();
    nxs[1] = z;
    nxs[2] = nes;
    nxs[3] = nflo;
    nxs[4] = nsh;
    nxs[5] = nepr;
    nxs[6] = nssh;
    nxs[7] = ne;
    nxs[8] = nxl;
    nxs[9] = na;
    nxs[10] = nb;
    nxs[11] = nbl;
    nxs[12] = ninc;
    nxs[13] = ncoh;

    return { std::move( iz ), std::move( aw ),
             std::move( nxs ), std::move( jxs ), std::move( xss ) };
  }

  void verifyType() {

    char type = this->ZAID().back();
    if ( ( type != 'p' ) ) {

      Log::error( "The ZAID given in the ACE table ({}) does not appear to be a "
                  "photoatomic type (p)", this->ZAID() );
      throw std::exception();
    }
  }

  void verifySubshellIndex( const std::size_t index ) const {

    if ( ( index < 1 ) || ( index > this->NSSH() ) ) {

      Log::error( "Illegal subshell index argument into the photoatomic table" );
      Log::info( "Index value: {}", index );
      Log::info( "The photoatomic table accepts an index between 1 and {} inclusively",
                 this->NSSH() );
      throw std::out_of_range( "PhotoatomicTable" );
    }
  }

public:

  /**
   *  @brief Copy constructor using a generic table
   *
   *  @param[in] table    the generic table to be copied
   */
  PhotoatomicTable( const Table& table ): Table( table ) {

    this->verifyType();
    this->generateBlocks();
  }

  /**
   *  @brief Move constructor using a generic table
   *
   *  @param[in] table    the generic table to be moved
   */
  PhotoatomicTable( Table&& table ): Table( std::move( table ) ) {

    this->verifyType();
    this->generateBlocks();
  }

  /**
   *  @brief Copy constructor using a photoatomic table
   *
   *  @param[in] table    the photoatomic table to be copied
   */
  PhotoatomicTable( const PhotoatomicTable& table ) :
    Table( table ) {

    this->verifyType();
    this->generateBlocks();
  }

  /**
   *  @brief Move constructor using a photoatomic table
   *
   *  @param[in] table    the photoatomic table to be moved
   */
  PhotoatomicTable( PhotoatomicTable&& table ) :
    Table( std::move( table ) ) {

    this->verifyType();
    this->generateBlocks();
  }

  /**
   *  @brief Copy assignment using a photoatomic table
   *
   *  @param[in] table    the photoatomic table to be copied
   */
  PhotoatomicTable& operator=( const PhotoatomicTable& base ) {

    if ( this != &base ) {

      Table::operator=( base );
      this->verifyType();
      this->generateBlocks();
    }
    return *this;
  }

  /**
   *  @brief Move assignment using a photoatomic table
   *
   *  @param[in] table    the photoatomic table to be moved
   */
  PhotoatomicTable& operator=( PhotoatomicTable&& base ) {

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
   *  @param[in] header    the header for the table
   *  @param[in] za        the list of ZA values
   *  @param[in] awr       the list of atomic mass values
   *  @param[in] eszg      the principal cross section block
   *  @param[in] jinc      the incoherent scattering function block
   *  @param[in] jcoh      the coherent form factor block
   *  @param[in] lhnm      the heating numbers block
   *  @param[in] jflo      the fluorescence data block
   *  @param[in] eps       the electron shell data block
   *  @param[in] swd       the compton profile block
   *  @param[in] subsh     the electron subshell data block
   *  @param[in] sphel     the photoelectric cross section block
   *  @param[in] xprob     the atomic relaxation data block
   *  @param[in] esze      the electron cross section block
   *  @param[in] excit     the excitation energy loss data block
   *  @param[in] elas      the electron elastic angular distribution block
   *  @param[in] eion      the electronionisation data block
   *  @param[in] breme     the photon energy distributions from Bremsstrahlung
   *  @param[in] breml     the electron average energy after Bremsstrahlung
   *  @param[in] selas     the additional electron elastic cross section block
   */
  PhotoatomicTable( unsigned int z, HeaderVariant header,
                    std::vector< unsigned int > za, std::vector< double > awr,
                    photoatomic::ESZG eszg, photoatomic::JINC jinc,
                    photoatomic::JCOH jcoh, photoatomic::LHNM lhnm,
                    std::optional< photoatomic::JFLO > jflo,
                    std::optional< electroatomic::EPS > eps,
                    std::optional< photoatomic::SWD > swd,
                    std::optional< electroatomic::SUBSH > subsh,
                    std::optional< photoatomic::SPHEL > sphel,
                    std::optional< electroatomic::XPROB > xprob,
                    std::optional< electroatomic::ESZE > esze,
                    std::optional< electroatomic::EXCIT > excit,
                    std::optional< electroatomic::ELAS > elas,
                    std::vector< electroatomic::EION > eion,
                    std::optional< electroatomic::BREME > breme,
                    std::optional< electroatomic::BREML > breml,
                    std::optional< electroatomic::SELAS > selas ) :
    PhotoatomicTable(
        Table( std::move( header ),
               generateData( z, std::move( za ), std::move( awr ),
                             std::move( eszg ), std::move( jinc ),
                             std::move( jcoh ), std::move( lhnm ),
                             std::move( jflo ), std::move( eps ),
                             std::move( swd ), std::move( subsh ),
                             std::move( sphel ), std::move( xprob ),
                             std::move( esze ), std::move( excit ),
                             std::move( elas ), std::move( eion ),
                             std::move( breme ), std::move( breml ),
                             std::move( selas ) ) ) ) {}

  using Table::header;
  using Table::data;
  using Table::print;

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
   *  @brief Return the atom number of the element
   */
  unsigned int Z() const { return this->data().NXS(2); }

  /**
   *  @brief Return the atom number of the element
   */
  unsigned int atomNumber() const { return this->Z(); }

  /**
   *  @brief Return the isomeric state of the target
   */
  static constexpr unsigned int S() { return 0; }

  /**
   *  @brief Return the isomeric state of the target
   */
  static constexpr unsigned int isomericState() { return 0; }

  /**
   *  @brief Return the mass number of the target
   */
  static constexpr unsigned int A() { return 0; }

  /**
   *  @brief Return the mass number of the target
   */
  static constexpr unsigned int massNumber() { return 0; }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int NES() const { return this->data().NXS(3); }

  /**
   *  @brief Return the number of energy points
   */
  unsigned int numberEnergyPoints() const { return this->NES(); }

  /**
   *  @brief Return the number of fluorescence edges
   */
  unsigned int NFLO() const { return this->data().NXS(4); }

  /**
   *  @brief Return the number of fluorescence edges
   */
  unsigned int numberFluorescenceEdges() const { return this->NFLO(); }

  /**
   *  @brief Return the number of electron shells (for Compton Doppler broadening)
   */
  unsigned int NSH() const { return this->data().NXS(5); }

  /**
   *  @brief Return the number of electron shells (for Compton Doppler broadening)
   */
  unsigned int numberElectronShells() const { return this->NSH(); }

  /**
   *  @brief Return the EPR data format flag (0 for the old mcplib format, 1 for
   *         EPR data from 2012 and 3 for EPR data from 2014 and above)
   */
  unsigned int NEPR() const { return this->data().NXS(6); }

  /**
   *  @brief Return the EPR data format flag (0 for the old mcplib format, 1 for
   *         EPR data from 2012 and 3 for EPR data from 2014 and above)
   */
  unsigned int electronPhotonRelaxationFormat() const { return this->NEPR(); }

  /**
   *  @brief Return the number of electron subshells (for photoelectric and electron
   *         impact ionization)
   */
  unsigned int NSSH() const { return this->data().NXS(7); }

  /**
   *  @brief Return the number of electron subshells (for photoelectric and electron
   *         impact ionization)
   */
  unsigned int numberElectronSubshells() const { return this->NSSH(); }

  /**
   *  @brief Return the number of electron energy points
   */
  unsigned int NE() const { return this->data().NXS(8); }

  /**
   *  @brief Return the number of electron energy points
   */
  unsigned int numberElectronEnergyPoints() const { return this->NE(); }

  /**
   *  @brief Return the number of electron excitation energy points
   */
  unsigned int NXL() const { return this->data().NXS(9); }

  /**
   *  @brief Return the number of electron excitation energy points
   */
  unsigned int numberElectronExcitationEnergyPoints() const {

    return this->NXL();
  }

  /**
   *  @brief Return the number of energy points with electron elastic angular
   *         distributions
   */
  unsigned int NA() const { return this->data().NXS(10); }

  /**
   *  @brief Return the number of energy points with electron elastic angular
   *         distributions
   */
  unsigned int numberElectronElasticEnergyPoints() const { return this->NA(); }

  /**
   *  @brief Return the number of energy points with Bremsstrahlung photon
   *         energy distributions
   */
  unsigned int NB() const { return this->data().NXS(11); }

  /**
  *  @brief Return the number of energy points with Bremsstrahlung photon
  *         energy distributions
   */
  unsigned int numberPhotonBremsstrahlungEnergyPoints() const {

    return this->NB();
  }

  /**
   *  @brief Return the number of electron Bremsstrahlung energy points
   */
  unsigned int NBL() const { return this->data().NXS(12); }

  /**
   *  @brief Return the number of electron Bremsstrahlung energy points
   */
  unsigned int numberElectronBremsstrahlungEnergyPoints() const {

    return this->NBL();
  }

  /**
   *  @brief Return the number of momentum values in the JINC block (NEPR > 1)
   */
  unsigned int NINC() const { return this->data().NXS(13); }

  /**
   *  @brief Return the number of momentum values in the JINC block (NEPR > 1)
   */
  unsigned int numberIncoherentMomentumValues() const { return this->NINC(); }

  /**
   *  @brief Return the number of momentum values in the JCOH block (NEPR > 1)
   */
  unsigned int NCOH() const { return this->data().NXS(14); }

  /**
   *  @brief Return the number of momentum values in the JCOH block (NEPR > 1)
   */
  unsigned int numberCoherentMomentumValues() const { return this->NCOH(); }

  // JXS information

  // XSS blocks

  /**
   *  @brief Return the principal cross section block
   */
  const photoatomic::ESZG& ESZG() const { return this->eszg_; }

  /**
   *  @brief Return the principal cross section block
   */
  const photoatomic::ESZG& principalCrossSectionBlock() const {

    return this->ESZG();
  }

  /**
   *  @brief Return the incoherent scattering function block
   */
  const photoatomic::JINC& JINC() const { return this->jinc_; }

  /**
   *  @brief Return the incoherent scattering function block
   */
  const photoatomic::JINC& incoherentScatteringFunctionBlock() const {

    return this->JINC();
  }

  /**
   *  @brief Return the coherent form factor block
   */
  const photoatomic::JCOH& JCOH() const { return this->jcoh_; }

  /**
   *  @brief Return the coherent form factor block
   */
  const photoatomic::JCOH& coherentFormFactorBlock() const {

    return this->JCOH();
  }

  /**
   *  @brief Return the fluoresence data block
   */
  const std::optional< photoatomic::JFLO >& JFLO() const { return this->jflo_; }

  /**
   *  @brief Return the fluoresence data block
   */
  const std::optional< photoatomic::JFLO >& fluorescenceDataBlock() const {

    return this->JFLO();
  }

  /**
   *  @brief Return the heating numbers block
   */
  const photoatomic::LHNM& LHNM() const { return this->lhnm_; }

  /**
   *  @brief Return the heating numbers block
   */
  const photoatomic::LHNM& heatingNumbersBlock() const { return this->LHNM(); }

  /**
   *  @brief Return the electron shell block
   */
  const std::optional< electroatomic::EPS >& EPS() const { return this->eps_; }

  /**
   *  @brief Return the electron shell block
   */
  const std::optional< electroatomic::EPS >& electronShellBlock() const {

    return this->EPS();
  }

  /**
   *  @brief Return the compton profile block
   */
  const std::optional< photoatomic::SWD >& SWD() const { return this->swd_; }

  /**
   *  @brief Return the compton profile block
   */
  const std::optional< photoatomic::SWD >& comptonProfileBlock() const {

    return this->SWD();
  }

  /**
   *  @brief Return the electron subshell data block for eprdata (NEPR > 0)
   */
  const std::optional< electroatomic::SUBSH >& SUBSH() const { return this->subsh_; }

  /**
   *  @brief Return the electron subshell data block for eprdata (NEPR > 0)
   */
  const std::optional< electroatomic::SUBSH >& electronSubshellBlock() const {

    return this->SUBSH();
  }

  /**
   *  @brief Return the photoelectric cross section block for eprdata (NEPR > 0)
   */
  const std::optional< photoatomic::SPHEL >& SPHEL() const {

    return this->sphel_;
  }

  /**
   *  @brief Return the photoelectric cross section block for eprdata (NEPR > 0)
   */
  const std::optional< photoatomic::SPHEL >& photoelectricCrossSectionBlock() const {

    return this->SPHEL();
  }

  /**
   *  @brief Return the subshell transition data block for eprdata (NEPR > 0)
   */
  const std::optional< electroatomic::XPROB >& XPROB() const { return this->xprob_; }

  /**
   *  @brief Return the subshell transition data block for eprdata (NEPR > 0)
   */
  const std::optional< electroatomic::XPROB >& subshellTransitionDataBlock() const {

    return this->XPROB();
  }

  /**
   *  @brief Return the electron cross section block for eprdata (NEPR > 0)
   */
  const std::optional< electroatomic::ESZE >& ESZE() const { return this->esze_; }

  /**
   *  @brief Return the electron cross section block for eprdata (NEPR > 0)
   */
  const std::optional< electroatomic::ESZE >& electronCrossSectionBlock() const {

    return this->ESZE();
  }

  /**
   *  @brief Return the electron excitation energy loss block for eprdata (NEPR > 0)
   */
  const std::optional< electroatomic::EXCIT >& EXCIT() const { return this->excit_; }

  /**
   *  @brief Return the electron excitation energy loss block for eprdata (NEPR > 0)
   */
  const std::optional< electroatomic::EXCIT >& electronExcitationEnergyLossBlock() const {

    return this->EXCIT();
  }

  /**
   *  @brief Return the electron elastic angular distribution block for eprdata (NEPR > 0)
   */
  const std::optional< electroatomic::ELAS >& ELAS() const { return this->elas_; }

  /**
   *  @brief Return the electron elastic angular distribution block for eprdata (NEPR > 0)
   */
  const std::optional< electroatomic::ELAS >& electronElasticAngularDistributionBlock() const {

    return this->ELAS();
  }

  /**
   *  @brief Return the knock-on electron energy distribution block for a subshell
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const electroatomic::EION& EION( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifySubshellIndex( index );
    #endif
    return this->eion_[ index - 1 ];
  }

  /**
   *  @brief Return the knock-on electron energy distribution block for a subshell
   *         index
   *
   *  When the index is out of range an std::out_of_range exception is thrown
   *  (debug mode only).
   *
   *  @param[in] index     the index (one-based)
   */
  const electroatomic::EION& electroionisationEnergyDistributionBlock( std::size_t index ) const {

    return this->EION( index );
  }

  /**
   *  @brief Return the Bremsstrahlung energy distribution block for eprdata (NEPR > 0)
   */
  const std::optional< electroatomic::BREME >& BREME() const { return this->breme_; }

  /**
   *  @brief Return the Bremsstrahlung energy distribution block for eprdata (NEPR > 0)
   */
  const std::optional< electroatomic::BREME >& bremsstrahlungEnergyDistributionBlock() const {

    return this->BREME();
  }

  /**
   *  @brief Return the electron energy after Brehmsstrahlung block for eprdata (NEPR > 0)
   */
  const std::optional< electroatomic::BREML >& BREML() const { return this->breml_; }

  /**
   *  @brief Return the electron energy after Brehmsstrahlung block for eprdata (NEPR > 0)
   */
  const std::optional< electroatomic::BREML >& electronEnergyAfterBremsstrahlungBlock() const {

    return this->BREML();
  }

  /**
   *  @brief Return the additional elastic cross section block for eprdata (NEPR = 3)
   */
  const std::optional< electroatomic::SELAS >& SELAS() const { return this->selas_; }

  /**
   *  @brief Return the additional elastic cross section block for eprdata (NEPR = 3)
   */
  const std::optional< electroatomic::SELAS >& electronElasticCrossSectionBlock() const {

    return this->SELAS();
  }
};

} // ACEtk namespace
} // njoy namespace

#endif
