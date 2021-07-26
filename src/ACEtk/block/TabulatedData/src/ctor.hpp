TabulatedData() = default;

TabulatedData( const TabulatedData& ) = default;
TabulatedData( TabulatedData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] name           the name of the data
 *  @param[in] boundaries     the interpolation range boundaries
 *  @param[in] interpolants   the interpolation types for each range
 *  @param[in] x              the x values
 *  @param[in] y              the y values
 */
TabulatedData( std::string&& name,
               std::vector< long >&& boundaries,
               std::vector< long >&& interpolants,
               std::vector< double >&& x,
               std::vector< double >&& y ) :
  Base( std::move( name ),
        generateXSS( std::move( boundaries ), std::move( interpolants ),
                     std::move( x ), std::move( y ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] name           the name of the data
 *  @param[in] x              the x values
 *  @param[in] y              the y values
 */
TabulatedData( std::string&& name,
               std::vector< double >&& x,
               std::vector< double >&& y ) :
 Base( std::move( name ),
       generateXSS( {}, {}, std::move( x ), std::move( y ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the SIG block in the XSS array
 *  @param[in] end      the end iterator of the SIG block in the XSS array
 */
TabulatedData( std::string&& name, Iterator begin, Iterator end ) :
  Base( std::move( name ), begin, end ) {

  verifySize( this->begin(), this->end() );
}

TabulatedData& operator=( const TabulatedData& ) = default;
TabulatedData& operator=( TabulatedData&& ) = default;
