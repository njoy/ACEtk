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
BandMatrixData( std::string&& name,
            Iterator begin,
            Iterator end,
            unsigned int size,
            unsigned int nsuper,
            unsigned int nsub ) :
Base( std::move( name ), begin, end ),
size_(size), nsuper_(nsuper), nsub_(nsub) {

  verifySize( this->begin(), this->end() );
}
