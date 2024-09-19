AngularDistributionBlock() = default;

AngularDistributionBlock( const AngularDistributionBlock& ) = default;
AngularDistributionBlock( AngularDistributionBlock&& ) = default;

AngularDistributionBlock& operator=( const AngularDistributionBlock& ) = default;
AngularDistributionBlock& operator=( AngularDistributionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] elastic    the distribution data for elastic
 *  @param[in] data       the distribution data for the other reactions
 */
AngularDistributionBlock( DistributionData elastic,
                          std::vector< DistributionData > data ) :
  base::AngularDistributionBlock( "AND", std::move( elastic ), std::move( data ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] loc     the begin iterator of the LSIG block in the XSS array
 *  @param[in] data    the begin iterator of the SIG block in the XSS array
 *  @param[in] end     the end iterator of the SIG block in the XSS array
 *  @param[in] nr      the number of reactions (excluding elastic)
 */
AngularDistributionBlock( Iterator loc, Iterator data, Iterator end,
                          unsigned int nr ) :
  base::AngularDistributionBlock( "AND", loc, data, end, nr, true ) {}
