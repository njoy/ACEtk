#ifndef NJOY_ACETK_XSDIR
#define NJOY_ACETK_XSDIR

// system includes
#include <algorithm>
#include <map>
#include <vector>
#include <fstream>
#include <locale>

// other includes
#include "ACEtk/XsdirEntry.hpp"

namespace njoy {
namespace ACEtk {

/**
 *  @class
 *  @brief An xsdir file
 *
 *  An xsdir file consists of the following:
 *    - an optional data path
 *    - a set of atomic weight values
 *    - a set of xsdir entries
 */
class Xsdir {

  /* fields */

  std::optional< std::string > datapath_;
  std::map< unsigned int, double > awr_;
  std::vector< XsdirEntry > entries_;
  std::unordered_map< std::string, std::size_t > indices_;

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

  static void toLowerCase( std::string& string ) {

    std::transform( string.begin(), string.end(), string.begin(),
                    [] ( const auto& c ) { return std::tolower( c ); } );
  }

  static void trimToLowerCase( std::string& string ) {

    trim( string );
    toLowerCase( string );
  }

  static std::string getline( std::istream& in, std::istream::pos_type& position ) {

    // a line is a comment line if the first character on it is '#'
    auto isCommentLine = [] ( const auto& line ) {

      if ( line.size() > 0 ) {

        return line[0] == '#';
      }
      return false;
    };

    std::string current;

    // read over all comment lines and empty lines
    position = in.tellg();
    std::getline( in, current );
    while ( !in.eof() && ( isCommentLine( current ) || current.size() == 0 ) ) {

      position = in.tellg();
      std::getline( in, current );
    }

    // trim the line and return it
    trim( current );
    return current;
  }

  static Xsdir parse( std::istream& in ) {

    auto position = in.tellg();
    std::string current;

    // go to the next line
    current = getline( in, position );

    // verify for the presence of a datapath
    std::optional< std::string > datapath = std::nullopt;
    if ( current.size() != 0 ) {

      std::string path = current.substr( 0, 8 );
      toLowerCase( path );
      if ( path == "datapath" ) {

        current = current.erase( 0, 8 );
        trim( current );
        if ( current.size() != 0 ) {

          if ( current[0] == '=' ) {

            current.erase( 0, 1 );
            if ( current.size() != 0 ) {

              datapath = current;
            }
          }
        }

        current = getline( in, position );
        toLowerCase( current );
      }
    }

    // verify for the atomic weight ratios
    if ( current != "atomic weight ratios" ) {

      in.clear();
      in.seekg( position );
      in.setstate( std::ios::failbit );

      Log::error( "Expected \'atomic weight ratios\' but found \'{}\'", current );
      throw std::exception();
    }

    // read ZA, AWR pairs
    unsigned int za;
    double awr;
    std::map< unsigned int, double > ratios;
    current = getline( in, position );
    while ( current != "directory" ) {

      //! @todo we do not verify duplicates or completeness
      std::istringstream input( current );
      while ( input >> za >> awr ) {

        ratios[ za ] = awr;
      }

      // read the next line
      current = getline( in, position );
      toLowerCase( current );
      if ( in.fail() ) {

        in.clear();
        in.seekg( position );
        in.setstate( std::ios::failbit );

        Log::error( "Unexpected error while reading atomic weights" );
        throw std::exception();
      }
    }

    // read entries from this point forward
    XsdirEntry entry;
    std::vector< XsdirEntry > entries;
    while ( in >> entry ) {

      entries.emplace_back( std::move( entry ) );

      // check if there is another entry after this one
      current = getline( in, position );
      if ( !in.eof() ) {

        in.clear();
        in.seekg( position );
      }
      else {

        break;
      }
    }

    if ( !in.eof() ) {

      in.clear();
      in.seekg( position );
      in.setstate( std::ios::failbit );

      Log::error( "Something went wrong while reading an xsdir entry" );
      if ( entries.size() > 0 ) {

        Log::error( "Last entry read: {}", entries.back().ZAID() );
      }
      throw std::exception();
    }

    return Xsdir( std::move( ratios ), std::move( entries ),
                  std::move( datapath ) );
  }

  static std::unordered_map< std::string, std::size_t >
  indices( const std::vector< XsdirEntry > entries ) {

    std::unordered_map< std::string, std::size_t > indices;
    for ( unsigned int i = 0; i < entries.size(); ++i ) {

      indices[ entries[i].ZAID() ] = i;
    }
    return indices;
  }

public:

  /* constructor */

  Xsdir() = default;
  Xsdir( const Xsdir& ) = default;
  Xsdir( Xsdir&& ) = default;

