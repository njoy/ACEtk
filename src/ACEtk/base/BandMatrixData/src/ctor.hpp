BandMatrixData() = default;

BandMatrixData( const BandMatrixData& ) = default;
BandMatrixData( BandMatrixData&& ) = default;

BandMatrixData& operator=( const BandMatrixData& ) = default;
BandMatrixData& operator=( BandMatrixData&& ) = default;

/**
*  @brief Constructor
*
*  @param[in] name        the name of the block
*  @param[in] vals        the two-dimensional matrix data values
*  @param[in] nsuper      the number of super-diagonals
*  @param[in] nsub         the number of sub-diagonals
*/
BandMatrixData( std::string&& name,
            std::vector< std::vector< double > >&& vals,
            unsigned int nsuper, unsigned int nsub ) :
Base( std::move( name ),
      generateXSS( std::move( vals ), nsuper, nsub ) ),
 size_( vals.size() ), nsuper_( nsuper ), nsub_( nsub ) {}

// /**
// *  @brief Constructor
// *
// *  @param[in] begin      the begin iterator of the matrix data in the XSS array
// *  @param[in] end        the end iterator of the matrix data in the XSS array
// *  @param[in] nrows      the number of rows and row labels
// *  @param[in] ncols      the number of columns and column labels
// *  @param[in] rowmajor   whether the matrix data have row or column major order
// */
// BandMatrixData( std::string&& name,
//             Iterator begin,
//             Iterator end,
//             unsigned int nrows,
//             unsigned int ncols,
//             bool rowmajor ) :
// Base( std::move( name ), begin, end ),
// rowmajor_(rowmajor), nrows_(nrows), ncols_(ncols) {

//   verifySize( this->begin(), this->end(), this->nrows_, this->ncols_ );
// }
