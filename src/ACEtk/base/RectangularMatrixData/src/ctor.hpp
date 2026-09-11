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
