ParameterData() = default;

ParameterData( const ParameterData& ) = default;
ParameterData( ParameterData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] energies        the energy values
 *  @param[in] values          the parameter values
 */
ParameterData( std::vector< long > boundaries,
               std::vector< long > interpolants,
               std::vector< double > energies,
               std::vector< double > values ) :
  TabulatedData( "ParameterData", std::move( boundaries ), std::move( interpolants ),
                 std::move( energies ), std::move( values ) ) {}

/**
 *  @brief Constructor (linear interpolation is assumed)
 *
 *  @param[in] energies        the energy values
 *  @param[in] values          the parameter values
 */
ParameterData( std::vector< double > energies,
               std::vector< double > values ) :
  ParameterData( {}, {}, std::move( energies ), std::move( values ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the block in the XSS array
 *  @param[in] end      the end iterator of the block in the XSS array
 */
ParameterData( Iterator begin, Iterator end ) :
  TabulatedData( "ParameterData", begin, end ) {}

ParameterData& operator=( const ParameterData& ) = default;
ParameterData& operator=( ParameterData&& ) = default;
