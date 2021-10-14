AngularDistributionData() = default;

AngularDistributionData( const AngularDistributionData& ) = default;
AngularDistributionData( AngularDistributionData&& ) = default;

// /**
//  *  @brief Constructor
//  *
//  *  @param[in] xs    the cross section data
//  */
// AngularDistributionData( std::vector< Distribution >&& distributions ) :
//   AngularDistributionData( std::move( xs ), xs.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] lsig    the begin iterator of the LSIG block in the XSS array
 *  @param[in] sig     the begin iterator of the SIG block in the XSS array
 *  @param[in] end     the end iterator of the SIG block in the XSS array
 *  @param[in] ntr     the number of reactions (excluding elastic)
 */
AngularDistributionData( std::size_t locb, Iterator begin, Iterator end ) :
  Base( "AND::AngularDistributionData", begin, end ), locb_( locb ) {

  verifySize( this->begin(), this->end(), this->numberIncidentEnergies() );
}

AngularDistributionData& operator=( const AngularDistributionData& ) = default;
AngularDistributionData& operator=( AngularDistributionData&& ) = default;
