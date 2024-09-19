AngleEnergyDistributionData() = default;

AngleEnergyDistributionData( const AngleEnergyDistributionData& ) = default;
AngleEnergyDistributionData( AngleEnergyDistributionData&& ) = default;

AngleEnergyDistributionData& operator=( const AngleEnergyDistributionData& ) = default;
AngleEnergyDistributionData& operator=( AngleEnergyDistributionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] boundaries       the interpolation range boundaries
 *  @param[in] interpolants     the interpolation types for each range
 *  @param[in] distributions    the distributions for each incident energy
 *  @param[in] locb             the starting xss index with respect to the superblock
 */
AngleEnergyDistributionData(
    std::vector< long > boundaries,
    std::vector< long > interpolants,
    std::vector< TabulatedAngleEnergyDistribution > distributions,
    std::size_t locb = 1 ) :
  DistributionData( "AngleEnergyDistributionData",
                    std::move( boundaries ), std::move( interpolants ),
                    std::move( distributions ), locb ) {}

/**
 *  @brief Constructor without interpolation data
 *
 *  @param[in] distributions    the distributions for each incident energy
 *  @param[in] locb             the starting xss index with respect to the superblock
 */
AngleEnergyDistributionData(
    std::vector< TabulatedAngleEnergyDistribution > distributions,
    std::size_t locb = 1 ) :
  AngleEnergyDistributionData( {}, {}, std::move( distributions ), locb ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] locb    the starting xss index with respect to the superblock
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
AngleEnergyDistributionData( std::size_t locb, Iterator begin, Iterator end ) :
  DistributionData( "AngleEnergyDistributionData", locb, begin, end ) {}
