#ifndef NJOY_ACETK_ELECTRONTABLE
#define NJOY_ACETK_ELECTRONTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/electron/BremsstrahlungAngularSpectrumBlock.hpp"
#include "ACEtk/electron/BremsstrahlungCorrectionFactorBlock.hpp"
#include "ACEtk/electron/BremsstrahlungEnergySpectrumBlock.hpp"
#include "ACEtk/electron/BremsstrahlungHighFrequencyBlock.hpp"
#include "ACEtk/electron/BremsstrahlungProductionBlock.hpp"
#include "ACEtk/electron/MottScatteringCorrectionBlock.hpp"
#include "ACEtk/electron/OscillatorBlock.hpp"
#include "ACEtk/electron/RadiationStoppingPowerBlock.hpp"
#include "ACEtk/electron/RileyCrossSectionBlock.hpp"
#include "ACEtk/electron/TransitionEnergyBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The electron ACE table
 *
 *  The ElectronTable class represents the ACE table for the electron data.
 */
class ElectronTable : protected Table {
  
  /* fields */

  electron::EKT ekt_;
  electron::RAD rad_;
  electron::MOT mot_;
  electron::RLY rly_;
  std::optional< electron::XSB > xsb_;
  std::optional< electron::CRB > crb_;
  std::optional< electron::HFB > hfb_;
  std::optional< electron::RKT > rkt_;
  std::optional< electron::RKA > rka_;
  std::optional< electron::OSC > osc_;
  
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


  void generateBlocks() {

    // transition energy block
    auto iterators = block( 1 );
    this->ekt_ = electron::EKT( iterators.first, iterators.second, this->NEL() );

    // radiation stopping power block
    iterators = block( 2 );
    this->rad_ = electron::RAD( iterators.first, iterators.second,
                                this->NRAD(), this->NEL() );

    // Mott scattering correction block
    iterators = block( 3 );
    this->mot_ = electron::MOT( iterators.first, iterators.second, this->NMOT() );

    // Riley cross section block
    iterators = block( 4 );
    this->rly_ = electron::RLY( iterators.first, iterators.second );

    if ( this->NEL() == 3 ) {

      // nullify unused blocks
      this->crb_ = std::nullopt;
      this->hfb_ = std::nullopt;

      // bremsstrahlung production block
      iterators = block( 5 );
      this->xsb_ = electron::XSB( iterators.first, iterators.second,
                                  this->NEB(), this->NPB() );

      // bremsstrahlung energy spectrum block
      iterators = block( 9 );
      this->rkt_ = electron::RKT( iterators.first, iterators.second, this->NRKT() );

      // bremsstrahlung angular spectrum block
      iterators = block( 10 );
      this->rka_ = electron::RKA( iterators.first, iterators.second, this->NRKA() );

      // oscillator block
      iterators = block( 11 );
      this->osc_ = electron::OSC( iterators.first, iterators.second, this->NOSC() );
    } else {

      // nullify unused blocks
      this->xsb_ = std::nullopt;
      this->rkt_ = std::nullopt;
      this->rka_ = std::nullopt;
      this->osc_ = std::nullopt;

      // bremsstrahlung correction factor block
      iterators = block( 5 );
      this->crb_ = electron::CRB( iterators.first, iterators.second, this->NCRB() );

      // bremsstrahlung high frequency block
      iterators = block( 6 );
      this->hfb_ = electron::HFB( iterators.first, iterators.second, this->NHFB() );
    }
  }

