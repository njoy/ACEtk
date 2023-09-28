#ifndef NJOY_ACETK_FROMFILE
#define NJOY_ACETK_FROMFILE

// system includes
#include <string>
#include <fstream>

// other includes
#include "Log.hpp"
#include "ACEtk/Table.hpp"

namespace njoy {
namespace ACEtk {

  /**
   *  @brief Utility function to read the content of a file to a string
   *
   *  @param[in] filename   the file name
   */
  inline auto readContentFromFile( const std::string& filename ) {

    std::string content;
    std::ifstream in( filename,
                      std::ios::in | std::ios::binary | std::ios::ate );
    if ( not in ) {

      Log::error( "Could not open file \'{}\'", filename );
      throw std::exception();
    }

    const auto file_size = in.tellg();
    in.seekg( 0, std::ios::beg );
    content.resize( file_size / sizeof( char ) );
    in.read( content.data(), file_size );
    return content;
  }

  /**
   *  @brief Factory function to make an ACE table from a file
   *
   *  If this function is applied to a concatenated ACE file, only the first
   *  table is read.
   *
   *  @param[in] filename   the file name
   */
  inline auto fromFile( const std::string& filename ) {

    std::string content = readContentFromFile( filename );

    using Iterator = decltype( content.begin() );
    State< Iterator > state{ 1, content.begin(), content.end() };

    return njoy::ACEtk::Table( state );
  }

  /**
   *  @brief Factory function to make ACE tables from a concatenated file
   *
   *  @param[in] filename   the file name
   */
  inline auto fromConcatenatedFile( const std::string& filename ) {

    std::string content = readContentFromFile( filename );

    using Iterator = decltype( content.begin() );
    State< Iterator > state{ 1, content.begin(), content.end() };

    std::vector< Table > tables;
    while ( state.position != state.end ) {

      tables.emplace_back( state );
    }

    return tables;
  }

} // ENDFtk namespace
} // njoy namespace

#endif
