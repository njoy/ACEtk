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
