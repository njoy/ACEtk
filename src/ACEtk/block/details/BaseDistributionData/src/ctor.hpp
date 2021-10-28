BaseDistributionData() = default;

BaseDistributionData( const BaseDistributionData& base ) :
  Base( base ), locb_( base.locb_ ) {

  this->generateBlocks();
}

BaseDistributionData( BaseDistributionData&& base ) :
  Base( std::move( base ) ), locb_( base.locb_ ) {

  this->generateBlocks();
}

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
  Base( std::move( name ),
        generateXSS( std::string( name ),
                     std::move( boundaries ), std::move( interpolants ),
                     std::move( distributions ), locb ) ),
  locb_( locb ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] name    the name of the block
 *  @param[in] locb    the starting xss index with respect to the superblock
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
BaseDistributionData( std::string&& name, std::size_t locb,
                      Iterator begin, Iterator end ) :
  Base( std::move( name ), begin, end ), locb_( locb ) {

  std::size_t nr = static_cast< std::size_t >( this->XSS( 1 ) );
  std::size_t ne = static_cast< std::size_t >( this->XSS( 1 + 2 * nr + 1 ) );
  verifySize( this->begin(), this->end(), nr, ne );
  this->generateBlocks();
}

BaseDistributionData& operator=( const BaseDistributionData& base ) {

  new (this) BaseDistributionData( base );
  return *this;
}

BaseDistributionData& operator=( BaseDistributionData&& base ) {

  new (this) BaseDistributionData( std::move( base ) );
  return *this;
}
