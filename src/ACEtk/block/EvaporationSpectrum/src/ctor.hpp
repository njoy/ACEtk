EvaporationSpectrum() = default;

EvaporationSpectrum( const EvaporationSpectrum& ) = default;
EvaporationSpectrum( EvaporationSpectrum&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] energies        the energy values
 *  @param[in] temperatures    the temperature values
 *  @param[in] energy          the restriction energy
 */
EvaporationSpectrum(
    std::vector< long > boundaries,
    std::vector< long > interpolants,
    std::vector< double > energies,
    std::vector< double > temperatures,
    double energy ) :
  BaseEvaporationSpectrum(
        "EvaporationSpectrum",
        EnergyDistributionType::Evaporation,
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
EvaporationSpectrum(
    std::vector< double >&& energies,
    std::vector< double >&& temperatures,
    double energy ) :
  EvaporationSpectrum(
      {}, {}, std::move( energies ), std::move( temperatures ), energy ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] locb    the starting xss index with respect to the superblock
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
EvaporationSpectrum( Iterator begin, Iterator end ) :
  BaseEvaporationSpectrum( "EvaporationSpectrum",
                           EnergyDistributionType::Evaporation,
                           begin, end ) {}

EvaporationSpectrum& operator=( const EvaporationSpectrum& ) = default;
EvaporationSpectrum& operator=( EvaporationSpectrum&& base ) = default;
