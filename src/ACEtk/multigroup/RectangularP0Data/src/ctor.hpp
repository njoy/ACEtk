RectangularP0Data() = default;

RectangularP0Data( const RectangularP0Data& ) = default;
RectangularP0Data( RectangularP0Data&& ) = default;

RectangularP0Data& operator=( const RectangularP0Data& ) = default;
RectangularP0Data& operator=( RectangularP0Data&& ) = default;


/**
 *  @brief Constructor
*
*  Note: Any non-zero values in the matrix outside of the defined
*  bands will be lost in the construction of the RectangularP0Data 
*  object. 
 *
*  @param[in] matrix     the two-dimensional matrix data values
*/
RectangularP0Data( std::vector< std::vector< double > >&& matrix ) :
  RectangularMatrixData( "RectangularP0Data", std::move( matrix ) ) {}

/**
*  @brief Constructor
*
*  @param[in] begin      the begin iterator of the P0 data in the XSS array
*  @param[in] end        the end iterator of the P0 data in the XSS array
*  @param[in] nrows      the number of rows and row labels
*  @param[in] ncols      the number of columns and column labels
*/
RectangularP0Data( Iterator begin,
            Iterator end,
            unsigned int nrows,
            unsigned int ncols ) :
RectangularMatrixData( "RectangularP0Data", begin, end, nrows, ncols ) {}

