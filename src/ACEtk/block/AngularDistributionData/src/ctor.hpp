AngularDistributionData() = default;

AngularDistributionData( const AngularDistributionData& base ) :
  Base( base ), locb_( base.locb_ ) {

  this->generateBlocks();
}

AngularDistributionData( AngularDistributionData&& base ) :
  Base( std::move( base ) ), locb_( base.locb_ ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] distributions    the angular distributions for each incident energy
 *  @param[in] locb             the starting xss index with respect to the AND block
 */
AngularDistributionData( std::vector< Distribution > distributions,
                         std::size_t locb = 1 ) :
  Base( "AngularDistributionData",
        generateXSS( std::move( distributions ), locb ) ),
  locb_( locb ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] locb    the starting xss index with respect to the AND block
 *  @param[in] begin   the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
AngularDistributionData( std::size_t locb, Iterator begin, Iterator end ) :
  Base( "AngularDistributionData", begin, end ), locb_( locb ) {

  this->generateBlocks();
  verifySize( this->begin(), this->end(), this->numberIncidentEnergies() );
}

AngularDistributionData& operator=( const AngularDistributionData& base ) {

  new (this) AngularDistributionData( base );
  return *this;
}

AngularDistributionData& operator=( AngularDistributionData&& base ) {

  new (this) AngularDistributionData( std::move( base ) );
  return *this;
}
