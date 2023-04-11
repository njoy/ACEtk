TabulatedSecondaryParticleMultiplicity() = default;

TabulatedSecondaryParticleMultiplicity( const TabulatedSecondaryParticleMultiplicity& base ) :
  Base( base ) {

  this->generateBlocks();
}

TabulatedSecondaryParticleMultiplicity( TabulatedSecondaryParticleMultiplicity&& base ) :
  Base( std::move( base ) ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] mftype            the type (12 or 16)
 *  @param[in] mt                the associated reaction number
 *  @param[in] boundaries        the interpolation range boundaries
 *  @param[in] interpolants      the interpolation types for each range
 *  @param[in] energies          the energy values
 *  @param[in] multiplicities    the multiplicity values
 */
TabulatedSecondaryParticleMultiplicity( unsigned int mftype, unsigned int mt,
                                        std::vector< long > boundaries,
                                        std::vector< long > interpolants,
                                        std::vector< double > energies,
                                        std::vector< double > multiplicities ) :
  Base( "TabulatedSecondaryParticleMultiplicity",
        generateXSS( mftype, mt,
                     std::move( boundaries ), std::move( interpolants ),
                     std::move( energies ), std::move( multiplicities ) ) ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] mfmult            the type (12 or 16)
 *  @param[in] mt                the associated reaction number
 *  @param[in] energies          the energy values
 *  @param[in] multiplicities    the multiplicity values
 */
TabulatedSecondaryParticleMultiplicity( unsigned int mftype, unsigned int mt,
                                        std::vector< double > energies,
                                        std::vector< double > multiplicities ) :
 TabulatedSecondaryParticleMultiplicity( mftype, mt, {}, {},
                                         std::move( energies ),
                                         std::move( multiplicities ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the multiplicity data in the XSS array
 *  @param[in] end      the end iterator of the multiplicity data in the XSS array
 */
TabulatedSecondaryParticleMultiplicity( Iterator begin, Iterator end ) :
  Base( "TabulatedSecondaryParticleMultiplicity", begin, end ) {

  this->generateBlocks();
}

TabulatedSecondaryParticleMultiplicity& operator=( const TabulatedSecondaryParticleMultiplicity& base ) {

  new (this) TabulatedSecondaryParticleMultiplicity( base );
  return *this;
}

TabulatedSecondaryParticleMultiplicity& operator=( TabulatedSecondaryParticleMultiplicity&& base ) {

  new (this) TabulatedSecondaryParticleMultiplicity( std::move( base ) );
  return *this;
}
