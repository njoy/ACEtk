#ifndef NJOY_ACETK_XSDIRENTRY
#define NJOY_ACETK_XSDIRENTRY

// system includes
#include <algorithm>
#include <iomanip>
#include <string>
#include <optional>
#include <sstream>

// other includes
#include "tools/Log.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief An entry in an xsdir file
 *
 *  An xsdir entry consists of either 7, 10 or 11 values:
 *    - the zaid
 *    - the atomic mass ratio
 *    - file name
 *    - an access path (undefined path if "0")
 *    - a file type (1 for ascii, 2 for binary)
 *    - the starting address or line number
 *    - the table length (number of words in the XSS array)
 *    - the length of a record (0 for ascii files)
 *    - the number of entries (0 for ascii files)
 *    - the temperature in MeV
 *    - ptable if the table has a probability table for the URR
 */
class XsdirEntry {

  /* fields */

  std::string zaid_;
  double awr_;
  std::string filename_;
  std::optional< std::string > access_;
  unsigned int filetype_;
  unsigned int address_;
  unsigned int tablelength_;
  std::optional< unsigned int > recordlength_;
  std::optional< unsigned int > entries_;
  std::optional< double > temperature_;
  bool ptable_;

  /* auxiliary functions */

  static void trim( std::string& string ) {

    // useful lambdas
    auto isNotSpace = [] ( const auto& c ) { return !std::isspace( c ); };

    // trim front and back whitespace
    string.erase( string.begin(),
                  std::find_if( string.begin(), string.end(), isNotSpace ) );
    string.erase( std::find_if( string.rbegin(), string.rend(), isNotSpace ).base(),
                  string.end() );
  }

  static std::string getline( std::istream& in ) {

    // a line is a comment line if the first character on it is '#'
    auto isCommentLine = [] ( const auto& line ) {

      if ( line.size() > 0 ) {

        return line[0] == '#' ? true : false;
      }
      return false;
    };

    std::string current;

    std::getline( in, current );
    while ( isCommentLine( current ) ) {

      std::getline( in, current );
    }

    // trim the line and return it
    trim( current );
    return current;
  }

  static XsdirEntry parse( std::istream& in ) {

    auto position = in.tellg();

    // read a line and verify for continue on the next line
    std::string line;
    std::string next;

    line = getline( in );
    while ( line.back() == '+' ) {

      line.back() = ' ';
      next = getline( in );
      line += next;
    }

    if ( !in.eof() ) {

      // data to be read
      std::string zaid;
      double awr;
      std::string filename;
      std::string access;
      unsigned int filetype;
      unsigned int address;
      unsigned int length;
      unsigned int recordlength = 0;
      unsigned int entries = 0;
      double temperature = 0.;
      bool ptable = false;

      // read minimum of 7 entries, then read 3 more and a string after that
      std::istringstream xsdir( line );
      xsdir >> zaid >> awr >> filename >> access >> filetype >> address >> length;
      if ( !xsdir.fail() ) {

        // read the next 3 or 4 entries
        if ( xsdir >> recordlength ) {

          xsdir >> entries >> temperature;
          if ( !xsdir.fail() ) {

            xsdir >> next;
            if ( xsdir.fail() ) {

              xsdir.clear();
            }
            else {

              if ( next == "ptable" ) {

                ptable = true;
              }
              else {

                xsdir.setstate( std::ios::failbit );
              }
            }
          }
        }
        else {

          xsdir.clear();
        }
      }

      if ( xsdir.fail() ) {

        in.clear();
        in.seekg( position );
        in.setstate( std::ios::failbit );

        Log::error( "Something went wrong while reading an xsdir entry" );
        throw std::exception();
      }

      return XsdirEntry( std::move( zaid ), awr, std::move( filename ),
                         filetype, address, length,
                         access == "0"
                           ? std::nullopt
                           : std::optional< std::string >( std::move( access ) ),
                         recordlength == 0
                           ? std::nullopt
                           : std::optional< unsigned int >( recordlength ),
                         entries == 0
                           ? std::nullopt
                           : std::optional< unsigned int >( entries ),
                         temperature == 0
                           ? std::nullopt
                           : std::optional< double >( temperature ),
                         ptable );
    }
    else {

      Log::error( "Expected an additional line but found the end of stream" );
      throw std::exception();
    }
  }

public:

  /* constructor */

  XsdirEntry() = default;
  XsdirEntry( const XsdirEntry& ) = default;
  XsdirEntry( XsdirEntry&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] zaid            the zaid
   *  @param[in] awr             the atomic weight ratio (to the neutron mass)
   *  @param[in] filename        the file name
   *  @param[in] filetype        the file type
   *  @param[in] address         the starting address or line
   *  @param[in] length          the length of the file
   *  @param[in] access          the access path for the file (optional)
   *  @param[in] recordlength    the length of a record (optional)
   *  @param[in] entries         the number of entries per record (optional)
   *  @param[in] temperature     the temperature of the file (optional)
   *  @param[in] ptable          flag to indicate if a probability table is present
   */
  XsdirEntry( std::string zaid, double awr, std::string filename,
              unsigned int filetype, unsigned int address, unsigned int length,
              std::optional< std::string > access = std::nullopt,
              std::optional< unsigned int > recordlength = std::nullopt,
              std::optional< unsigned int > entries = std::nullopt,
              std::optional< double > temperature = std::nullopt,
              bool ptable = false ) :
    zaid_( std::move( zaid ) ),  awr_( awr ), filename_( std::move( filename ) ),
    access_( std::move( access ) ), filetype_( filetype ), address_( address ),
    tablelength_( length ), recordlength_( std::move( recordlength ) ),
    entries_( std::move( entries ) ), temperature_( std::move( temperature ) ),
    ptable_( ptable ) {}

