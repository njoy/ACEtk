TabulatedAngleEnergyDistribution() = default;

TabulatedAngleEnergyDistribution( const TabulatedAngleEnergyDistribution& ) = default;
TabulatedAngleEnergyDistribution( TabulatedAngleEnergyDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] incident         the incident energy value
 *  @param[in] interpolation    the interpolation type
 *  @param[in] distributions    the distributions for each outgoing energy
 *  @param[in] locb             the starting xss index with respect to the superblock
 */
TabulatedAngleEnergyDistribution(
    double incident,
    int interpolation,
    std::vector< TabulatedEnergyDistribution > distributions,
    std::size_t locb = 1 ) :
  DistributionDataWithInterpolationType( "TabulatedAngleEnergyDistribution",
                                         interpolation,
                                         std::move( distributions ), locb ),
  incident_( incident ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] incident   the incident energy value
 *  @param[in] locb       the starting xss index with respect to the superblock
 *  @param[in] sig        the begin iterator of the block in the XSS array
 *  @param[in] end        the end iterator of the block in the XSS array
 */
TabulatedAngleEnergyDistribution( double incident, std::size_t locb,
                                  Iterator begin, Iterator end ) :
  DistributionDataWithInterpolationType( "TabulatedAngleEnergyDistribution",
                                         locb, begin, end ),
  incident_( incident ) {}

TabulatedAngleEnergyDistribution& operator=( const TabulatedAngleEnergyDistribution& ) = default;
TabulatedAngleEnergyDistribution& operator=( TabulatedAngleEnergyDistribution&& ) = default;
