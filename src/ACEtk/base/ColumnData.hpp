#ifndef NJOY_ACETK_BASE_COLUMNDATA
#define NJOY_ACETK_BASE_COLUMNDATA

// system includes

// other includes
#include "ACEtk/base/Base.hpp"

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
  std::size_t nc_;

  /* auxiliary functions */
  #include "ACEtk/base/ColumnData/src/generateXSS.hpp"
  #include "ACEtk/base/ColumnData/src/verifySize.hpp"

public:

  /* constructor */
  #include "ACEtk/base/ColumnData/src/ctor.hpp"

  /**
   *  @brief Return the number of columns
   */
  std::size_t NC() const { return this->nc_; }

  /**
   *  @brief Return the number of columns
   */
  std::size_t numberColumns() const { return this->NC(); }

  /**
   *  @brief Return the number of elements in a column
   */
  std::size_t N() const { return this->empty() ? 0 : this->IXSS( 1 ); }

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
  double value( std::size_t column, std::size_t index ) const {

    auto number = this->N();
    return this->XSS( 2 + ( column - 1 ) * number + index - 1 );
  }

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::IXSS;
  using Base::begin;
  using Base::end;
};

} // details namespace
} // block namespace
} // ACEtk namespace
} // njoy namespace

#endif
