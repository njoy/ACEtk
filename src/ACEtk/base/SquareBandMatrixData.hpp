#ifndef NJOY_ACETK_BASE_SQUAREBANDMATRIXDATA
#define NJOY_ACETK_BASE_SQUAREBANDMATRIXDATA

// system includes
#include <algorithm>

// other includes
#include "ACEtk/base/Base.hpp"
#include "tools/std20/views.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief A block of data given as a square matrix with a defined number of
 *         super-diagonals and sub-diagonals (default is zero for each)
 */
class SquareBandMatrixData : protected Base {

  /* fields */

  unsigned int size_;
  unsigned int nsuper_ = 0;
  unsigned int nsub_ = 0;

  /* auxiliary functions */

  /**
   *  @brief Verify that the row exists in the matrix
   *
   *  @param[in] row    the row index (one-based)
   */
  bool verifyRow( unsigned int row ) const {

    // Verify row index
    if ( ( row < 1 ) || (row > this->M() ) ) {

      return false;
    }

    return true;
  }

  /**
   *  @brief Verify that the col exists in the matrix
   *
   *  @param[in] col    the column index (one-based)
   */
  bool verifyCol( unsigned int col ) const {

    // Verify column index
    if ( ( col < 1 ) || ( col > this->N() ) ) {

      return false;
    }

    return true;
  }

  /**
   *  @brief Verify that the element is within the bounds of
   *         the matrix, and exists within the diagonal bands
   *
   *  @param[in] row    the row index (one-based)
   *  @param[in] col    the column index (one-based)
   */
  bool verifyIndex( std::size_t row, std::size_t col ) const {

    if ( !verifyRow( row ) || !verifyCol( col ) ) {

      return false;
    }

    // Verify that the (row,col) pair exists in the list
    if ( ( col < this->rowStart( row ) ) || ( col > this->rowEnd( row ) ) ) {

      return false;
    }

    return true;
  }

  template < typename Number >
  static std::vector< double >
  generateXSS( std::vector< std::vector< Number > >&& vals,
              unsigned int nsuper, unsigned int nsub ) {

    std::vector< double > xss;
    unsigned int nrows = vals.size();
    unsigned int ncols = vals.front().size();

    if ( nrows != ncols ) {

      Log::error( "SquareBandMatrixData requires a square matrix" );
      Log::info( "Matrix has {} rows", nrows );
      Log::info( "But the first row is length {} ", ncols);
      throw std::exception();
    }

    if ( nsuper >= nrows ) {

      Log::error( "Number of super-diagonals cannot be greater than or equal to the number of rows" );
      Log::info( "Number of rows: {} ", nrows );
      Log::info( "Number of super-diagonals: {} ", nsuper );
    }
    if ( nsub >= nrows ) {

      Log::error( "Number of sub-diagonals cannot be greater than or equal to the number of rows" );
      Log::info( "Number of rows: {} ", nrows );
      Log::info( "Number of sub-diagonals: {} ", nsub );
    }

    const auto sz = nrows * ( 1 + nsub + nsuper)  - ( ( nsub * ( 1 + nsub ) ) + ( nsuper * ( 1 + nsuper ) ) ) / 2 ;
    xss.reserve( sz );

    int k = 0;
    int rowStart;
    int rowEnd;

    for ( auto&& array: vals ) {

      k++;

      if ( array.size() != ncols ) {

        Log::error( "The size of the diagonal matrix data array is not as expected in row {}", k );
        Log::info( "Expected: {} elements", ncols );
        Log::info( "Found: {} elements", array.size() );
        throw std::exception();
      }

      // both of these calculations are based on one-indexed matrices
      rowStart = std::max( k - static_cast< int >( nsub ),  1 );
      rowEnd = std::min( nrows, k + nsuper );


      if ( array.begin() + rowEnd  > array.end() ) {
        Log::error( "The row end calculation is beyond the end of the array for row {}", k );
        Log::info( "Array length: {}", array.size() );
        Log::info( "Calculated row end: {} ", rowEnd );
        throw std::exception();
      }

      xss.insert( xss.end(), array.begin() + ( rowStart - 1 ), array.begin() + rowEnd );

    }

    return xss;
  }

