BaseEvaporationSpectrum() = default;

BaseEvaporationSpectrum( const BaseEvaporationSpectrum& base ) :
  Base( base ), tabulated_( base.tabulated_ ),
  type_( base.type_ ) {

  if ( Base::owner() ) {

    this->generateBlocks();
  }
}

BaseEvaporationSpectrum( BaseEvaporationSpectrum&& base ) :
  Base( std::move( base ) ), tabulated_( std::move( base.tabulated_ ) ),
  type_( base.type_ ) {

  if ( Base::owner() ) {

    this->generateBlocks();
  }
}

/**
 *  @brief Constructor
 *
 *  @param[in] name            the name of the block
 *  @param[in] type            the energy distribution type
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] energies        the energy values
 *  @param[in] temperatures    the temperature values
 *  @param[in] energy          the restriction energy
 */
BaseEvaporationSpectrum(
    std::string name,
    EnergyDistributionType type,
    std::vector< long > boundaries,
    std::vector< long > interpolants,
    std::vector< double > energies,
    std::vector< double > temperatures,
    double energy ) :
  Base( std::move( name ),
        generateXSS( std::move( boundaries ), std::move( interpolants ),
                     std::move( energies ), std::move( temperatures ),
                     energy ) ),
  type_( type ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] name     the name of the block
 *  @param[in] type     the energy distribution type
 *  @param[in] begin    the begin iterator of the block in the XSS array
 *  @param[in] end      the end iterator of the block in the XSS array
 */
BaseEvaporationSpectrum( std::string name, EnergyDistributionType type,
                         Iterator begin, Iterator end ) :
  Base( std::move( name ), begin, end ), type_( type ) {

  std::size_t nr = static_cast< std::size_t >( this->XSS( 1 ) );
  std::size_t ne = static_cast< std::size_t >( this->XSS( 1 + 2 * nr + 1 ) );
  verifySize( this->begin(), this->end(), nr, ne );
  this->generateBlocks();
}

BaseEvaporationSpectrum& operator=( const BaseEvaporationSpectrum& base ) {

  new (this) BaseEvaporationSpectrum( base );
  return *this;
}

BaseEvaporationSpectrum& operator=( BaseEvaporationSpectrum&& base ) {

  new (this) BaseEvaporationSpectrum( std::move( base ) );
  return *this;
}
