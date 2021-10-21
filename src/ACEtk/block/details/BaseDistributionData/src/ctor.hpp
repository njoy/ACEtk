BaseDistributionData() = default;

BaseDistributionData( const BaseDistributionData& ) = default;
BaseDistributionData( BaseDistributionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] name             the name of the block
 *  @param[in] boundaries       the interpolation range boundaries
 *  @param[in] interpolants     the interpolation types for each range
 *  @param[in] distributions    the distributions for each incident energy
 *  @param[in] locb             the starting xss index with respect to the superblock
 */
BaseDistributionData( std::string&& name,
                      std::vector< long >&& boundaries,
                      std::vector< long >&& interpolants,
                      std::vector< Distribution >&& distributions,
                      std::size_t locb = 1 ) :
  Base( name, generateXSS( std::move( name ),
                           std::move( boundaries ), std::move( interpolants ),
                           std::move( distributions ), locb ) ),
  locb_( locb ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] locb    the starting xss index with respect to the superblock
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
BaseDistributionData( std::string&& name, std::size_t locb,
                      Iterator begin, Iterator end ) :
  Base( std::move( name ), begin, end ), locb_( locb ) {

  verifySize( this->begin(), this->end(),
              this->numberInterpolationRegions(),
              this->numberIncidentEnergies() );
  this->generateBlocks();
}

BaseDistributionData& operator=( const BaseDistributionData& ) = default;
BaseDistributionData& operator=( BaseDistributionData&& ) = default;
