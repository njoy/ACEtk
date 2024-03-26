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
  #include "ACEtk/Xsdir/src/parse.hpp"
  #include "ACEtk/Xsdir/src/indices.hpp"

public:

  /* constructor */
  #include "ACEtk/Xsdir/src/ctor.hpp"
  #include "ACEtk/Xsdir/src/fromFile.hpp"

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

  #include "ACEtk/Xsdir/src/print.hpp"
};

#include "ACEtk/Xsdir/src/stream.hpp"

} // ACEtk namespace
} // njoy namespace

#endif
