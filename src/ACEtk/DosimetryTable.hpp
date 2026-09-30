#ifndef NJOY_ACETK_DOSIMETRYYTABLE
#define NJOY_ACETK_DOSIMETRYYTABLE

// system includes

// other includes
#include "ACEtk/Table.hpp"
#include "ACEtk/continuous/ReactionNumberBlock.hpp"
#include "ACEtk/dosimetry/CrossSectionBlock.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The dosimetry ACE table
 *
 *  The DosimetryTable class represents the ACE table for dosimetry data.
 */
class DosimetryTable : protected Table {

  /* fields */

  continuous::MTR mtr_;
  dosimetry::SIGD sig_;

  /* auxiliary functions */

  void generateBlocks() {

    auto begin = this->data().XSS().begin();
    auto mtr = begin + this->data().JXS(3) - 1;
    auto lsig = begin + this->data().JXS(6) - 1;
    auto sig = begin + this->data().JXS(7) - 1;
    auto end = this->data().XSS().end();

    this->mtr_ = continuous::MTR( mtr, lsig, this->NTR() );
    this->sig_ = dosimetry::SIGD( lsig, sig, end, this->NTR() );
  }

  Data generateData( unsigned int z, unsigned int a,
                     continuous::MTR&& mtr, dosimetry::SIGD&& sigd ) {

    std::array< int32_t, 16 > iz;
    std::array< double, 16 > aw;
    std::array< int64_t, 16 > nxs;
    std::array< int64_t, 32 > jxs;
    iz.fill( 0 );
    aw.fill( 0. );
    nxs.fill( 0 );
    jxs.fill( 0 );
    std::vector< double > xss;

    // verify some stuff:
    //  - MTR and SIGD have the same NTR
    if ( mtr.NTR() != sigd.NTR() ) {

      Log::error( "Inconsistent NTR between the MTR and SIGD block" );
      Log::info( "MTR NTR value = {}", mtr.NTR() );
      Log::info( "SIGD NTR value = {}", sigd.NTR() );
      throw std::exception();
    }

    // generate the xss array and set the locators in the jxs array as we go
    jxs[0] = 1;
    jxs[2] = 1;
    xss.insert( xss.end(), mtr.begin(), mtr.end() );
    jxs[5] = xss.size() + 1;
    jxs[6] = xss.size() + mtr.NTR() + 1;
    xss.insert( xss.end(), sigd.begin(), sigd.end() );
    jxs[21] = xss.size();

    // set the nxs values for the dosimetry table
    // NXS(1) = length
    // NXS(2) = za
    // NXS(4) = NTR
    nxs[0] = xss.size();
    nxs[1] = z * 1000 + a;
    nxs[3] = mtr.NTR();

    return { std::move( iz ), std::move( aw ),
             std::move( nxs ), std::move( jxs ), std::move( xss ) };
  }

  void verifyType() {

    char type = this->ZAID().back();
    if ( ( type != 'y' ) ) {


      Log::error( "The ZAID given in the ACE table ({}) does not appear to be a "
                  "dosimetry type (y)", this->ZAID() );
      throw std::exception();
    }
  }

public:

  /**
   *  @brief Copy constructor using a generic table
   *
   *  @param[in] table    the generic table to be copied
   */
  DosimetryTable( const Table& table ): Table( table ) {

    this->verifyType();
    this->generateBlocks();
  }

  /**
   *  @brief Move constructor using a generic table
   *
   *  @param[in] table    the generic table to be moved
   */
  DosimetryTable( Table&& table ): Table( std::move( table ) ) {

    this->verifyType();
    this->generateBlocks();
  }

  /**
   *  @brief Copy constructor using a dosimetry table
   *
   *  @param[in] table    the dosimetry table to be copied
   */
  DosimetryTable( const DosimetryTable& dostable ) :
    Table( dostable ) {

    this->verifyType();
    this->generateBlocks();
  }

  /**
   *  @brief Move constructor using a dosimetry table
   *
   *  @param[in] table    the dosimetry table to be moved
   */
  DosimetryTable( DosimetryTable&& dostable ) :
    Table( std::move( dostable ) ) {

    this->verifyType();
    this->generateBlocks();
  }

  /**
   *  @brief Copy assignment using a dosimetry table
   *
   *  @param[in] table    the dosimetry table to be copied
   */
  DosimetryTable& operator=( const DosimetryTable& base ) {

    if ( this != &base ) {

      Table::operator=( base );
      this->verifyType();
      this->generateBlocks();
    }
    return *this;
  }

  /**
   *  @brief Move assignment using a dosimetry table
   *
   *  @param[in] table    the dosimetry table to be moved
   */
  DosimetryTable& operator=( DosimetryTable&& base ) {

    if ( this != &base ) {

      Table::operator=( std::move( base ) );
      this->verifyType();
      this->generateBlocks();
    }
    return *this;
  }

  /**
   *  @brief Constructor
   *
   *  @param[in] z         the Z number of the nuclide
   *  @param[in] a         the A number of the nuclide
   *  @param[in] header    the header for the table
   *  @param[in] mtr       the reaction number block
   *  @param[in] sigd      the cross section data block
   */
  DosimetryTable( unsigned int z, unsigned int a,
                  HeaderVariant header, continuous::MTR mtr, dosimetry::SIGD sigd ) :
    DosimetryTable( Table( std::move( header ),
                           generateData( z, a, std::move( mtr ),
                                         std::move( sigd ) ) ) ) {}

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
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int NTR() const { return this->data().NXS(4); }

  /**
   *  @brief Return the number of available reactions (excluding elastic)
   */
  unsigned int numberReactions() const { return this->NTR(); }

  // JXS information

  // XSS blocks

  /**
   *  @brief Return the reaction number block
   */
  const continuous::MTR& MTR() const { return this->mtr_; }

  /**
   *  @brief Return the reaction number block
   */
  const continuous::MTR& reactionNumberBlock() const { return this->MTR(); }

  /**
   *  @brief Return the cross section block
   */
  const dosimetry::SIGD& SIGD() const { return this->sig_; }

  /**
   *  @brief Return the cross section block
   */
  const dosimetry::SIGD& crossSectionBlock() const { return this->SIGD(); }
};

} // ACEtk namespace
} // njoy namespace

#endif
