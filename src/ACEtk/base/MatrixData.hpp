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

  void verifyIndex( std::size_t row, std::size_t col ) const {

    // Verify row index
    if ( ( row < 1 ) || (row > this->M() ) ) {

      Log::error( "Illegal row index argument into the {} block", this->name() );
      Log::info( "Row index value: {}", row );
      Log::info( "{} accepts an index between {} and {} inclusively",
                 this->name(), 1, this->M() );
      throw std::out_of_range( this->name() );
    }

    // Verify column index
    if ( ( col < 1 ) || (col > this->N() ) ) {

      Log::error( "Illegal column index argument into the {} block", this->name() );
      Log::info( "Column index value: {}", col );
      Log::info( "{} accepts an index between {} and {} inclusively",
                 this->name(), 1, this->N() );
      throw std::out_of_range( this->name() );
    }
  }

  template < typename Number >
  static std::vector< double >
  generateXSS( std::vector< Number >&& rows,
               std::vector< Number >&& cols,
               std::vector< std::vector< Number > >&& vals ) {

    std::vector< double > xss;
    const auto nrows = rows.size();
    const auto ncols = cols.size();
    const auto sz = nrows + ncols + nrows * ncols;
    xss.reserve( sz );

    if ( vals.front().size() == ncols ) {

      if (vals.size() != nrows ) {

        Log::error( "The size of the matrix data is not as expected" );
        Log::info( "Expected: {} arrays", nrows );
        Log::info( "Found: {} arrays", vals.size() );
        throw std::exception();
      }
    } else if ( vals.front().size() == nrows ) {

      if (vals.size() != ncols ) {

        Log::error( "The size of the matrix data is not as expected" );
        Log::info( "Expected: {} arrays", ncols );
        Log::info( "Found: {} arrays", vals.size() );
        throw std::exception();
      }
    } else {

      Log::error( "The size of the matrix data is not as expected" );
      Log::info( "Expected: {} or {}", nrows, ncols );
      Log::info( "Found: {}", vals.front().size() );
      throw std::exception();
    }

    xss.insert( xss.end(), rows.begin(), rows.end() );
    xss.insert( xss.end(), cols.begin(), cols.end() );
    for ( auto&& array: vals ) {

      if ( array.size() != vals.front().size() ) {

        Log::error( "The size of a matrix data array is not as expected" );
        Log::info( "Expected: {} elements", vals.front().size() );
        Log::info( "Found: {} elements", array.size() );
        throw std::exception();
      }
      xss.insert( xss.end(), array.begin(), array.end() );
    }

    return xss;
  }

  void verifySize( Iterator begin, Iterator end, unsigned int nrows, unsigned int ncols ) {

    // There must be at least nrows + ncols + nrows * ncols values
    auto size = std::distance( begin, end );
    unsigned int expectedSize = nrows + ncols + nrows * ncols;
    if ( size < expectedSize ) {

      Log::error( "The size of the XSS subrange in the {} block should be at least {}",
                  this->name(), expectedSize );
      Log::info( "M value: {}, N value: {}", nrows, ncols );
      Log::info( "XSS.size(): {}", size );
      throw std::exception();
    }
  }
  
public:

  /* constructor */

  MatrixData() = default;

  MatrixData( const MatrixData& ) = default;
  MatrixData( MatrixData&& ) = default;

  MatrixData& operator=( const MatrixData& ) = default;
  MatrixData& operator=( MatrixData&& ) = default;

  /**
  *  @brief Constructor
  *
  *  @param[in] name        the name of the block
  *  @param[in] rows        the row labels
  *  @param[in] cols        the column labels
  *  @param[in] vals        the two-dimensional matrix data values
  *  @param[in] rowmajor    whether the matrix data have row or column major order
  */
  template < typename Number >
  MatrixData( std::string&& name,
              std::vector< Number >&& rows,
              std::vector< Number >&& cols,
              std::vector< std::vector< Number > >&& vals,
              bool rowmajor ) :
  Base( std::move( name ),
        generateXSS( std::move( rows ), std::move( cols ), std::move( vals ) ) ),
  rowmajor_( rowmajor ), nrows_( rows.size() ), ncols_( cols.size() ) {}

  /**
  *  @brief Constructor
  *
  *  @param[in] begin      the begin iterator of the matrix data in the XSS array
  *  @param[in] end        the end iterator of the matrix data in the XSS array
  *  @param[in] nrows      the number of rows and row labels
  *  @param[in] ncols      the number of columns and column labels
  *  @param[in] rowmajor   whether the matrix data have row or column major order
  */
  MatrixData( std::string&& name,
              Iterator begin,
              Iterator end,
              unsigned int nrows,
              unsigned int ncols,
              bool rowmajor ) :
  Base( std::move( name ), begin, end ),
  rowmajor_(rowmajor), nrows_(nrows), ncols_(ncols) {

    verifySize( this->begin(), this->end(), this->nrows_, this->ncols_ );
  }
  
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
    
    return this->XSS( this->M() + this->N() + 1, this->M() * this->N() );
  }

  /**
   *  @brief Return a matrix of integers (as a 1-D array)
   */
  auto imatrix() const {
    
    return this->IXSS( this->M() + this->N() + 1, this->M() * this->N() );
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
      
      std::size_t index = ( row - 1 ) * this->N() + this->M() + this->N();
      std::size_t span = this->N();
      return njoy::tools::std23::views::stride( this->XSS( index, span ), 1 );
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
      
      std::size_t index = ( row - 1 ) * this->N() + this->M() + this->N();
      std::size_t span = this->N();
      return njoy::tools::std23::views::stride( this->IXSS( index, span ), 1 );
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
      
      std::size_t index = ( col - 1 ) * this->M() + this->M() + this->N();
      std::size_t span = this->M();
      return njoy::tools::std23::views::stride( this->XSS( index, span ), 1 );
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
      
      std::size_t index = ( col - 1 ) * this->M() + this->M() + this->N();
      std::size_t span = this->M();
      return njoy::tools::std23::views::stride( this->IXSS( index, span ), 1 );
    }
  }

  /**
   *  @brief Return an empty matrix
   */
  auto emptyMatrix() const { return this->XSS( 1, 0 ); }

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
