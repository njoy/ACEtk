#ifndef NJOY_ACETK_BLOCK_BASE
#define NJOY_ACETK_BLOCK_BASE

// system includes
#include <vector>
#include <optional>

// other includes
#include "Log.hpp"
#include "range/v3/all.hpp"
// AFTER RANGES UPDATE
// #include "range/v3/view/subrange.hpp"

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
  std::string name_;
  std::optional< std::vector< double > > xss_;
  std::vector< double >::iterator begin_;
  std::vector< double >::iterator end_;
  std::size_t length_;

protected:

  /* auxiliary functions */
  #include "ACEtk/block/Base/src/verifyIndex.hpp"

  /* constructor */
  #include "ACEtk/block/Base/src/ctor.hpp"

public:

  /* methods */

  /**
   *  @brief Return the name of the block
   */
  const std::string& name() const { return this->name_; }

  /**
   *  @brief Return the length of the the xss array of the block
   */
  std::size_t length() const { return this->length_; }

  /**
   *  @brief Return the begin itertor to the xss array of the block
   */
  auto begin() const { return this->begin_; }

  /**
   *  @brief Return the begin itertor to the xss array of the block
   */
  auto end() const { return this->end_; }

  /**
   *  @brief Return the xss array of the block
   */
  auto XSS() const {

    return ranges::make_iterator_range( this->begin(), this->end() );
  }

  /**
   *  @brief Return a value from the XSS array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  auto XSS( std::size_t index ) const {

    this->verifyIndex( index );
    return *std::next( this->begin(), index - 1 );
  }

  /**
   *  @brief Return a subrange of a given length from the xss array of the block
   *
   *  When the index is out of range or if the array goes over its length,
   *  an std::out_of_range exception is thrown.
   *
   *  @param[in] index     the index (one-based)
   *  @param[in] length    the length of the subrange
   */
  auto XSS( std::size_t index, std::size_t length ) const {

    this->verifyIndex( index );
    this->verifyIndex( index + length - 1 );
    const auto left = std::next( this->begin(), index - 1 );
    const auto right = left + length;
    return ranges::make_iterator_range( left, right );
  }
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
