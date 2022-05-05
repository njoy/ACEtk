BaseTabulatedData() = default;

BaseTabulatedData( const BaseTabulatedData& base ) :
  Base( base ), interpolation_( base.interpolation_ ),
  data_( base.data_ ) {

  if ( Base::owner() ) {

    this->generateBlocks();
  }
}

BaseTabulatedData( BaseTabulatedData&& base ) :
  Base( std::move( base ) ), interpolation_( std::move( base.interpolation_ ) ),
  data_( std::move( base.data_ ) ) {

  if ( Base::owner() ) {

    this->generateBlocks();
  }
}

/**
 *  @brief Constructor
 *
 *  @param[in] name            the name of the block
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] x               the x values
 *  @param[in] y               the y values
 */
BaseTabulatedData( std::string name,
                   std::vector< long > boundaries,
                   std::vector< long > interpolants,
                   std::vector< double > x,
                   std::vector< double > y ) :
  Base( std::move( name ),
        generateXSS( name,
                     std::move( boundaries ), std::move( interpolants ),
                     std::move( x ), std::move( y ) ) ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] name    the name of the block
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
BaseTabulatedData( std::string name, Iterator begin, Iterator end ) :
  Base( std::move( name ), begin, end ) {

  std::size_t nr = static_cast< std::size_t >( round( this->XSS( 1 ) ) );
  std::size_t ne = static_cast< std::size_t >( round( this->XSS( 1 + 2 * nr + 1 ) ) );
  verifySize( this->begin(), this->end(), nr, ne );
  this->generateBlocks();
}

BaseTabulatedData& operator=( const BaseTabulatedData& base ) {

  new (this) BaseTabulatedData( base );
  return *this;
}

BaseTabulatedData& operator=( BaseTabulatedData&& base ) {

  new (this) BaseTabulatedData( std::move( base ) );
  return *this;
}
