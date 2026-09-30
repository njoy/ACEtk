#ifndef NJOY_ACETK_TABLE
#define NJOY_ACETK_TABLE

// system includes
#include <cctype>
#include <istream>
#include <regex>
#include <string>
#include <variant>
#include <vector>

// other includes
#include "tools/Log.hpp"
#include "tools/std20/views.hpp"
#include "tools/disco.hpp"
#include "ACEtk/State.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief The generic ACE table
 *
 *  The Table class represents the generic ACE table, which can be of any type
 *  (e.g. continuous energy, thermal scattering, etc.). It contains a header
 *  and the actual data of the table (the data being the IZAW, NXS, JXS and XSS
 *  arrays).
 */
class Table {

public:

  #include "ACEtk/Table/Header.hpp"
  #include "ACEtk/Table/Header201.hpp"
  #include "ACEtk/Table/Data.hpp"

  using HeaderVariant = std::variant< Header, Header201 >;

private:

  Data data_;
  HeaderVariant header_;

  /* auxiliary functions */

  template< typename Iterator >
  static std::string readVersion( State< Iterator >& state ) {

    using namespace njoy::tools::disco;

    // read a line, reset state
    using Line = Record< Character< 80 > >;
    std::string line;
    auto begin = state.position;
    Line::read( state.position, state.end, line );
    state.position = begin;

    // extract the first substring
    std::istringstream input( line );
    std::string version;
    input >> version;
    return version;
  }

  template< typename Iterator >
  static HeaderVariant parse( State< Iterator >& state ) {

    std::string version = readVersion( state );
    if ( ( version == "2.0.0" ) || ( version == "2.0.1" ) ) {

      return Header201( state );
    }
    else{

      return Header( state );
    }
  }

protected:

  /* constructor */

  /**
   *  @brief Private constructor
   */
  template< typename Iterator >
  Table( HeaderVariant&& header, State< Iterator >& state ) :
    Table( std::move( header ), Data( state ) ){}

public:

  /**
   *  @brief Constructor
   *
   *  @param[in] header   the header information
   *  @param[in] data     the ACE data
   */
  Table( HeaderVariant&& header, Data&& data ) :
    data_( std::move(data) ), header_( std::move(header) ){}

  Table( const Table& ) = default;
  Table( Table&& ) = default;

  Table& operator=( const Table& ) = default;
  Table& operator=( Table&& ) = default;

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator   a buffer iterator
   *
   *  @param[in] state   the buffer state
   */
  template< typename Iterator >
  Table( State< Iterator >& state )
    try: Table( parse( state ), state ) {}
    catch( std::exception& e ) {

      Log::info("Error while constructing ACE Table");
      throw e;
    }

  /**
   *  @brief Constructor (from a buffer)
   *
   *  @tparam Iterator   a buffer iterator
   *
   *  @param[in] state   the buffer state
   */
  template< typename Iterator >
  Table( State< Iterator >&& state ) : Table( state ) {}

  /**
   *  @brief Return the header information
   */
  const auto& header() const { return this->header_; }

  /**
   *  @brief Return the data arrays
   */
  const auto& data() const { return this->data_; }

  /**
   *  @brief Return the header information
   */
  auto& header() { return this->header_; }

  /**
   *  @brief Return the data arrays
   */
  auto& data() { return this->data_; }

  /**
   *  @brief Print the table
   *
   *  @param[in] ostream   the output stream to write to
   */
  template< typename Ostream >
  void print( Ostream& ostream ) const {

    std::visit( [&ostream] ( const auto& header ) { header.print( ostream ); },
                this->header_ );
    this->data_.print( ostream );
  }
};

} // ACEtk namespace
} // njoy namespace

#endif
