TabulatedEnergyAngleDistribution() = default;

TabulatedEnergyAngleDistribution( const TabulatedEnergyAngleDistribution& ) = default;
TabulatedEnergyAngleDistribution( TabulatedEnergyAngleDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] incident         the incident energy value
 *  @param[in] interpolation    the interpolation type
 *  @param[in] distributions    the distributions for each outgoing energy
 *  @param[in] locb             the starting xss index with respect to the superblock
 */
TabulatedEnergyAngleDistribution(
    double incident,
    int interpolation,
    std::vector< TabulatedAngularDistributionWithProbability > distributions,
    std::size_t locb = 1 ) :
  DistributionDataWithInterpolationType( "TabulatedEnergyAngleDistribution",
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
TabulatedEnergyAngleDistribution( double incident, std::size_t locb,
                                  Iterator begin, Iterator end ) :
  DistributionDataWithInterpolationType( "TabulatedEnergyAngleDistribution",
                                         locb, begin, end ),
  incident_( incident ) {}

TabulatedEnergyAngleDistribution& operator=( const TabulatedEnergyAngleDistribution& ) = default;
TabulatedEnergyAngleDistribution& operator=( TabulatedEnergyAngleDistribution&& ) = default;
