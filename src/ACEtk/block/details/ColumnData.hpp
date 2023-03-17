#ifndef NJOY_ACETK_BLOCK_DETAILS_COLUMNDATA
#define NJOY_ACETK_BLOCK_DETAILS_COLUMNDATA

// system includes

// other includes
#include "ACEtk/block/details/Base.hpp"

namespace njoy {
namespace ACEtk {
namespace block {
namespace details {

/**
 *  @class
 *  @brief Column data: a number of columns of fixed length
 */
class ColumnData : protected Base {

  /* fields */

  /* auxiliary functions */
  #include "ACEtk/block/details/ColumnData/src/generateXSS.hpp"
  #include "ACEtk/block/details/ColumnData/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/block/details/ColumnData/src/ctor.hpp"

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
   *  @param[in] column     the column index (one-based)
   */
  auto C( std::size_t column ) const {

    auto number = this->N();
    return this->XSS( 2 + ( column - 1 ) * number, number );
  }

  /**
   *  @brief Return the column
   *
   *  @param[in] column     the column index (one-based)
   */
  auto column( std::size_t column ) const { return this->C( column ); }

  /**
   *  @brief Return a value
   *
   *  @param[in] column     the column index (one-based)
   *  @param[in] index      the index in the column (one-based)
   */
  auto value( std::size_t column, std::size_t index ) const {

    auto number = this->N();
    return this->XSS( 2 + ( column - 1 ) * number + index - 1 );
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::begin;
  using Base::end;
};

} // details namespace
} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
