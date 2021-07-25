TabulatedData() = default;

TabulatedData( const TabulatedData& ) = default;
TabulatedData( TabulatedData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] xs    the cross section data
 */
TabulatedData( std::vector< long >&& boundaries,
               std::vector< long >&& interpolants,
               std::vector< double >&& x,
               std::vector< double >&& y ) :
  Base( "TABLE", generateXSS( std::move( boundaries ), std::move( interpolants ),
                              std::move( x ), std::move( y ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the SIG block in the XSS array
 *  @param[in] end      the end iterator of the SIG block in the XSS array
 */
TabulatedData( Iterator begin, Iterator end ) :
  Base( "TABLE", begin, end ) {

  verifySize( this->begin(), this->end() );
}

TabulatedData& operator=( const TabulatedData& ) = default;
TabulatedData& operator=( TabulatedData&& ) = default;
