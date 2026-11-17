#ifndef NJOY_ACETK_BASE_RECTANGULARMATRIXDATA
#define NJOY_ACETK_BASE_RECTANGULARMATRIXDATA

// system includes

// other includes
#include "ACEtk/base/Base.hpp"
#include "tools/std23/views.hpp"

namespace njoy {
namespace ACEtk {
namespace base {

/**
 *  @class
 *  @brief A block of data given as a full 2-D matrix without row/column labels
 */
class RectangularMatrixData : protected Base {

  /* fields */

  unsigned int nrows_;
  unsigned int ncols_;
  
  /* auxiliary functions */

  void verifyIndex( std::size_t row, std::size_t col ) const {

    // Verify row index
    if ( ( row < 1 ) || ( row > this->M() ) ) {

      Log::error( "Illegal row index argument into the {} block", this->name() );
      Log::info( "Row index value: {}", row );
      Log::info( "{} accepts an index between {} and {} inclusively",
                 this->name(), 1, this->M() );
      throw std::out_of_range( this->name() );
    }

    // Verify column index
    if ( ( col < 1 ) || ( col > this->N() ) ) {

      Log::error( "Illegal column index argument into the {} block", this->name() );
      Log::info( "Column index value: {}", col );
      Log::info( "{} accepts an index between {} and {} inclusively",
                 this->name(), 1, this->N() );
      throw std::out_of_range( this->name() );
    }
  }

  template < typename Number >
  static std::vector< double >
  generateXSS( std::vector< std::vector< Number > >&& vals ) {

    std::vector< double > xss;
    const auto nrows = vals.size();
    const auto ncols = vals.front().size();
    const auto sz = nrows * ncols;
    xss.reserve( sz );

    for ( auto&& array: vals ) {

      if ( array.size() != ncols ) {

        Log::error( "The size of a rectangular matrix data array is not as expected in" );
        Log::info( "Expected: {} elements", ncols );
        Log::info( "Found: {} elements", array.size() );
        throw std::exception();
      }
      xss.insert( xss.end(), array.begin(), array.end() );
    }

    return xss;
  }

  void verifySize( Iterator begin, Iterator end, unsigned int nrows, unsigned int ncols ) {

    // There must be nrows * ncols values
    auto size = std::distance( begin, end );
    unsigned int expectedSize =  nrows * ncols;
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

  RectangularMatrixData() = default;

  RectangularMatrixData( const RectangularMatrixData& ) = default;
  RectangularMatrixData( RectangularMatrixData&& ) = default;

  RectangularMatrixData& operator=( const RectangularMatrixData& ) = default;
  RectangularMatrixData& operator=( RectangularMatrixData&& ) = default;

  /**
  *  @brief Constructor
  *
  *  @param[in] name        the name of the block
  *  @param[in] vals        the two-dimensional matrix data values
  */
  template < typename Number >
  RectangularMatrixData( std::string&& name,
              std::vector< std::vector< Number > >&& vals ) :
  Base( std::move( name ),
        generateXSS( std::move( vals ) ) ),
   nrows_( vals.size() ), ncols_( vals.front().size() ) {}

  /**
  *  @brief Constructor
  *
  *  @param[in] begin      the begin iterator of the matrix data in the XSS array
  *  @param[in] end        the end iterator of the matrix data in the XSS array
  *  @param[in] nrows      the number of rows and row labels
  *  @param[in] ncols      the number of columns and column labels
  *  @param[in] rowmajor   whether the matrix data have row or column major order
  */
  RectangularMatrixData( std::string&& name,
              Iterator begin,
              Iterator end,
              unsigned int nrows,
              unsigned int ncols ) :
  Base( std::move( name ), begin, end ),
   nrows_( nrows ), ncols_( ncols ) {

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
   *  @brief Return the number of columns (second index)
   */
  unsigned int N() const { return this->ncols_; }

  /**
   *  @brief Return the number of columns (second index)
   */
  unsigned int numberColumns() const { return this->N(); }

  /**
   *  @brief Return the number of values in the matrix
   */
  unsigned int numberValues() const { return this->M() * this->N(); }

  /**
   *  @brief Return a matrix of doubles (as a 1-D array)
   */
  auto dmatrix() const {
    
    return this->XSS( 1, this->M() * this->N() );
  }

  /**
   *  @brief Return a matrix of integers (as a 1-D array)
   */
  auto imatrix() const {
    
    return this->IXSS( 1, this->M() * this->N() );
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
    
    return this->XSS( ( row - 1 ) * this->N() + col  );

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
    
    return this->IXSS( ( row - 1 ) * this->N() + col  );

  }

  /**
   *  @brief Return a row of doubles
   */
  auto drow( std::size_t row ) const {
    
    #ifndef NDEBUG
    this->verifyIndex( row, 1 );
    #endif
      
    std::size_t index = ( row - 1 ) * this->N() + 1 ;
    std::size_t span = this->N();
    return njoy::tools::std23::views::stride( this->XSS( index, span ), 1 );

  }

  /**
   *  @brief Return a row of integers
   */
  auto irow( std::size_t row ) const {
    
    #ifndef NDEBUG
    this->verifyIndex( row, 1 );
    #endif
      
    std::size_t index = ( row - 1 ) * this->N() + 1;
    std::size_t span = this->N();
    return njoy::tools::std23::views::stride( this->IXSS( index, span ), 1 );

  }

  /**
   *  @brief Return a column of doubles
   */
  auto dcolumn( std::size_t col ) const {
    
    #ifndef NDEBUG
    this->verifyIndex( 1, col );
    #endif
      
    std::size_t index =  col;
    std::size_t span = ( this->M() - 1 ) * this->N() + 1;
    return njoy::tools::std23::views::stride( this->XSS( index, span ), this->N() );

  }

  /**
   *  @brief Return a column of integers
   */
  auto icolumn( std::size_t col ) const {
    
    #ifndef NDEBUG
    this->verifyIndex( 1, col );
    #endif
      
    std::size_t index = col;
    std::size_t span = ( this->M() - 1 ) * this->N() + 1;
    return njoy::tools::std23::views::stride( this->IXSS( index, span ), this->N() );

  }

  /**
   *  @brief Return the matrix
   *
   */
   auto matrix( ) const {

      std::vector<  std::vector < double > > v;

      for (unsigned int row = 1; row <= this->M(); ++row ){

        v.push_back( {} );
        for (unsigned int col = 1; col <= this-> N(); ++col ) {
          
          v.back().push_back( this-> dvalue( row, col ) ) ;
        }
      }

    return v;
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
