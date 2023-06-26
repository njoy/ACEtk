DelayedNeutronPrecursorData() = default;

DelayedNeutronPrecursorData( const DelayedNeutronPrecursorData& base ) :
  Base( base ), number_( base.number_ ),
  data_( base.data_ ) {

  if ( Base::owner() ) {

    this->generateBlocks();
  }
}

DelayedNeutronPrecursorData( DelayedNeutronPrecursorData&& base ) :
  Base( std::move( base ) ), number_( base.number_ ),
  data_( std::move( base.data_ ) ) {

  if ( Base::owner() ) {

    this->generateBlocks();
  }
}

/**
 *  @brief Constructor
 *
 *  @param[in] number            the precursor group number
 *  @param[in] constant          the precursor group's decay constant
 *  @param[in] boundaries        the interpolation range boundaries
 *  @param[in] interpolants      the interpolation types for each range
 *  @param[in] energies          the energy values
 *  @param[in] multiplicities    the multiplicity values
 */
DelayedNeutronPrecursorData( unsigned int number, double constant,
                             std::vector< long > boundaries,
                             std::vector< long > interpolants,
                             std::vector< double > energies,
                             std::vector< double > multiplicities ) :
  Base( "DelayedNeutronPrecursorData",
        generateXSS( constant,
                     std::move( boundaries ), std::move( interpolants ),
                     std::move( energies ), std::move( multiplicities ) ) ),
  number_( number ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] number            the precursor group number
 *  @param[in] constant          the precursor group's decay constant
 *  @param[in] energies          the energy values
 *  @param[in] multiplicities    the multiplicity values
 */
DelayedNeutronPrecursorData( unsigned int number, double constant,
                             std::vector< double > energies,
                             std::vector< double > multiplicities ) :
 DelayedNeutronPrecursorData( number, constant, {}, {}, std::move( energies ),
                              std::move( multiplicities ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] number   the precursor group number
 *  @param[in] begin    the begin iterator of the multiplicity data in the XSS array
 *  @param[in] end      the end iterator of the multiplicity data in the XSS array
 */
DelayedNeutronPrecursorData( Iterator begin, Iterator end, unsigned int number ) :
  Base( "DelayedNeutronPrecursorData", begin, end ),
  number_( number ) {

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
