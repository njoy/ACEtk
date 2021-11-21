SimpleMaxwellianFissionSpectrum() = default;

SimpleMaxwellianFissionSpectrum( const SimpleMaxwellianFissionSpectrum& base ) :
  Base( base ) {

  this->generateBlocks();
}

SimpleMaxwellianFissionSpectrum( SimpleMaxwellianFissionSpectrum&& base ) :
  Base( std::move( base ) ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] energies        the energy values
 *  @param[in] temperatures    the temperature values
 *  @param[in] energy          the restriction energy
 */
SimpleMaxwellianFissionSpectrum(
    std::vector< long >&& boundaries,
    std::vector< long >&& interpolants,
    std::vector< double >&& energies,
    std::vector< double >&& temperatures,
    double energy ) :
  Base( "DLW::SimpleMaxwellianFissionSpectrum",
        generateXSS( std::move( boundaries ), std::move( interpolants ),
                     std::move( energies ), std::move( temperatures ),
                     energy ) ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor without interpolation data
 *
 *  @param[in] energies        the energy values
 *  @param[in] temperatures    the temperature values
 *  @param[in] energy          the restriction energy
 */
SimpleMaxwellianFissionSpectrum(
    std::vector< double >&& energies,
    std::vector< double >&& temperatures,
    double energy ) :
  SimpleMaxwellianFissionSpectrum(
      {}, {}, std::move( energies ), std::move( temperatures ), energy ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] locb    the starting xss index with respect to the superblock
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
SimpleMaxwellianFissionSpectrum( Iterator begin, Iterator end ) :
  Base( "DLW::SimpleMaxwellianFissionSpectrum", begin, end ) {

  std::size_t nr = static_cast< std::size_t >( this->XSS( 1 ) );
  std::size_t ne = static_cast< std::size_t >( this->XSS( 1 + 2 * nr + 1 ) );
  verifySize( this->begin(), this->end(), nr, ne );
  this->generateBlocks();
}

SimpleMaxwellianFissionSpectrum& operator=( const SimpleMaxwellianFissionSpectrum& base ) {

  new (this) SimpleMaxwellianFissionSpectrum( base );
  return *this;
}

SimpleMaxwellianFissionSpectrum& operator=( SimpleMaxwellianFissionSpectrum&& base ) {

  new (this) SimpleMaxwellianFissionSpectrum( std::move( base ) );
  return *this;
}
