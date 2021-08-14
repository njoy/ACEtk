#ifndef NJOY_ACETK_BLOCK_COLUMNDATA
#define NJOY_ACETK_BLOCK_COLUMNDATA

// system includes

// other includes
#include "ACEtk/block/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {

/**
 *  @class
 *  @brief Column data: a number of columns of fixed length
 */
class ColumnData : protected Base {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/block/ColumnData/src/generateXSS.hpp"
  #include "ACEtk/block/ColumnData/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/ColumnData/src/ctor.hpp"

  /**
   *  @brief Return the number of elements in a column
   */
  std::size_t N() const { return this->XSS( 1 ); }

  /**
   *  @brief Return the number of elements in a column
   */
  std::size_t numberElements() const { return this->N(); }

  /**
   *  @brief Return the column
   *
   *  @param[in] index     the column index (one-based)
   */
  auto C( std::size_t index ) const {

    auto number = this->N();
    return this->XSS( 2 + ( index - 1 ) * number, number );
  }

  /**
   *  @brief Return the column
   *
   *  @param[in] index     the column index (one-based)
   */
  auto column( std::size_t index ) const { return this->C( index ); }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