  Data generateData( unsigned int z,
                     std::vector< unsigned int > za, std::vector< double > awr,
                     electron::EKT&& ekt, electron::RAD&& rad,
                     electron::MOT&& mot, electron::RLY&& rly,
                     std::optional< electron::XSB >&& xsb,
                     std::optional< electron::CRB >&& crb,
                     std::optional< electron::HFB >&& hfb,
                     std::optional< electron::RKT >&& rkt,
                     std::optional< electron::RKA >&& rka,
                     std::optional< electron::OSC >&& osc ) {

    std::array< int32_t, 16 > iz;
    std::array< double, 16 > aw;
    std::array< int64_t, 16 > nxs;
    std::array< int64_t, 32 > jxs;
    std::vector< double > xss;
    iz.fill( 0 );
    aw.fill( 0.0 );
    nxs.fill( 0 );
    jxs.fill( 0 );

    // assign za values
    if ( za.size() != awr.size() ) {

      Log::error( "Inconsistent number of ZA and atomic mass values" );
      Log::info( "Number of ZA values = {}", za.size() );
      Log::info( "Number of atomic mass values = {}", awr.size() );
      throw std::exception();
    }
    for ( unsigned int i = 0; i < za.size(); ++i ) {

      iz[i] = za[i];
      aw[i] = awr[i];
    }

    // determine electron table type (EL or EL03)
    unsigned int nel;
    if ( xsb.has_value() && !crb.has_value() && !hfb.has_value()
         && rkt.has_value() && rka.has_value() && osc.has_value() ) {

      nel = 3;
    } else if ( !xsb.has_value() && crb.has_value() && hfb.has_value()
                && !rkt.has_value() && !rka.has_value() && !osc.has_value() ) {

      nel = 0;
    } else {

      Log::error( "Inconsistent data blocks for electron table type" );
      Log::info( "For EL03 expect: XSB ({}), RKT ({}), RKA ({}), OSC ({})",
                 xsb.has_value() ? "yes" : "no",
                 rkt.has_value() ? "yes" : "no",
                 rka.has_value() ? "yes" : "no",
                 osc.has_value() ? "yes" : "no" );
      Log::info( "For EL expect: CRB ({}), HFB ({})",
                 crb.has_value() ? "yes" : "no",
                 hfb.has_value() ? "yes" : "no" );
      Log::info( "EL and EL03 are mutually exclusive" );
      throw std::exception();
    }

    // generate the xss array
    xss.insert( xss.end(), ekt.begin(), ekt.end() );
    xss.insert( xss.end(), rad.begin(), rad.end() );
    xss.insert( xss.end(), mot.begin(), mot.end() );
    xss.insert( xss.end(), rly.begin(), rly.end() );
    if ( nel == 3 ) {

      xss.insert( xss.end(), xsb.value().begin(), xsb.value().end() );
      xss.insert( xss.end(), rkt.value().begin(), rkt.value().end() );
      xss.insert( xss.end(), rka.value().begin(), rka.value().end() );
      xss.insert( xss.end(), osc.value().begin(), osc.value().end() );
    } else {

      xss.insert( xss.end(), crb.value().begin(), crb.value().end() );
      xss.insert( xss.end(), hfb.value().begin(), hfb.value().end() );
    }

    // generate the jxs array
    // offsets to blocks listed below:
    // JXS    EL03    EL
    //  1     1       1
    //  2     RAD     RAD
    //  3     MOT     MOT
    //  4     RLY     RLY
    //  5     XSB     CRB
    //  6     unused  HFB
    //  9     RKT     unused
    // 10     RKA     unused
    // 11     OSC     unused
    jxs[0] = 1;
    jxs[1] = jxs[0] + ekt.length();
    jxs[2] = jxs[1] + rad.length();
    jxs[3] = jxs[2] + mot.length();
    jxs[4] = jxs[3] + rly.length();
    if ( nel == 3 ) {

      jxs[8] = jxs[4] + xsb.value().length();
      jxs[9] = jxs[8] + rkt.value().length();
      jxs[10] = jxs[9] + rka.value().length();
    } else {

      jxs[5] = jxs[4] + crb.value().length();
    }

    // generate the nxs array
    // NXS    EL03    EL
    //  1    .value().length .value().length
    //  2     Z       Z
    //  3     NRAD    NRAD
    //  4     NMOT    NMOT
    //  5     NEB     NCRB
    //  6     NPB     NHFB
    //  9     NRKT    unused
    // 10     NRKA    unused
    // 11     NOSC    unused
    // 16     3       unused
    nxs[0] = xss.size();
    nxs[1] = z;
    nxs[2] = rad.NRAD();
    nxs[3] = mot.NMOT();
    if ( nel == 3 ) {

      nxs[4] = xsb.value().NEB();
      nxs[5] = xsb.value().NPB();
      nxs[8] = rkt.value().NRKT();
      nxs[9] = rka.value().NRKA();
      nxs[10] = osc.value().NOSC();
    } else {

      nxs[4] = crb.value().NCRB();
      nxs[5] = hfb.value().NHFB();
      nxs[8] = 0;
      nxs[9] = 0;
      nxs[10] = 0;
    }
    nxs[15] = nel;

    return { std::move( iz ), std::move( aw ),
             std::move( nxs ), std::move( jxs ), std::move( xss ) };
  }

