TabulatedOutgoingEnergyAngleDistribution() = default;

TabulatedOutgoingEnergyAngleDistribution( const TabulatedOutgoingEnergyAngleDistribution& ) = default;
TabulatedOutgoingEnergyAngleDistribution( TabulatedOutgoingEnergyAngleDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] incident         the incident energy value
 *  @param[in] boundaries       the interpolation range boundaries
 *  @param[in] interpolants     the interpolation types for each range
 *  @param[in] distributions    the distributions for each outgoing energy
 *  @param[in] locb             the starting xss index with respect to the superblock
 */
TabulatedOutgoingEnergyAngleDistribution(
    double incident,
    std::vector< long > boundaries,
    std::vector< long > interpolants,
    std::vector< TabulatedAngularDistribution > distributions,
    std::size_t locb = 1 ) :
  BaseDistributionData( "TabulatedOutgoingEnergyAngleDistribution",
                        std::move( boundaries ), std::move( interpolants ),
                        std::move( distributions ), locb ),
  incident_( incident ) {}

/**
 *  @brief Constructor without interpolation data
 *
 *  @param[in] incident         the incident energy value
 *  @param[in] distributions    the distributions for each incident energy
 *  @param[in] locb             the starting xss index with respect to the superblock
 */
TabulatedOutgoingEnergyAngleDistribution(
    double incident,
    std::vector< TabulatedAngularDistribution > distributions,
    std::size_t locb = 1 ) :
  TabulatedOutgoingEnergyAngleDistribution(
    incident, {}, {}, std::move( distributions ), locb ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] locb    the starting xss index with respect to the superblock
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
TabulatedOutgoingEnergyAngleDistribution( double incident, std::size_t locb,
                                          Iterator begin, Iterator end ) :
  BaseDistributionData( "TabulatedOutgoingEnergyAngleDistribution", locb,
                        begin, end ),
  incident_( incident ) {}

TabulatedOutgoingEnergyAngleDistribution& operator=( const TabulatedOutgoingEnergyAngleDistribution& ) = default;
TabulatedOutgoingEnergyAngleDistribution& operator=( TabulatedOutgoingEnergyAngleDistribution&& ) = default;
