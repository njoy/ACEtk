#ifndef NJOY_ACETK_BASE_MATRIXDATA
#define NJOY_ACETK_BASE_MATRIXDATA

// system includes

// other includes
#include "ACEtk/base/Base.hpp"
#include "tools/std23/views.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief A block of data given as a 2-D matrix with row/column labels
 */
class MatrixData : protected Base {

  /* fields */
  bool rowmajor_;
  unsigned int nrows_;
  unsigned int ncols_;
  
  /* auxiliary functions */
  #include "ACEtk/base/MatrixData/src/verifyIndex.hpp"
  #include "ACEtk/base/MatrixData/src/generateXSS.hpp"
  #include "ACEtk/base/MatrixData/src/verifySize.hpp"
  
public:

  /* constructor */
  #include "ACEtk/base/MatrixData/src/ctor.hpp"
  
  /* methods */

  /**
   *  @brief Return the number of rows (first index)
   */
  unsigned int M() const { return this->nrows_; }

  /**
   *  @brief Return the number of rows (first index)
   */
  unsigned int numberRows() const { return this->M(); }

  /**
   *  @brief Return the row label at the given index as a double
   *
   *  @param[in] index    the row index (one-based)
   */
  auto drowLabel( std::size_t index ) const {
    
    #ifndef NDEBUG
    this->verifyIndex( index, 1 );
    #endif
    return this->XSS( index );
  }

  /**
   *  @brief Return the row label at the given index as an integer
   *
   *  @param[in] index    the row index (one-based)
   */
  auto irowLabel( std::size_t index ) const {
    
    #ifndef NDEBUG
    this->verifyIndex( index, 1 );
    #endif
    return this->IXSS( index );
  }

  /**
   *  @brief Return the row labels as doubles (first index)
   */
  auto drowLabels() const { return this->XSS( 1, this->M() ); }

  /**
   *  @brief Return the row labels as integers (first index)
   */
  auto irowLabels() const { return this->IXSS( 1, this->M() ); }

  /**
   *  @brief Return the number of columns (second index)
   */
  unsigned int N() const { return this->ncols_; }

  /**
   *  @brief Return the number of columns (second index)
   */
  unsigned int numberColumns() const { return this->N(); }

  /**
   *  @brief Return the column label at the given index as a double
   *
   *  @param[in] index    the column index (one-based)
   */
  auto dcolumnLabel( std::size_t index ) const {
    
    #ifndef NDEBUG
    this->verifyIndex( 1, index );
    #endif
    return this->XSS( this->M() + index );
  }

  /**
   *  @brief Return the column label at the given index as an integer
   *
   *  @param[in] index    the column index (one-based)
   */
  auto icolumnLabel( std::size_t index ) const {
    
    #ifndef NDEBUG
    this->verifyIndex( 1, index );
    #endif
    return this->IXSS( this->M() + index );
  }

  /**
   *  @brief Return the column labels as doubles (second index)
   */
  auto dcolumnLabels() const { return this->XSS( this->M() + 1, this->N() ); }

  /**
   *  @brief Return the column labels as integers (second index)
   */
  auto icolumnLabels() const { return this->IXSS( this->M() + 1, this->N() ); }

  /**
   *  @brief Return the number of values in the matrix
   */
  unsigned int numberValues() const { return this->M() * this->N(); }

  /**
   *  @brief Return a matrix of doubles (as a 1-D array)
   */
  auto dmatrix() const {
    
    return this->XSS( this->M() + this->N(), this->M() * this->N() );
  }

  /**
   *  @brief Return a matrix of integers (as a 1-D array)
   */
  auto imatrix() const {
    
    return this->IXSS( this->M() + this->N(), this->M() * this->N() );
  }

  /**
   *  @brief Return a double value
   *
   *  @param[in] row    the row index (one-based)
   *  @param[in] col    the column index (one-based)
   */
  double dvalue( std::size_t row, std::size_t col ) const {
    
    #ifndef NDEBUG
    this->verifyIndex( row, col );
    #endif
    if ( rowmajor_ ) {
      
      return this->XSS( ( row - 1 ) * this->N() + col + this->M() + this->N() );
    } else {
      
      return this->XSS( ( col - 1 ) * this->M() + row + this->M() + this->N() );
    }
  }

  /**
   *  @brief Return an integer value
   *
   *  @param[in] row    the row index (one-based)
   *  @param[in] col    the column index (one-based)
   */
  double ivalue( std::size_t row, std::size_t col ) const {
    
    #ifndef NDEBUG
    this->verifyIndex( row, col );
    #endif
    if ( rowmajor_ ) {
      
      return this->IXSS( ( row - 1 ) * this->N() + col + this->M() + this->N() );
    } else {
      
      return this->IXSS( ( col - 1 ) * this->M() + row + this->M() + this->N() );
    }
  }

  /**
   *  @brief Return a row of doubles
   */
  auto drow( std::size_t row ) const {
    
    #ifndef NDEBUG
    this->verifyIndex( row, 1 );
    #endif
    if ( rowmajor_ ) {
      
      return this->XSS( ( row - 1 ) * this->N() + this->M() + this->N(), this->N() );
    } else {
      
      std::size_t index = this->M() + this->N() + row;
      std::size_t span = ( this->N() - 1 ) * this->M() + 1;
      return njoy::tools::std23::views::stride( this->XSS( index, span ), this->M() );
    }
  }

  /**
   *  @brief Return a row of integers
   */
  auto irow( std::size_t row ) const {
    
    #ifndef NDEBUG
    this->verifyIndex( row, 1 );
    #endif
    if ( rowmajor_ ) {
      
      return this->IXSS( ( row - 1 ) * this->N() + this->M() + this->N(), this->N() );
    } else {
      
      std::size_t index = this->M() + this->N() + row;
      std::size_t span = ( this->N() - 1 ) * this->M() + 1;
      return njoy::tools::std23::views::stride( this->IXSS( index, span ), this->M() );
    }
  }

  /**
   *  @brief Return a column of doubles
   */
  auto dcolumn( std::size_t col ) const {
    
    #ifndef NDEBUG
    this->verifyIndex( 1, col );
    #endif
    if ( rowmajor_ ) {
      
      std::size_t index = this->M() + this->N() + col;
      std::size_t span = ( this->M() - 1 ) * this->N() + 1;
      return njoy::tools::std23::views::stride( this->XSS( index, span ), this->N() );
    } else {
      
      return this->XSS( ( col - 1 ) * this->M() + this->M() + this->N(), this->M() );
    }
  }

  /**
   *  @brief Return a column of integers
   */
  auto icolumn( std::size_t col ) const {
    
    #ifndef NDEBUG
    this->verifyIndex( 1, col );
    #endif
    if ( rowmajor_ ) {
      
      std::size_t index = this->M() + this->N() + col;
      std::size_t span = ( this->M() - 1 ) * this->N() + 1;
      return njoy::tools::std23::views::stride( this->IXSS( index, span ), this->N() );
    } else {
      
      return this->IXSS( ( col - 1 ) * this->M() + this->M() + this->N(), this->M() );
    }
  }

  /**
   *  @brief Return an empty matrix
   */
  auto emptyMatrix() const { return this->XSS( 1, 0 ); }
  auto emptyRow() const { return this->emptyMatrix(); }  // tomato, tomato
  auto emptyColumn() const { return this->emptyMatrix(); }  // potato, potato

  using Base::empty;
  using Base::name;
  using Base::length;
  using Base::XSS;
  using Base::IXSS;
  using Base::begin;
  using Base::end;
};

} // base namespace
} // ACEtk namespace
} // njoy namespace

#endif