  void verifyType() {

    char type = this->ZAID().back();
    if ( ( type != 'e' ) ) {

      Log::error( "The ZAID given in the ACE table ({}) does not appear to be an "
                  "electron type (e)", this->ZAID() );
      throw std::exception();
    }
  }
  
public:

  /**
   *  @brief Copy constructor using a generic table
   *
   *  @param[in] table    the generic table to be copied
   */
  ElectronTable( const Table& table ): Table( table ) {

    this->verifyType();
    this->generateBlocks();
  }

  /**
   *  @brief Move constructor using a generic table
   *
   *  @param[in] table    the generic table to be moved
   */
  ElectronTable( Table&& table ): Table( std::move( table ) ) {

    this->verifyType();
    this->generateBlocks();
  }

  /**
   *  @brief Copy constructor using a photoatomic table
   *
   *  @param[in] table    the photoatomic table to be copied
   */
  ElectronTable( const ElectronTable& table ) :
    Table( table ) {

    this->verifyType();
    this->generateBlocks();
  }

  /**
   *  @brief Move constructor using a photoatomic table
   *
   *  @param[in] table    the photoatomic table to be moved
   */
  ElectronTable( ElectronTable&& table ) :
    Table( std::move( table ) ) {

    this->verifyType();
    this->generateBlocks();
  }

