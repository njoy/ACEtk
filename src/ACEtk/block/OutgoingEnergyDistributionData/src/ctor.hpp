OutgoingEnergyDistributionData() = default;

OutgoingEnergyDistributionData( const OutgoingEnergyDistributionData& ) = default;
OutgoingEnergyDistributionData( OutgoingEnergyDistributionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] boundaries       the interpolation range boundaries
 *  @param[in] interpolants     the interpolation types for each range
 *  @param[in] distributions    the distributions for each incident energy
 *  @param[in] locb             the starting xss index with respect to the superblock
 */
OutgoingEnergyDistributionData(
    std::vector< long > boundaries,
    std::vector< long > interpolants,
    std::vector< TabulatedOutgoingEnergyDistribution > distributions,
    std::size_t locb = 1 ) :
  BaseDistributionData( "DLW::OutgoingEnergyDistributionData",
                        std::move( boundaries ), std::move( interpolants ),
                        std::move( distributions ), locb ) {}

/**
 *  @brief Constructor without interpolation data
 *
 *  @param[in] distributions    the distributions for each incident energy
 *  @param[in] locb             the starting xss index with respect to the superblock
 */
OutgoingEnergyDistributionData(
    std::vector< TabulatedOutgoingEnergyDistribution > distributions,
    std::size_t locb = 1 ) :
  OutgoingEnergyDistributionData( {}, {}, std::move( distributions ), locb ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] locb    the starting xss index with respect to the superblock
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
OutgoingEnergyDistributionData( std::size_t locb, Iterator begin, Iterator end ) :
  BaseDistributionData( "DLW::OutgoingEnergyDistributionData", locb,
                        begin, end ) {}

OutgoingEnergyDistributionData& operator=( const OutgoingEnergyDistributionData& ) = default;
OutgoingEnergyDistributionData& operator=( OutgoingEnergyDistributionData&& ) = default;
