DelayedNeutronPrecursorData() = default;

DelayedNeutronPrecursorData( const DelayedNeutronPrecursorData& base ) :
  Base( base ) {

  this->generateBlocks();
}

DelayedNeutronPrecursorData( DelayedNeutronPrecursorData&& base ) :
  Base( std::move( base ) ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] lambda            the precursor group's decay constant
 *  @param[in] boundaries        the interpolation range boundaries
 *  @param[in] interpolants      the interpolation types for each range
 *  @param[in] energies          the energy values
 *  @param[in] multiplicities    the multiplicity values
 */
DelayedNeutronPrecursorData( double lambda,
                             std::vector< long > boundaries,
                             std::vector< long > interpolants,
                             std::vector< double > energies,
                             std::vector< double > multiplicities ) :
  Base( "DelayedNeutronPrecursorData",
        generateXSS( lambda,
                     std::move( boundaries ), std::move( interpolants ),
                     std::move( energies ), std::move( multiplicities ) ) ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] lambda            the precursor group's decay constant
 *  @param[in] energies          the energy values
 *  @param[in] multiplicities    the multiplicity values
 */
DelayedNeutronPrecursorData( double lambda,
                             std::vector< double > energies,
                             std::vector< double > multiplicities ) :
 DelayedNeutronPrecursorData( lambda, {}, {}, std::move( energies ),
                              std::move( multiplicities ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the multiplicity data in the XSS array
 *  @param[in] end      the end iterator of the multiplicity data in the XSS array
 */
DelayedNeutronPrecursorData( Iterator begin, Iterator end ) :
  Base( "DelayedNeutronPrecursorData", begin, end ) {

  this->generateBlocks();
}

DelayedNeutronPrecursorData& operator=( const DelayedNeutronPrecursorData& base ) {

  new (this) DelayedNeutronPrecursorData( base );
  return *this;
}

DelayedNeutronPrecursorData& operator=( DelayedNeutronPrecursorData&& base ) {

  new (this) DelayedNeutronPrecursorData( std::move( base ) );
  return *this;
}