  /**
   *  @brief Copy assignment using a photoatomic table
   *
   *  @param[in] table    the photoatomic table to be copied
   */
  ElectronTable& operator=( const ElectronTable& base ) {

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
  ElectronTable& operator=( ElectronTable&& base ) {

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
   *  @param[in] ekt       the transition energy block
   *  @param[in] rad       the radiation stopping power block
   *  @param[in] mot       the Mott scattering correction block
   *  @param[in] rly       the Riley cross section block
   *  @param[in] xsb       the brmsstrahlung production block (NEL == 3)
   *  @param[in] crb       the bremsstrahlung correction factor block (NEL != 3)
   *  @param[in] hfb       the bremsstrahlung high-frequency block (NEL != 3)
   *  @param[in] rkt       the bremsstrahlung energy spectrum block (NEL == 3)
   *  @param[in] rka       the bremsstrahlung angular spectrum block (NEL == 3)
   *  @param[in] osc       the oscillator block (NEL == 3)
   */
  ElectronTable( unsigned int z, HeaderVariant header,
                 std::vector< unsigned int > za, std::vector< double > awr,
                 electron::EKT ekt, electron::RAD rad,
                 electron::MOT mot, electron::RLY rly,
                 std::optional< electron::XSB > xsb,
                 std::optional< electron::CRB > crb,
                 std::optional< electron::HFB > hfb,
                 std::optional< electron::RKT > rkt,
                 std::optional< electron::RKA > rka,
                 std::optional< electron::OSC > osc ) :
    ElectronTable(
      Table( std::move( header ),
             generateData( z, std::move( za ), std::move( awr ),
                           std::move( ekt ), std::move( rad ),
                           std::move( mot ), std::move( rly ),
                           std::move( xsb ), std::move( crb ),
                           std::move( hfb ), std::move( rkt ),
                           std::move( rka ), std::move( osc ) ) ) ) {}
  
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
   *  @brief Return the EL data format flag (0 or 3)
   */
  unsigned int NEL() const { return this->data().NXS( 16 ); }

  /**
   *  @brief Return the EL data format flag (0 or 3)
   */
  unsigned int electronDataFormat() const { return this->NEL(); }

  /**
   *  @brief Return the total length of the XSS array
   */
  unsigned int length() const { return this->data().NXS( 1 ); }

  /**
   *  @brief Return the atom number of the element
   */
  unsigned int Z() const { return this->data().NXS( 2 ); }

  /**
   *  @brief Return the atom number of the element
   */
  unsigned int atomNumber() const { return this->Z(); }

  /**
   *  @brief Return the isomeric state of the target
   */
  unsigned int S() const { return 0; }

  /**
   *  @brief Return the isomeric state of the target
   */
  unsigned int isomericState() const { return this->S(); }

  /**
   *  @brief Return the mass number of the target
   */
  unsigned int A() const { return 0; }

  /**
   *  @brief Return the mass number of the target
   */
  unsigned int massNumber() const { return this->A(); }

  /**
   *  @brief Return the number of radiation stopping power points
   */
  unsigned int NRAD() const { return this->data().NXS( 3 ); }

  /**
   *  @brief Return the number of radiation stopping power points
   */
  unsigned int numberRadiationStoppingPoints() const { return this->NRAD(); }

  /**
   *  @brief Return the number of Mott scattering correction points
   */
  unsigned int NMOT() const { return this->data().NXS( 4 ); }

  /**
   *  @brief Return the number of Mott scattering correction points
   */
  unsigned int numberMottCorrectionPoints() const { return this->NMOT(); }

  /**
   *  @brief Return the number of electron energy points for bremsstrahlung production (NEL == 3)
   */
  unsigned int NEB() const { return ( this->NEL() == 3 ) ? this->data().NXS( 5 ) : 0; }

  /**
   *  @brief Return the number of electron energy points for bremsstrahlung production (NEL == 3)
   */
  unsigned int numberElectronBremsstrahlungEnergyPoints() const { return this->NEB(); }

  /**
   *  @brief Return the number of photon ratio points for bremsstrahlung production (NEL == 3)
   */
  unsigned int NPB() const { return ( this->NEL() == 3 ) ? this->data().NXS( 6 ) : 0; }

  /**
   *  @brief Return the number of photon ratio points for bremsstrahlung production (NEL == 3)
   */
  unsigned int numberPhotonBremsstrahlungRatioPoints() const { return this->NPB(); }

  /**
   *  @brief Return the number of bremsstrahlung correction factor points (NEL != 3)
   */
  unsigned int NCRB() const { return ( this->NEL() != 3 ) ? this->data().NXS( 5 ) : 0; }

  /**
   *  @brief Return the number of bremsstrahlung correction factor points (NEL != 3)
   */
  unsigned int numberBremsstrahlungCorrectionPoints() const { return this->NCRB(); }

  /**
   *  @brief Return the number of bremsstrahlung high-frequency limit points (NEL != 3)
   */
  unsigned int NHFB() const { return ( this->NEL() != 3 ) ? this->data().NXS( 6 ) : 0; }

  /**
   *  @brief Return the number of bremsstrahlung high-frequency limit points (NEL != 3)
   */
  unsigned int numberBremsstrahlungHighFrequencyPoints() const { return this->NHFB(); }

  /**
   *  @brief Return the number of bremsstrahlung energy spectrum points (NEL == 3)
   */
  unsigned int NRKT() const { return ( this->NEL() == 3 ) ? this->data().NXS( 9 ) : 0; }

  /**
   *  @brief Return the number of bremsstrahlung energy spectrum points (NEL == 3)
   */
  unsigned int numberBremsstrahlungEnergySpectrumPoints() const { return this->NRKT(); }

  /**
   *  @brief Return the number of bremsstrahlung angular spectrum points (NEL == 3)
   */
  unsigned int NRKA() const { return ( this->NEL() == 3 ) ? this->data().NXS( 10 ) : 0; }

  /**
   *  @brief Return the number of bremsstrahlung angular spectrum points (NEL == 3)
   */
  unsigned int numberBremsstrahlungAngularSpectrumPoints() const { return this->NRKA(); }

  /**
   *  @brief Return the number of oscillator points (NEL == 3)
   */
  unsigned int NOSC() const { return ( this->NEL() == 3 ) ? this->data().NXS( 11 ) : 0; }

  /**
   *  @brief Return the number of oscillator points (NEL == 3)
   */
  unsigned int numberOscillatorPoints() const { return this->NOSC(); }

  // JXS information

  // XSS blocks

  /**
   *  @brief Return the transition energy block
   */
  const electron::EKT& EKT() const { return this->ekt_; }

  /**
   *  @brief Return the transition energy block
   */
  const electron::EKT& transitionEnergyBlock() const {
    
    return this->EKT();
  }

  /**
   *  @brief Return the radiation stopping power block
   */
  const electron::RAD& RAD() const { return this->rad_; }

  /**
   *  @brief Return the radiation stopping power block
   */
  const electron::RAD& radiationStoppingPowerBlock() const {
    
    return this->RAD();
  }

  /**
   *  @brief Return the Mott scattering correction block
   */
  const electron::MOT& MOT() const { return this->mot_; }

  /**
   *  @brief Return the Mott scattering correction block
   */
  const electron::MOT& mottScatteringCorrectionBlock() const {
    
    return this->MOT();
  }

  /**
   *  @brief Return the Riley cross section block
   */
  const electron::RLY& RLY() const { return this->rly_; }

  /**
   *  @brief Return the Riley cross section block
   */
  const electron::RLY& rileyCrossSectionBlock() const {
    
    return this->RLY();
  }

  /**
   *  @brief Return the bremsstrahlung production block (NEL == 3)
   */
  const std::optional< electron::XSB >& XSB() const { return this->xsb_; }

  /**
   *  @brief Return the bremsstrahlung production block (NEL == 3)
   */
  const std::optional< electron::XSB >& bremsstrahlungProductionBlock() const {
    
    return this->XSB();
  }

  /**
   *  @brief Return the bremsstrahlung correction factor block (NEL != 3)
   */
  const std::optional< electron::CRB >& CRB() const { return this->crb_; }

  /**
   *  @brief Return the bremsstrahlung correction factor block (NEL != 3)
   */
  const std::optional< electron::CRB >& bremsstrahlungCorrectionFactorBlock() const {
    
    return this->CRB();
  }

  /**
   *  @brief Return the bremsstrahlung high-frequency block (NEL != 3)
   */
  const std::optional< electron::HFB >& HFB() const { return this->hfb_; }

  /**
   *  @brief Return the bremsstrahlung high-frequency block (NEL != 3)
   */
  const std::optional< electron::HFB >& bremsstrahlungHighFrequencyBlock() const {
    
    return this->HFB();
  }

  /**
   *  @brief Return the bremsstrahlung energy spectrum block (NEL == 3)
   */
  const std::optional< electron::RKT >& RKT() const { return this->rkt_; }

  /**
   *  @brief Return the bremsstrahlung energy spectrum block (NEL == 3)
   */
  const std::optional< electron::RKT >& bremsstrahlungEnergySpectrumBlock() const {
    
    return this->RKT();
  }

  /**
   *  @brief Return the bremsstrahlung angular spectrum block (NEL == 3)
   */
  const std::optional< electron::RKA >& RKA() const { return this->rka_; }

  /**
   *  @brief Return the bremsstrahlung angular spectrum block (NEL == 3)
   */
  const std::optional< electron::RKA >& bremsstrahlungAngularSpectrumBlock() const {
    
    return this->RKA();
  }

  /**
   *  @brief Return the oscillator block (NEL == 3)
   */
  const std::optional< electron::OSC >& OSC() const { return this->osc_; }

  /**
   *  @brief Return the oscillator block (NEL == 3)
   */
  const std::optional< electron::OSC >& oscillatorBlock() const {
    
    return this->OSC();
  }
  
};

} // ACEtk namespace
} // njoy namespace

#endif