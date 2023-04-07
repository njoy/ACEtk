AngularDistributionData() = default;

AngularDistributionData( const AngularDistributionData& ) = default;
AngularDistributionData( AngularDistributionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] distributions    the angular distributions for each incident energy
 *  @param[in] locb             the starting xss index with respect to the AND block
 */
AngularDistributionData( std::vector< Distribution > distributions,
                         std::size_t locb = 1 ) :
  Base( "AND::AngularDistributionData",
        generateXSS( std::move( distributions ), locb ) ),
  locb_( locb ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] locb    the starting xss index with respect to the AND block
 *  @param[in] begin   the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
AngularDistributionData( std::size_t locb, Iterator begin, Iterator end ) :
  Base( "AND::AngularDistributionData", begin, end ), locb_( locb ) {

  verifySize( this->begin(), this->end(), this->numberIncidentEnergies() );
}

AngularDistributionData& operator=( const AngularDistributionData& ) = default;
AngularDistributionData& operator=( AngularDistributionData&& ) = default;
