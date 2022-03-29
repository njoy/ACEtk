EnergyAngleDistributionData() = default;

EnergyAngleDistributionData( const EnergyAngleDistributionData& ) = default;
EnergyAngleDistributionData( EnergyAngleDistributionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] boundaries       the interpolation range boundaries
 *  @param[in] interpolants     the interpolation types for each range
 *  @param[in] distributions    the distributions for each incident energy
 *  @param[in] locb             the starting xss index with respect to the superblock
 */
EnergyAngleDistributionData(
    std::vector< long > boundaries,
    std::vector< long > interpolants,
    std::vector< TabulatedEnergyAngleDistribution > distributions,
    std::size_t locb = 1 ) :
  BaseDistributionData( "EnergyAngleDistributionData",
                        std::move( boundaries ), std::move( interpolants ),
                        std::move( distributions ), 2, locb ) {}

/**
 *  @brief Constructor without interpolation data
 *
 *  @param[in] distributions    the distributions for each incident energy
 *  @param[in] locb             the starting xss index with respect to the superblock
 */
EnergyAngleDistributionData(
    std::vector< TabulatedEnergyAngleDistribution > distributions,
    std::size_t locb = 1 ) :
  EnergyAngleDistributionData( {}, {}, std::move( distributions ), locb ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] locb    the starting xss index with respect to the superblock
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
EnergyAngleDistributionData( std::size_t locb, Iterator begin, Iterator end ) :
  BaseDistributionData( "EnergyAngleDistributionData", 2, locb,
                        begin, end ) {}

EnergyAngleDistributionData& operator=( const EnergyAngleDistributionData& ) = default;
EnergyAngleDistributionData& operator=( EnergyAngleDistributionData&& ) = default;
