#ifndef NJOY_ACETK_BLOCK_BASE
#define NJOY_ACETK_BLOCK_BASE

// system includes
#include <vector>
#include <optional>

// other includes

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief The base class for a block of data from an ACE file
 *
 *  The Base class represents a block of data from the XSS array in the ACE
 *  tables, for example: the ESZ block for a continuous energy ACE file.
 */
class Base {

public:

  using Iterator = std::vector< double >::iterator;

private:

  /* fields */
  std::optional< std::vector< double > > xss_;
  std::vector< double >::iterator begin_;
  std::vector< double >::iterator end_;

public:

  #include "ACEtk/block/Base/src/ctor.hpp"

  auto begin() const { return this->begin_; }
  auto end() const { return this->end_; }

  auto XSS() const {

    return ranges::make_iterator_range( this->begin(), this->end() );
  }
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
