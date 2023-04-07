SimpleMaxwellianFissionSpectrum() = default;

SimpleMaxwellianFissionSpectrum( const SimpleMaxwellianFissionSpectrum& ) = default;
SimpleMaxwellianFissionSpectrum( SimpleMaxwellianFissionSpectrum&& ) = default;

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
    std::vector< long > boundaries,
    std::vector< long > interpolants,
    std::vector< double > energies,
    std::vector< double > temperatures,
    double energy ) :
  BaseEvaporationSpectrum(
        "DLW::SimpleMaxwellianFissionSpectrum",
        EnergyDistributionType::SimpleMaxwellianFission,
        std::move( boundaries ), std::move( interpolants ),
        std::move( energies ), std::move( temperatures ),
        energy ) {}

/**
 *  @brief Constructor without interpolation data
 *
 *  @param[in] energies        the energy values
 *  @param[in] temperatures    the temperature values
 *  @param[in] energy          the restriction energy
 */
SimpleMaxwellianFissionSpectrum(
    std::vector< double > energies,
    std::vector< double > temperatures,
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
  BaseEvaporationSpectrum( "DLW::SimpleMaxwellianFissionSpectrum",
                           EnergyDistributionType::SimpleMaxwellianFission,
                           begin, end ) {}

SimpleMaxwellianFissionSpectrum& operator=( const SimpleMaxwellianFissionSpectrum& ) = default;
SimpleMaxwellianFissionSpectrum& operator=( SimpleMaxwellianFissionSpectrum&& base ) = default;
