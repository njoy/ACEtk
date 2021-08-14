TabulatedFissionMultiplicity() = default;

TabulatedFissionMultiplicity( const TabulatedFissionMultiplicity& ) = default;
TabulatedFissionMultiplicity( TabulatedFissionMultiplicity&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] boundaries        the interpolation range boundaries
 *  @param[in] interpolants      the interpolation types for each range
 *  @param[in] energies          the energy values
 *  @param[in] multiplicities    the multiplicity values
 */
TabulatedFissionMultiplicity( std::vector< long >&& boundaries,
                              std::vector< long >&& interpolants,
                              std::vector< double >&& energies,
                              std::vector< double >&& multiplicities ) :
  Base( "NU::TABLE",
        generateXSS( std::move( boundaries ), std::move( interpolants ),
                     std::move( energies ), std::move( multiplicities ) ) ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] energies          the energy values
 *  @param[in] multiplicities    the multiplicity values
 */
TabulatedFissionMultiplicity( std::vector< double >&& energies,
                              std::vector< double >&& multiplicities ) :
 TabulatedFissionMultiplicity( {}, {}, std::move( energies ),
                               std::move( multiplicities ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the multiplicity data in the XSS array
 *  @param[in] end      the end iterator of the multiplicity data in the XSS array
 */
TabulatedFissionMultiplicity( Iterator begin, Iterator end ) :
  Base( "NU::TABLE", begin, end ) {

  this->generateBlocks();
}

TabulatedFissionMultiplicity& operator=( const TabulatedFissionMultiplicity& ) = default;
TabulatedFissionMultiplicity& operator=( TabulatedFissionMultiplicity&& ) = default;
