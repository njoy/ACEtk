KalbachMannDistributionData() = default;

KalbachMannDistributionData( const KalbachMannDistributionData& ) = default;
KalbachMannDistributionData( KalbachMannDistributionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] boundaries       the interpolation range boundaries
 *  @param[in] interpolants     the interpolation types for each range
 *  @param[in] distributions    the distributions for each incident energy
 *  @param[in] locb             the starting xss index with respect to the superblock
 */
KalbachMannDistributionData(
    std::vector< long > boundaries,
    std::vector< long > interpolants,
    std::vector< TabulatedKalbachMannDistribution > distributions,
    std::size_t locb = 1 ) :
  DistributionData( "KalbachMannDistributionData",
                    std::move( boundaries ), std::move( interpolants ),
                    std::move( distributions ), locb ) {}

/**
 *  @brief Constructor without interpolation data
 *
 *  @param[in] distributions    the distributions for each incident energy
 *  @param[in] locb             the starting xss index with respect to the superblock
 */
KalbachMannDistributionData(
    std::vector< TabulatedKalbachMannDistribution > distributions,
    std::size_t locb = 1 ) :
  KalbachMannDistributionData( {}, {}, std::move( distributions ), locb ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] locb    the starting xss index with respect to the superblock
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
KalbachMannDistributionData( std::size_t locb, Iterator begin, Iterator end ) :
  DistributionData( "KalbachMannDistributionData", locb, begin, end ) {}

KalbachMannDistributionData& operator=( const KalbachMannDistributionData& ) = default;
KalbachMannDistributionData& operator=( KalbachMannDistributionData&& ) = default;