  /**
   *  @brief Constructor (ASCII file)
   *
   *  @param[in] zaid            the zaid
   *  @param[in] awr             the atomic weight ratio (to the neutron mass)
   *  @param[in] filename        the file name
   *  @param[in] address         the starting address or line
   *  @param[in] length          the length of the file
   *  @param[in] temperature     the temperature of the file (optional)
   *  @param[in] ptable          flag to indicate if a probability table is present
   *  @param[in] access          the access path for the file (optional)
   */
  XsdirEntry( std::string zaid, double awr, std::string filename,
              unsigned int address, unsigned int length,
              std::optional< double > temperature = std::nullopt,
              bool ptable = false,
              std::optional< std::string > access = std::nullopt ) :
    XsdirEntry( std::move( zaid ), awr, std::move( filename ),
                1, address, length, std::move( access ),
                std::nullopt, std::nullopt, std::move( temperature ), ptable ) {}


  /**
   *  @brief Constructor (from a stream)
   *
   *  @param[in] in   the input stream
   */
  XsdirEntry( std::istream& in )
    try : XsdirEntry( parse( in ) ) {}
    catch( std::exception& e ) {

      Log::info( "Error while constructing an xsdir entry" );
      throw e;
    }

  XsdirEntry& operator=( const XsdirEntry& ) = default;
  XsdirEntry& operator=( XsdirEntry&& right ) = default;

  /**
   *  @brief Return the ZAID of the table
   */
  const std::string& ZAID() const { return this->zaid_; }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double AWR() const { return this->awr_; }

  /**
   *  @brief Return the atomic weight ratio (with respect to the neutron mass)
   */
  double atomicWeightRatio() const { return this->AWR(); }

  /**
   *  @brief Return the file name and path
   */
  const std::string& fileName() const { return this->filename_; }

  /**
   *  @brief Return the access route
   */
  const std::optional< std::string >& accessRoute() const { return this->access_; }

  /**
   *  @brief Return the file type
   */
  unsigned int fileType() const { return this->filetype_; }

  /**
   *  @brief Return the table address or starting line
   */
  unsigned int address() const { return this->address_; }

  /**
   *  @brief Return the table length
   */
  unsigned int tableLength() const { return this->tablelength_; }

  /**
   *  @brief Return the record length (used for binary files only)
   */
  const std::optional< unsigned int >& recordLength() const {

    return this->recordlength_;
  }

  /**
   *  @brief Return the number of entries per record (used for binary files only)
   */
  const std::optional< unsigned int >& entriesPerRecord() const {

    return this->entries_;
  }

  /**
   *  @brief Return the temperature of the table (if it is defined)
   */
  const std::optional< double >& temperature() const {

    return this->temperature_;
  }

  /**
   *  @brief Return the flag indicating whether or not a probability table is
   *         present
   */
  bool ptable() const {

    return this->ptable_;
  }

  /**
   *  @brief Print the entry
   *
   *  @param[in] ostream   the output stream to write to
   */
  void print( std::ostream& ostream ) const {

    // print the entry
    std::ostringstream out;
    out << std::right;
    out << std::setw( 10 ) << this->ZAID();
    out << std::setw( 13 )<< std::fixed << std::setprecision( 6 ) << this->AWR();
    out << ' ' << this->fileName();
    out << ' ' << ( this->accessRoute() ? this->accessRoute().value() : "0" );
    out << ' ' << this->fileType();
    out << ' ' << this->address();
    out << ' ' << this->tableLength();
    if ( this->recordLength() && this->entriesPerRecord() ) {

      out << ' ' << this->recordLength().value()
          << ' ' << this->entriesPerRecord().value();
    }
    else {

      if ( this->temperature() || this->ptable() ) {

        out << " 0 0";
      }
    }
    if ( this->temperature() ){

      out << std::setw( 13 ) << std::scientific << std::setprecision( 6 )
          << this->temperature().value();
    }
    else {

      if ( this->ptable() ) {

        out << " 0";
      }
    }
    out << ( this->ptable() ? " ptable" : "" );
    out << std::endl;

    // check size and split as required (we assume we have to split more than once)
    std::string entry = out.str();
    if ( entry.size() > 100 ) {

      auto size = entry.size();
      while ( size > 100 ) {

        auto begin = entry.rbegin();
        auto iter = begin + size;
        while ( std::distance( begin, iter ) > 100 ) {

          begin = std::find( begin, iter, ' ' ) + 1; // move past the space
        }
        auto pos = std::distance( begin, entry.rend() );
        entry.insert( pos, " +\n    " );
        size = entry.size() - ( pos + 3 ); // remaining characters after the \n
      }
    }

    ostream << entry;
  }
};

/**
 *  @brief operator>> for xsdir entries
 *
 *  @param[in] in       the input stream
 *  @param[in] entry    the xsdir entry
 *
 *  @return the input stream
 */
inline std::istream &operator>>( std::istream& in, XsdirEntry& entry ) {

  try {

    XsdirEntry temp( in );
    entry = std::move( temp );
  }
  catch ( ... ) {

    // mimic standard library behaviour: stream position has not changed and
    // stream state is in fail
    // nothing to do here: the constructor handles the stream state
  }

  return in;
}

/**
 *  @brief operator<< for xsdir entries
 *
 *  @param[in] in       the output stream
 *  @param[in] entry    the xsdir entry
 *
 *  @return the input stream
 */
inline std::ostream &operator<<( std::ostream& out, const XsdirEntry& entry ) {

  entry.print( out );
  return out;
}

} // ACEtk namespace
} // njoy namespace

#endif