  /**
   *  @brief Return the starting index (one-based) of a row
   *         in the list of values
   *
   *  @param[in] row     the row index in the matrix (one-based)
   */
  unsigned int rowListStart( unsigned int row ) const {

      unsigned int index = 0;

      // get length of rows above desired row to
      // find the start index of desired row
      for (unsigned int i = 1; i < row; ++i) {

          index = index + this->rowLength( i );
      }

      return index + 1;
  }

  /**
   *  @brief Return the index (one-based) of an element
   *         in the list of values
   *
   *  This function assumes the element exists in the list - the
   *  behavior is undefined if the element is not. The verifyIndex
   *  method should always be called before this method.
   *
   *  @param[in] row     the row index in the matrix (one-based)
   *  @param[in] col     the col index in the matrix (one-based)
   */
  unsigned int listIndex( unsigned int row, unsigned int col ) const {

      unsigned int index = rowListStart( row );
      return index + ( col - this->rowStart( row ) ) ;
  }

  void verifySize( Iterator begin,
            Iterator end
          ) {

    auto length = std::distance( begin, end );
    unsigned int expectedSize = this->blockLength();
    if ( length < expectedSize ) {

      Log::error( "The size of the XSS subrange in the {} block should be at least {}",
                  this->name(), expectedSize );
      Log::info( "XSS.size(): {}", length );
      throw std::exception();
    }
  }

public:

  /* constructor */

  SquareBandMatrixData() = default;

  SquareBandMatrixData( const SquareBandMatrixData& ) = default;
  SquareBandMatrixData( SquareBandMatrixData&& ) = default;

  SquareBandMatrixData& operator=( const SquareBandMatrixData& ) = default;
  SquareBandMatrixData& operator=( SquareBandMatrixData&& ) = default;

  /**
  *  @brief Constructor
  *
  *  Note: Any non-zero values in the matrix outside of the defined
  *  bands will be lost in the construction of the SquareBandMatrixData
  *  object. The object will check that that the given number of
  *  super-diagonals and sub-diagonals are allowed (no greater than
  *  one less than the length of the side of the matrix) but does not
  *  check that they are consistent with the values in the matrix
  *
  *  @param[in] name        the name of the block
  *  @param[in] vals        the two-dimensional matrix data values
  *  @param[in] nsuper      the number of super-diagonals
  *  @param[in] nsub         the number of sub-diagonals
  */
  template < typename Number >
  SquareBandMatrixData( std::string&& name,
              std::vector< std::vector< Number > >&& vals,
              unsigned int nsuper, unsigned int nsub ) :
  Base( std::move( name ),
        generateXSS( std::move( vals ), nsuper, nsub ) ),
   size_( vals.size() ), nsuper_( nsuper ), nsub_( nsub ) {}

  /**
  *  @brief Constructor
  *
  *  @param[in] name       the name of the block
  *  @param[in] begin      the begin iterator of the matrix data in the XSS array
  *  @param[in] end        the end iterator of the matrix data in the XSS array
  *  @param[in] size       the number of rows and columns in the matrix
  *  @param[in] nsuper     the number of super-diagonals
  *  @param[in] nsub       the number of sub-diagonals
  */
  SquareBandMatrixData( std::string&& name,
              Iterator begin,
              Iterator end,
              unsigned int size,
              unsigned int nsuper,
              unsigned int nsub ) :
  Base( std::move( name ), begin, end ),
  size_( size ), nsuper_( nsuper ), nsub_( nsub ) {

    verifySize( this->begin(), this->end() );
  }

  /* methods */

  /**
   *  @brief Return the matrix size (number of rows/columns)
   */
  unsigned int size() const { return this->size_; }

  /**
   *  @brief Return the number of rows (first index)
   */
  unsigned int M() const { return this->size_; }

  /**
   *  @brief Return the number of rows (first index)
   */
  unsigned int numberRows() const { return this->M(); }

  /**
   *  @brief Return the number of columns (second index)
   */
  unsigned int N() const { return this->size_; }

  /**
   *  @brief Return the number of columns (second index)
   */
  unsigned int numberColumns() const { return this->N(); }

