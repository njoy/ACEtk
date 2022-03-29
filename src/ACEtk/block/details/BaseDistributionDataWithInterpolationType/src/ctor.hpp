BaseDistributionDataWithInterpolationType() = default;

BaseDistributionDataWithInterpolationType( const BaseDistributionDataWithInterpolationType& base ) :
  Base( base ), locb_( base.locb_ ) {

  static_cast< Derived* >( this )->generateBlocks();
}

BaseDistributionDataWithInterpolationType( BaseDistributionDataWithInterpolationType&& base ) :
  Base( std::move( base ) ), locb_( base.locb_ ) {

    static_cast< Derived* >( this )->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] name             the name of the block
 *  @param[in] interpolation    the interpolation type
 *  @param[in] distributions    the distributions for each incident energy
 *  @param[in] locb             the starting xss index with respect to the superblock
 */
BaseDistributionDataWithInterpolationType( std::string&& name,
                                           unsigned int interpolation,
                                           std::vector< Distribution >&& distributions,
                                           std::size_t locb ) :
  Base( std::move( name ),
        Derived::generateXSS( std::string( name ), interpolation,
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
BaseDistributionDataWithInterpolationType( std::string&& name,
                                           std::size_t locb,
                                           Iterator begin, Iterator end ) :
  Base( std::move( name ), begin, end ), locb_( locb ) {

  std::size_t ne = static_cast< std::size_t >( this->XSS( 2 ) );
  verifySize( this->begin(), this->end(), ne );
  static_cast< Derived* >( this )->generateBlocks();
}

BaseDistributionDataWithInterpolationType& operator=( const BaseDistributionDataWithInterpolationType& base ) {

  new (this) BaseDistributionDataWithInterpolationType( base );
  return *this;
}

BaseDistributionDataWithInterpolationType& operator=( BaseDistributionDataWithInterpolationType&& base ) {

  new (this) BaseDistributionDataWithInterpolationType( std::move( base ) );
  return *this;
}
