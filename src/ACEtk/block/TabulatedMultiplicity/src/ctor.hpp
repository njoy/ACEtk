TabulatedMultiplicity() = default;

TabulatedMultiplicity( const TabulatedMultiplicity& ) = default;
TabulatedMultiplicity( TabulatedMultiplicity&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] boundaries        the interpolation range boundaries
 *  @param[in] interpolants      the interpolation types for each range
 *  @param[in] energies          the energy values
 *  @param[in] multiplicities    the parameter values
 */
TabulatedMultiplicity( std::vector< long > boundaries,
                       std::vector< long > interpolants,
                       std::vector< double > energies,
                       std::vector< double > values ) :
  BaseTabulatedData( "TabulatedMultiplicity",
                     std::move( boundaries ), std::move( interpolants ),
                     std::move( energies ), std::move( values ) ) {}

/**
 *  @brief Constructor (linear interpolation is assumed)
 *
 *  @param[in] energies          the energy values
 *  @param[in] multiplicities    the parameter values
 */
TabulatedMultiplicity( std::vector< double > energies,
                       std::vector< double > values ) :
  TabulatedMultiplicity( {}, {}, std::move( energies ), std::move( values ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the block in the XSS array
 *  @param[in] end      the end iterator of the block in the XSS array
 */
TabulatedMultiplicity( Iterator begin, Iterator end ) :
  BaseTabulatedData( "TabulatedMultiplicity", begin, end ) {}

TabulatedMultiplicity& operator=( const TabulatedMultiplicity& ) = default;
TabulatedMultiplicity& operator=( TabulatedMultiplicity&& ) = default;
