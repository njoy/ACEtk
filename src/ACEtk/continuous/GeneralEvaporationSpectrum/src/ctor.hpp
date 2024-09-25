GeneralEvaporationSpectrum() = default;

GeneralEvaporationSpectrum( const GeneralEvaporationSpectrum& base ) :
  Base( base ),
  tabulated_( base.tabulated_ ), bins_( base.bins_ ) {

  if ( Base::owner() ) {

    this->generateBlocks();
  }
}

GeneralEvaporationSpectrum( GeneralEvaporationSpectrum&& base ) :
  Base( std::move( base ) ),
  tabulated_( std::move( base.tabulated_ ) ), bins_( std::move( base.bins_ ) ) {

  if ( Base::owner() ) {

    this->generateBlocks();
  }
}

GeneralEvaporationSpectrum& operator=( const GeneralEvaporationSpectrum& base ) {

  if ( this != &base ) {

    Base::operator=( base );
    this->tabulated_ = base.tabulated_;
    this->bins_ = base.bins_;
    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }
  return *this;
}

GeneralEvaporationSpectrum& operator=( GeneralEvaporationSpectrum&& base ) {

  if ( this != &base ) {

    Base::operator=( std::move( base ) );
    this->tabulated_ = std::move( base.tabulated_ );
    this->bins_ = std::move( base.bins_ );
    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }
  return *this;
}

/**
 *  @brief Constructor
 *
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] energies        the energy values
 *  @param[in] temperatures    the temperature values
 *  @param[in] bins            the x bin values
 */
GeneralEvaporationSpectrum(
    std::vector< long > boundaries,
    std::vector< long > interpolants,
    std::vector< double > energies,
    std::vector< double > temperatures,
    std::vector< double > bins ) :
  Base( "GeneralEvaporationSpectrum",
        generateXSS( std::move( boundaries ), std::move( interpolants ),
                     std::move( energies ), std::move( temperatures ),
                     std::move( bins ) ) ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor without interpolation data
 *
 *  @param[in] energies        the energy values
 *  @param[in] temperatures    the temperature values
 *  @param[in] bins            the x bin values
 */
GeneralEvaporationSpectrum(
    std::vector< double > energies,
    std::vector< double > temperatures,
    std::vector< double > bins ) :
  GeneralEvaporationSpectrum( {}, {},
                              std::move( energies ), std::move( temperatures ),
                              std::move( bins ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] locb    the starting xss index with respect to the superblock
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
GeneralEvaporationSpectrum( Iterator begin, Iterator end ) :
  Base( "GeneralEvaporationSpectrum", begin, end ) {

  std::size_t nr = static_cast< std::size_t >( this->IXSS( 1 ) );
  std::size_t ne = static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 ) );
  std::size_t nb = static_cast< std::size_t >( this->IXSS( 1 + 2 * nr + 1 + 2 * ne + 1 ) );
  verifySize( this->begin(), this->end(), nr, ne, nb );
  this->generateBlocks();
}
