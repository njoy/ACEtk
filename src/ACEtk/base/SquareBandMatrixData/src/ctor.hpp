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
SquareBandMatrixData( std::string&& name,
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
