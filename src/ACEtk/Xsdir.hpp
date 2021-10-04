#ifndef NJOY_ACETK_XSDIR
#define NJOY_ACETK_XSDIR

// system includes
#include <vector>

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
  std::vector< XsdirEntry > entries_;

  /* auxiliary functions */

public:

  /* constructor */
  #include "ACEtk/Xsdir/src/ctor.hpp"

  /**
   *  @brief Return the optional datapath
   */
  const std::optional< std::string >& dataPath() const {

    return this->datapath_;
  }

  /**
   *  @brief Return the xsdir entries
   */
  const std::vector< XsdirEntry >& entries() const { return this->entries_; }

  /**
   *  @brief Return the xsdir entry for a given ZAID
   */
  const XsdirEntry& entry( const std::string& zaid ) const {

    auto iter = std::find_if( this->entries().begin(), this->entries().end(),
                              [&] ( const auto& entry )
                                  { return entry.ZAID() == zaid; } );
    if ( iter != this->entries().end() ) {

      return *iter;
    }
    else {

      Log::error( "The requested ZAID is not present: ", zaid );
      throw std::exception();
    }
  }
};

} // ACEtk namespace
} // njoy namespace

#endif
