RectangularXPNData() = default;

RectangularXPNData( const RectangularXPNData& ) = default;
RectangularXPNData( RectangularXPNData&& ) = default;

RectangularXPNData& operator=( const RectangularXPNData& ) = default;
RectangularXPNData& operator=( RectangularXPNData&& ) = default;


/**
 *  @brief Constructor
*
*  Note: Any non-zero values in the matrix outside of the defined
*  bands will be lost in the construction of the RectangularXPNData 
*  object. 
 *
*  @param[in] matrix     the two-dimensional locator matrix
*/
RectangularXPNData( std::vector< std::vector< int > >&& matrix ) :
  RectangularMatrixData( "RectangularXPNData", std::move( matrix ) ) {}

/**
*  @brief Constructor
*
*  @param[in] begin      the begin iterator of the XPN data in the XSS array
*  @param[in] end        the end iterator of the XPN data in the XSS array
*  @param[in] nrows      the number of rows and row labels
*  @param[in] ncols      the number of columns and column labels
*/
RectangularXPNData( Iterator begin,
            Iterator end,
            unsigned int nrows,
            unsigned int ncols ) :
RectangularMatrixData( "RectangularXPNData", begin, end, nrows, ncols ) {}

