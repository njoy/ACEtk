#ifndef NJOY_ACETK_BASE_BASE
#define NJOY_ACETK_BASE_BASE

// system includes
#include <vector>
#include <optional>

// other includes
#include "Log.hpp"
#include "range/v3/view/subrange.hpp"
#include "range/v3/view/transform.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief The base class for a block of data from an ACE file
 *
 *  The Base class represents a block of data from the XSS array in the ACE
 *  tables, for example: the ESZ block for a continuous energy ACE file.
 */
class Base {

public:

  using Iterator = std::vector< double >::const_iterator;

private:

  /* fields */
  std::string name_;
  std::optional< std::vector< double > > xss_;
  Iterator begin_;
  Iterator end_;
  std::size_t length_;

protected:

  /* auxiliary functions */
  #include "ACEtk/base/Base/src/verifyIndex.hpp"
  #include "ACEtk/base/Base/src/verifyReactionIndex.hpp"

  /* constructor */
  #include "ACEtk/base/Base/src/ctor.hpp"

public:

  /* methods */

  /**
   *  @brief Check whether or not this objects owns the xss array
   */
  bool owner() const { return this->xss_ ? true : false; }

  /**
   *  @brief Return whether or not the block is empty
   */
  bool empty() const { return this->begin_ == this->end_; }

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
   *  @brief Return an iterator to an XSS element
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  Iterator iterator( std::size_t index ) const {

    #ifndef NDEBUG
    // an iterator may point to the position after the last one
    this->verifyIndex( index, 1, this->length() + 1 );
    #endif
    return std::next( this->begin(), index - 1 );
  }

  /**
   *  @brief Return the xss array of the block
   */
  auto XSS() const {

    return ranges::make_subrange( this->begin(), this->end() );
  }

  /**
   *  @brief Return a value from the XSS array
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  double XSS( std::size_t index ) const {

    #ifndef NDEBUG
    this->verifyIndex( index, 1, this->length() );
    #endif
    return *std::next( this->begin(), index - 1 );
  }

  /**
   *  @brief Return a value from the XSS array as an integer
   *
   *  Range checking is only performed when NDEBUG is not defined. When the index
   *  is out of range, an std::out_of_range exception is thrown.
   *
   *  @param[in] index    the index (one-based)
   */
  int IXSS( std::size_t index ) const {

    return static_cast< int >( std::round( this->XSS( index ) ) );
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

    const auto left = this->iterator( index );
    const auto right = length > 0 ? this->iterator( index + length - 1 ) + 1
                                  : left;
    return ranges::make_subrange( left, right );
  }

  /**
   *  @brief Return a subrange of integers of a given length from the xss array
   *         of the block
   *
   *  When the index is out of range or if the array goes over its length,
   *  an std::out_of_range exception is thrown.
   *
   *  @param[in] index     the index (one-based)
   *  @param[in] length    the length of the subrange
   */
  auto IXSS( std::size_t index, std::size_t length ) const {

    const auto left = this->iterator( index );
    const auto right = length > 0 ? this->iterator( index + length - 1 ) + 1
                                  : left;
    return this->XSS( index, length )
           | ranges::views::transform(
                 [] ( auto value ) -> int
                    { return static_cast< int >( std::round( value ) ); } );
  }
};

} // base namespace
} // ACEtk namespace
} // njoy namespace

#endif
