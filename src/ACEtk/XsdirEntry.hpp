#ifndef NJOY_ACETK_XSDIRENTRY
#define NJOY_ACETK_XSDIRENTRY

// system includes
#include <algorithm>
#include <iomanip>
#include <string>
#include <optional>
#include <sstream>

// other includes
#include "Log.hpp"

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
  #include "ACEtk/XsdirEntry/src/parse.hpp"

public:

  /* constructor */
  #include "ACEtk/XsdirEntry/src/ctor.hpp"

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

  #include "ACEtk/XsdirEntry/src/print.hpp"
};

#include "ACEtk/XsdirEntry/src/stream.hpp"

} // ACEtk namespace
} // njoy namespace

#endif