  /**
   *  @brief Constructor
   *
   *  @param[in] ratios     the atomic weight ratios
   *  @param[in] entries    the file name
   *  @param[in] datapath   the optional datapath
   */
  Xsdir( std::map< unsigned int, double > ratios,
         std::vector< XsdirEntry > entries,
         std::optional< std::string > datapath = std::nullopt ) :
    datapath_( std::move( datapath ) ), awr_( std::move( ratios ) ),
    entries_( std::move( entries ) ), indices_( indices( entries_ ) ) {}

  /**
   *  @brief Constructor (from a stream)
   *
   *  @param[in] in   the input stream
   */
  Xsdir( std::istream& in )
    try : Xsdir( parse( in ) ) {}
    catch( std::exception& e ) {

      Log::info( "Error while constructing an xsdir file" );
      throw e;
    }

  Xsdir& operator=( const Xsdir& ) = default;
  Xsdir& operator=( Xsdir&& right ) = default;

  /**
   *  @brief Factory function to make an xsdir from a file
   *
   *  @param[in] filename   the file name
   */
  static auto fromFile( const std::string& filename ) {

    std::ifstream in( filename );
    if ( not in ) {

      njoy::Log::error( "Could not open file \'{}\'", filename );
      throw std::exception();
    }
    return Xsdir( in );
  }

  /**
   *  @brief Return the optional datapath
   */
  const std::optional< std::string >& dataPath() const {

    return this->datapath_;
  }

  /**
   *  @brief Return the atomic weight ratios
   */
  const std::map< unsigned int, double >& atomicWeightRatios() const {

    return this->awr_;
  }

  /**
   *  @brief Return the atomic weight ratio for a given za
   */
  double atomicWeightRatio( unsigned int za ) const {

    try {

      return this->awr_.at( za );
    }
    catch ( ... ) {

      Log::error( "The requested ZA is not present in the atomic weight ratios: {}", za );
      throw std::exception();
    }
  }

  /**
   *  @brief Return the xsdir entries
   */
  const std::vector< XsdirEntry >& entries() const { return this->entries_; }

  /**
   *  @brief Return the xsdir entry for a given ZAID
   */
  const XsdirEntry& entry( const std::string& zaid ) const {

    auto iter = this->indices_.find( zaid );
    if ( iter != this->indices_.end() ) {

      return this->entries()[ iter->second ];
    }
    else {

      Log::error( "The requested ZAID is not present: {}", zaid );
      throw std::exception();
    }
  }

  /**
   *  @brief Print the xsdir
   *
   *  @param[in] ostream   the output stream to write to
   */
  void print( std::ostream& ostream ) const {

    // print the atomic weight ratios
    if ( this->dataPath() ) {

      ostream << "datapath=" << this->dataPath().value();
    }
    ostream << std::endl;

    // print the atomic weight ratios
    ostream << "atomic weight ratios" << std::endl;
    int count = -1;
    for ( const auto& entry : this->atomicWeightRatios() ) {

      if ( entry.first == 1 || entry.first%1000 == 0 ) {

        if ( entry.first != 1 ) {

          ostream << std::endl;
        }
        count = -1;
      }

      if ( count != 0 && count%3 == 0 ) {

        ostream << std::endl << std::setw( 21 ) << ' ';
      }

      ostream << std::right;
      ostream << std::setw( 8 ) << entry.first;
      ostream << std::setw( 13 )<< std::fixed << std::setprecision( 8 ) << entry.second;

      ++count;
    }
    ostream << std::endl;

    // print the directory
    ostream << std::endl;
    ostream << "directory" << std::endl;
    for ( const auto& entry : this->entries() ) {

      ostream << entry;
    }
  }
};

/**
 *  @brief operator>> for an xsdir
 *
 *  @param[in] in       the input stream
 *  @param[in] entry    the xsdir
 *
 *  @return the input stream
 */
inline std::istream &operator>>( std::istream& in, Xsdir& xsdir ) {

  try {

    Xsdir temp( in );
    xsdir = std::move( temp );
  }
  catch ( ... ) {

    // mimic standard library behaviour: stream position has not changed and
    // stream state is in fail
    // nothing to do here: the constructor handles the stream state
  }

  return in;
}

/**
 *  @brief operator<< for an xsdir
 *
 *  @param[in] in       the output stream
 *  @param[in] xsdir    the xsdir
 *
 *  @return the input stream
 */
inline std::ostream &operator<<( std::ostream& out, Xsdir& xsdir ) {

  xsdir.print( out );
  return out;
}

} // ACEtk namespace
} // njoy namespace

#endif