  /**
   *  @brief Return the number of super-diagonals
   */
  unsigned int NSUP() const { return this->nsuper_; }

  /**
   *  @brief Return the number of super-diagonals
   */
  unsigned int numberSuperDiagonals() const { return this->NSUP(); }

  /**
   *  @brief Return the number of sub-diagonals
   */
  unsigned int NSUB() const { return this->nsub_; }


  /**
   *  @brief Return the number of sub-diagonals
   */
  unsigned int numberSubDiagonals() const { return this->NSUB(); }


  /**
   *  @brief Return the length of the block
   */
  unsigned int blockLength() const {

    return ( this->size() * ( 1 + this->NSUB() + this->NSUP() )) - ( ( this->NSUB() * ( 1 + this->NSUB() ) ) + ( this->NSUP() * ( 1 + this->NSUP() ) ) ) / 2;
  }

  /**
   *  @brief Return the matrix as a 1-D array
   */
  auto matrixList() const {

    return this->XSS( );
  }

  /**
   *  @brief Return the number of super-diagonal bands for a row
   *
   *  @param[in] row     the row index (one-based)
   */
  unsigned int rowSuperDiagonals( unsigned int row ) const {

    return this->rowEnd( row ) - row;
  }

  /**
   *  @brief Return the number of sub-diagonal bands for a row
   *
   *  @param[in] row     the row index (one-based)
   */
  unsigned int rowSubDiagonals( unsigned int row ) const {

    return  row - this->rowStart( row ) ;
  }

  /**
   *  @brief Return the value at a location given by the row and
   *         column indices (one-based) in the matrix.
   *
   *  The function will return zero if:
   *    - the element isn't part of the list (the row and column
   *      correspond to an element outside the given bands)
   *    - if the element is outside the bounds of the matrix
   *
   *  @param[in] row     the row index (one-based)
   *  @param[in] col     the row index (one-based)
   */
  auto matrixValue( unsigned int row, unsigned int col ) const {

    // if this element isn't in the matrix or in the list,
    // return zero

    if ( this->verifyIndex( row, col ) ) {

      unsigned int index = this->listIndex( row, col );
      return this->XSS( index ) ;
    }
    else {

      return 0.;
    }


  }

  /**
   *  @brief Return a row of the matrix
   *
   *  If the row is out of bounds, an array of all
   *  zeros will be returned
   *
   *  @param[in] row     the row index (one-based)
   */
   auto matrixRow( unsigned int row ) const {

      std::vector< double > v;

      for (unsigned int col = 1; col <= this->M(); ++col ) {

        v.push_back( this-> matrixValue( row, col ) ) ;
      }

    return v;
    }

  /**
   *  @brief Return the matrix
   *
   */
   auto matrix( ) const {

      std::vector<  std::vector < double > > v;

      for (unsigned int row = 1; row <= this->size(); ++row ){

        v.push_back( {} );
        for (unsigned int col = 1; col <= this->size(); ++col ) {

          v.back().push_back( this-> matrixValue( row, col ) ) ;
        }
      }

    return v;
  }

  /**
   *  @brief Return the starting index (one-based) of a row
   *
   *  @param[in] row     the row index (one-based)
   */
  unsigned int rowStart( int row ) const {

    // Have to have signed ints here because this equation relies on the
    // ability of the first term to go negative when the row is filled
    // in all the way to first column, so that the max function gives 1.
    // To avoid casting to signed int, the logic would need to be changed.
    return std::max( row - static_cast< int >( this->NSUB() ),  1  );
  }

  /**
   *  @brief Return the ending index (one-based) of a row
   *
   *  @param[in] row     the row index (one-based)
   */
  unsigned int rowEnd( unsigned int row ) const {

    return std::min( this->size(), row + this->NSUP() );
  }

  /**
   *  @brief Return the length of a row
   *
   *  The length includes both the starting index and the ending
   *  index, so it is 1 + (end - start)
   *
   *  @param[in] row     the row index (one-based)
   */
  unsigned int rowLength( unsigned int row ) const {

        return 1 + this->rowEnd( row ) - this->rowStart( row ) ;
  }

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
