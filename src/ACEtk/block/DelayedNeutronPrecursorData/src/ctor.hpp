DelayedNeutronPrecursorData() = default;

DelayedNeutronPrecursorData( const DelayedNeutronPrecursorData& base ) :
  Base( base ), data_( base.data_ ) {

  if ( Base::owner() ) {

    this->generateBlocks();
  }
}

DelayedNeutronPrecursorData( DelayedNeutronPrecursorData&& base ) :
  Base( std::move( base ) ), data_( std::move( base.data_ ) ) {

  if ( Base::owner() ) {

    this->generateBlocks();
  }
}

/**
 *  @brief Constructor
 *
 *  @param[in] constant          the precursor group's decay constant
 *  @param[in] boundaries        the interpolation range boundaries
 *  @param[in] interpolants      the interpolation types for each range
 *  @param[in] energies          the energy values
 *  @param[in] multiplicities    the multiplicity values
 */
DelayedNeutronPrecursorData( double constant,
                             std::vector< long > boundaries,
                             std::vector< long > interpolants,
                             std::vector< double > energies,
                             std::vector< double > multiplicities ) :
  Base( "DelayedNeutronPrecursorData",
        generateXSS( constant,
                     std::move( boundaries ), std::move( interpolants ),
                     std::move( energies ), std::move( multiplicities ) ) ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] constant          the precursor group's decay constant
 *  @param[in] energies          the energy values
 *  @param[in] multiplicities    the multiplicity values
 */
DelayedNeutronPrecursorData( double constant,
                             std::vector< double > energies,
                             std::vector< double > multiplicities ) :
 DelayedNeutronPrecursorData( constant, {}, {}, std::move( energies ),
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
