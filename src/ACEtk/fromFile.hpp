#ifndef NJOY_ACETK_FROMFILE
#define NJOY_ACETK_FROMFILE

// system includes
#include <string>
#include <fstream>

// other includes
#include "Log.hpp"
#include "ACEtk.hpp"

namespace njoy {
namespace ACEtk {

  /**
   *  @brief Factory function to make an ACE table from a file
   *
   *  @param[in] filename   the file name
   */
  inline auto fromFile( const std::string& filename ) {

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
    in.read( &( content[ 0 ] ), file_size );
    return njoy::ACEtk::Table( content );
  }

} // ENDFtk namespace
} // njoy namespace

#endif
