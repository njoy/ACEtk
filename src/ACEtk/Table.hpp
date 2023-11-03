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
#include "ACEtk/State.hpp"
#include "disco.hpp"
#include "range/v3/view/subrange.hpp"

namespace njoy {
namespace ACEtk {

using namespace disco;

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
  #include "ACEtk/Table/src/parse.hpp"

public:

  #include "ACEtk/Table/src/ctor.hpp"

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

  #include "ACEtk/Table/src/print.hpp"
};

} // ACEtk namespace
} // njoy namespace

#endif
