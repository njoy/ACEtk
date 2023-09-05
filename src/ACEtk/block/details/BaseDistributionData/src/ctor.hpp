BaseDistributionData() = default;

BaseDistributionData( const BaseDistributionData& base ) :
  Base( base ), locb_( base.locb_ ),
  interpolation_( base.interpolation_ ),
  values_( base.values_ ),
  distributions_( base.distributions_ ) {

  if ( Base::owner() ) {

    this->distributions_.clear();
    static_cast< Derived* >( this )->generateBlocks();
  }
}

BaseDistributionData( BaseDistributionData&& base ) :
  Base( std::move( base ) ), locb_( base.locb_ ),
  interpolation_( std::move( base.interpolation_ ) ),
  values_( std::move( base.values_ ) ),
  distributions_( std::move( base.distributions_ ) ) {

  if ( Base::owner() ) {

    this->distributions_.clear();
    static_cast< Derived* >( this )->generateBlocks();
  }
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
BaseDistributionData( std::string name,
                      std::vector< long > boundaries,
                      std::vector< long > interpolants,
                      std::vector< Distribution > distributions,
                      std::size_t locb ) :
  Base( std::move( name ),
        Derived::generateXSS( std::string( name ),
                              std::move( boundaries ), std::move( interpolants ),
                              std::move( distributions ), locb ) ),
  locb_( locb ) {

  static_cast< Derived* >( this )->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] name    the name of the block
 *  @param[in] locb    the starting xss index with respect to the superblock
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
BaseDistributionData( std::string name, std::size_t locb,
                      Iterator begin, Iterator end ) :
  Base( std::move( name ), begin, end ), locb_( locb ) {

  const auto nr = static_cast< std::size_t >( std::round( this->XSS( 1 ) ) );
  const auto ne = static_cast< std::size_t >( std::round( this->XSS( 1 + 2 * nr + 1 ) ) );
  verifySize( this->begin(), this->end(), nr, ne );
  static_cast< Derived* >( this )->generateBlocks();
}

BaseDistributionData& operator=( const BaseDistributionData& base ) {

  new (this) BaseDistributionData( base );
  return *this;
}

BaseDistributionData& operator=( BaseDistributionData&& base ) {

  new (this) BaseDistributionData( std::move( base ) );
  return *this;
}
