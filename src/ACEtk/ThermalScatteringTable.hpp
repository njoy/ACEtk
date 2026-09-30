#ifndef NJOY_ACETK_THERMALSCATTERINGTABLE
#define NJOY_ACETK_THERMALSCATTERINGTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/thermal/CrossSectionBlock.hpp"
#include "ACEtk/thermal/InelasticAngularDistributionBlock.hpp"
#include "ACEtk/thermal/ElasticAngularDistributionBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The thermal scattering ACE table
 *
 *  The ThermalScatteringTable class represents the ACE table for the thermal
 *  scattering data.
 */
class ThermalScatteringTable : protected Table {

  /* fields */

  thermal::ITIE itie_;
  thermal::ITXE itxe_;
  std::optional< thermal::ITCE > itce_;
  std::optional< thermal::ITCA > itca_;
  std::optional< thermal::ITCEI> itcei_;
  std::optional< thermal::ITCAI> itcai_;

  /* auxiliary functions */

  auto block( std::size_t index ) const {

    // assumption: blocks are stored in sequence!

    auto begin = this->data().XSS().begin();
    std::size_t start = this->data().JXS( index );

    std::size_t end = 0;
    if ( start != 0 ) {

      // look for the first value that is larger than or equal to the start locator
      auto iter = std::find_if( index == 1 || index == 4 || index == 7
                                  ? this->data().JXS().begin() + index + 1
                                  : this->data().JXS().begin() + index,
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

    // reset optional blocks
    this->itce_ = std::nullopt;
    this->itca_ = std::nullopt;
    this->itcei_ = std::nullopt;
    this->itcai_ = std::nullopt;

    // starting iterator into the XSS array
    auto begin = this->data().XSS().begin();

    // inelastic thermal scattering data
    bool present = this->data().JXS(1) > 0 ? true : false;
    auto iterators = block( 1 );
    this->itie_ = thermal::ITIE( present ? iterators.first : begin,
                                 present ? iterators.second : begin );

    iterators = block( 3 );
    this->itxe_ = thermal::ITXE( present ? this->IFENG() : 0,
                                 present ? this->IFENG() < 2 ? this->NIEB() : 0 : 0,
                                 present ? this->IFENG() < 2 ? this->NIL() + 1
                                                             : this->NIL() - 1
                                         : 0,
                                 present ? this->ITIE().NE() : 0,
                                 present ? this->data().JXS(3) : 1,
                                 present ? iterators.first : begin,
                                 present ? iterators.second : begin );

    // coherent elastic thermal scattering data
    present = this->IDPNC() > 3 ? true : false;
    if ( present ) {

      iterators = block( 4 );
      this->itce_ = thermal::ITCE( iterators.first, iterators.second );

      present = this->NCL() + 1 != 0 ? true : false;
      if ( present ) {

        iterators = block( 6 );
        this->itca_ = thermal::ITCA( iterators.first, iterators.second,
                                     this->ITCE()->NE(), this->NCL() + 1 );
      }
    }

    // incoherent elastic thermal scattering data
    present = this->IDPNC() == 3 || this->IDPNC() == 5 ? true : false;
    if ( present ) {

      iterators = this->IDPNC() == 3 ? block( 4 ) : block( 7 );
      this->itcei_ = thermal::ITCEI( iterators.first, iterators.second );

      iterators = this->IDPNC() == 3 ? block( 6 ) : block( 9 );
      this->itcai_ = thermal::ITCA( iterators.first, iterators.second,
                                    this->ITCEI()->NE(),
                                    this->IDPNC() == 3 ? this->NCL() + 1
                                                       : this->NCLI() + 1 );
    }
  }

  Data generateData( std::vector< unsigned int > za,
                     thermal::ITIE&& itie, thermal::ITXE&& itxe,
                     std::optional< thermal::ITCE >&& itce,
                     std::optional< thermal::ITCA >&& itca,
                     std::optional< thermal::ITCEI >&& itcei,
                     std::optional< thermal::ITCAI >&& itcai ) {

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
    }

    // some size values
    unsigned int ne = itie.NE();
    int ncl = 0;
    int ncli = 0;

    // some options
    unsigned int idpnc = 0;
    if ( itce.has_value() || itcei.has_value() ) {

      if ( itce.has_value() && itcei.has_value() ) {

        idpnc = 5;
        ncl = itca.has_value() ? itca->NCL() : -1;
        ncli = itcai->NCL();
      }
      else {

        if ( itce.has_value() ) {

          idpnc = 4;
          ncl = itca.has_value() ? itca->NCL() : -1;
        }
        else {

          idpnc = 3;
          ncl = itcai->NCL();
        }
      }
    }

    // verify some stuff:
    //  - ITIE and ITXE use the same numbeer of incident energy values
    if ( ne != itxe.NE() ) {

      Log::error( "Inconsistent NE between the different blocks" );
      Log::info( "ITIE NE value = {}", itie.NE() );
      Log::info( "ITXE NE value = {}", itxe.NE() );
      throw std::exception();
    }

    // generate the xss array and set the locators in the jxs array as we go
    jxs[0] = 1;
    jxs[1] = jxs[0] + ne + 1;
    xss.insert( xss.end(), itie.begin(), itie.end() );
    jxs[2] = xss.size() + 1;
    xss.insert( xss.end(), itxe.begin(), itxe.end() );
    if ( idpnc == 3 ) {

      jxs[3] = xss.size() + 1;
      jxs[4] = jxs[3] + itcei->NE() + 1;
      xss.insert( xss.end(), itcei->begin(), itcei->end() );
      jxs[5] = xss.size() + 1;
      xss.insert( xss.end(), itcai->begin(), itcai->end() );
    }
    if ( ( idpnc == 4 ) || ( idpnc == 5 ) ) {

      jxs[3] = xss.size() + 1;
      jxs[4] = jxs[3] + itce->NE() + 1;
      xss.insert( xss.end(), itce->begin(), itce->end() );
      if ( itca ) {

        jxs[5] = itca->empty() ? 0 : xss.size() + 1;
        xss.insert( xss.end(), itca->begin(), itca->end() );
      }
    }
    if ( idpnc == 5 ) {

      jxs[6] = xss.size() + 1;
      jxs[7] = jxs[6] + itcei->NE() + 1;
      xss.insert( xss.end(), itcei->begin(), itcei->end() );
      jxs[8] = xss.size() + 1;
      xss.insert( xss.end(), itcai->begin(), itcai->end() );
    }

    // set the nxs values for the continuous energy table
    // NXS(1) = length
    // NXS(2) = IDPNI
    // NXS(3) = NIL
    // NXS(4) = NIEB
    // NXS(5) = IDPNC
    // NXS(6) = NCL
    // NXS(7) = IFENG
    // NXS(8) = NCLI
    nxs[0] = xss.size();
    nxs[1] = 3;
    nxs[2] = itxe.NIL();
    nxs[3] = itxe.IFENG() < 2 ? itxe.NIEB( 1 ) : 0;
    nxs[4] = idpnc;
    nxs[5] = ncl;
    nxs[6] = itxe.IFENG();
    nxs[7] = ncli;

    return { std::move( iz ), std::move( aw ),
             std::move( nxs ), std::move( jxs ), std::move( xss ) };
  }

  void verifyType() {

    char type = this->ZAID().back();
    if ( ( type != 't' ) ) {


      Log::error( "The ZAID given in the ACE table ({}) does not appear to be a "
                  "thermal scattering type (t)", this->ZAID() );
      throw std::exception();
    }
  }

public:

  /**
   *  @brief Copy constructor using a generic table
   *
   *  @param[in] table    the generic table to be copied
   */
  ThermalScatteringTable( const Table& table ): Table( table ) {

    this->verifyType();
    this->generateBlocks();
  }

  /**
   *  @brief Move constructor using a generic table
   *
   *  @param[in] table    the generic table to be moved
   */
  ThermalScatteringTable( Table&& table ): Table( std::move( table ) ) {

    this->verifyType();
    this->generateBlocks();
  }

  /**
   *  @brief Copy constructor using a thermal scattering table
   *
   *  @param[in] table    the thermal scattering table to be copied
   */
  ThermalScatteringTable( const ThermalScatteringTable& table ) :
    Table( table ) {

    this->verifyType();
    this->generateBlocks();
  }

  /**
   *  @brief Move constructor using a thermal scattering table
   *
   *  @param[in] table    the thermal scattering table to be moved
   */
  ThermalScatteringTable( ThermalScatteringTable&& table ) :
    Table( std::move( table ) ) {

    this->verifyType();
    this->generateBlocks();
  }

  /**
   *  @brief Copy assignment using a thermal scattering table
   *
   *  @param[in] table    the thermal scattering table to be copied
   */
  ThermalScatteringTable& operator=( const ThermalScatteringTable& base ) {

    if ( this != &base ) {

      Table::operator=( base );
      this->verifyType();
      this->generateBlocks();
    }
    return *this;
  }

  /**
   *  @brief Move assignment using a thermal scattering table
   *
   *  @param[in] table    the thermal scattering table to be moved
   */
  ThermalScatteringTable& operator=( ThermalScatteringTable&& base ) {

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
   *  @param[in] header    the header for the table
   *  @param[in] za        the list of ZA values
   *  @param[in] itie      the inelastic thermal scattering cross section block
   *  @param[in] itxe      the inelastic thermal scattering angular distribution block
   *  @param[in] itce      the coherent elastic thermal scattering cross section block
   *  @param[in] itca      the coherent elastic thermal scattering angular distribution block
   *  @param[in] itcei     the incoherent elastic thermal scattering cross section block
   *  @param[in] itcai     the incoherent elastic thermal scattering angular distribution block
   */
  ThermalScatteringTable( HeaderVariant header, std::vector< unsigned int > za,
                          thermal::ITIE itie, thermal::ITXE itxe,
                          std::optional< thermal::ITCE > itce,
                          std::optional< thermal::ITCA > itca,
                          std::optional< thermal::ITCEI > itcei,
                          std::optional< thermal::ITCAI > itcai ) :
    ThermalScatteringTable(
        Table( std::move( header ),
               generateData( std::move( za ),
                             std::move( itie ), std::move( itxe ),
                             std::move( itce ), std::move( itca ),
                             std::move( itcei ), std::move( itcai ) ) ) ) {}

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
   *  @brief Return the inelastic scattering mode
   */
  unsigned int IDPNI() const { return this->data().NXS(2); }

  /**
   *  @brief Return the inelastic scattering mode
   */
  unsigned int inelasticScatteringMode() const { return this->IDPNI(); }

  /**
   *  @brief Return the inelastic dimensioning parameter
   *
   *  For IFENG < 2, the inelastic dimensioning parameter will be equal to NC - 1,
   *  for IFENG = 2 this will be equal to NC + 1
   */
  unsigned int NIL() const { return this->data().NXS(3); }

  /**
   *  @brief Return the inelastic dimensioning parameter
   *
   *  For IFENG < 2, the inelastic dimensioning parameter will be equal to NC - 1,
   *  for IFENG = 2 this will be equal to NC + 1
   */
  unsigned int inelasticDimensioningParameter() const { return this->NIL(); }

  /**
   *  @brief Return the number of inelastic outgoing energies
   */
  unsigned int NIEB() const { return this->data().NXS(4); }

  /**
   *  @brief Return the number of inelastic outgoing energies
   */
  unsigned int numberInelasticOutgoingEnergies() const { return this->NIEB(); }

  /**
   *  @brief Return the elastic scattering mode
   */
  unsigned int IDPNC() const { return this->data().NXS(5); }

  /**
   *  @brief Return the elastic scattering mode
   */
  unsigned int elasticScatteringMode() const { return this->IDPNC(); }

  /**
   *  @brief Return the first elastic dimensioning parameter
   *
   *  The elastic dimensioning parameter is equal to NC - 1
   */
  int NCL() const { return this->data().NXS(6); }

  /**
   *  @brief Return the first elastic dimensioning parameter
   *
   *  The elastic dimensioning parameter is equal to NC - 1
   */
  int firstElasticDimensioningParameter() const { return this->NCL(); }

  /**
   *  @brief Return the second elastic dimensioning parameter
   *
   *  The elastic dimensioning parameter is equal to NC - 1
   */
  int NCLI() const { return this->data().NXS(8); }

  /**
   *  @brief Return the second elastic dimensioning parameter
   *
   *  The elastic dimensioning parameter is equal to NC - 1
   */
  int secondElasticDimensioningParameter() const { return this->NCLI(); }

  /**
   *  @brief Return the secondary energy mode
   */
  unsigned int IFENG() const { return this->data().NXS(7); }

  /**
   *  @brief Return the secondary energy mode
   */
  unsigned int secondaryEnergyMode() const { return this->IFENG(); }

  // JXS information

  // XSS blocks

  /**
   *  @brief Return the inelastic thermal scattering cross section block
   */
  const thermal::ITIE& ITIE() const { return this->itie_; }

  /**
   *  @brief Return the inelastic thermal scattering cross section block
   */
  const thermal::ITIE& inelasticCrossSectionBlock() const {

    return this->ITIE();
  }

  /**
   *  @brief Return the inelastic thermal scattering angular distribution block
   */
  const thermal::ITXE& ITXE() const { return this->itxe_; }

  /**
   *  @brief Return the inelastic thermal scattering angular distribution block
   */
  const thermal::ITXE& inelasticAngularDistributionBlock() const {

    return this->ITXE();
  }

  /**
   *  @brief Return the coherent elastic thermal scattering cross section block
   */
  const std::optional< thermal::ITCE >& ITCE() const { return this->itce_; }

  /**
   *  @brief Return the coherent elastic thermal scattering cross section block
   */
  const std::optional< thermal::ITCE >& coherentElasticCrossSectionBlock() const {

    return this->ITCE();
  }

  /**
   *  @brief Return the coherent elastic thermal scattering angular distribution
   *         block
   */
  const std::optional< thermal::ITCA >& ITCA() const { return this->itca_; }

  /**
   *  @brief Return the coherent elastic thermal scattering angular distribution
   *         block
   */
  const std::optional< thermal::ITCA >& coherentElasticAngularDistributionBlock() const {

    return this->ITCA();
  }

  /**
   *  @brief Return the incoherent elastic thermal scattering cross section block
   */
  const std::optional< thermal::ITCEI >& ITCEI() const { return this->itcei_; }

  /**
   *  @brief Return the incoherent elastic thermal scattering cross section block
   */
  const std::optional< thermal::ITCEI >& incoherentElasticCrossSectionBlock() const {

    return this->ITCEI();
  }

  /**
   *  @brief Return the incoherent elastic thermal scattering angular distribution
   *         block
   */
  const std::optional< thermal::ITCAI >& ITCAI() const { return this->itcai_; }

  /**
   *  @brief Return the incoherent elastic thermal scattering angular distribution
   *         block
   */
  const std::optional< thermal::ITCAI >& incoherentElasticAngularDistributionBlock() const {

    return this->ITCAI();
  }
};

} // ACEtk namespace
} // njoy namespace

#endif
