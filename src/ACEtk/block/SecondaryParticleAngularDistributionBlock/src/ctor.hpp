SecondaryParticleAngularDistributionBlock() = default;

SecondaryParticleAngularDistributionBlock( const SecondaryParticleAngularDistributionBlock& ) = default;

SecondaryParticleAngularDistributionBlock( SecondaryParticleAngularDistributionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] data    the ditribution data for all reactions
 */
SecondaryParticleAngularDistributionBlock( std::vector< DistributionData > data ) :
  BaseAngularDistributionBlock( "ANDH", std::move( data ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] loc     the begin iterator of the LSIG block in the XSS array
 *  @param[in] data    the begin iterator of the SIG block in the XSS array
 *  @param[in] end     the end iterator of the SIG block in the XSS array
 *  @param[in] nr      the number of reactions (excluding elastic)
 */
SecondaryParticleAngularDistributionBlock( Iterator loc, Iterator data,
                                           Iterator end, unsigned int nr ) :
  BaseAngularDistributionBlock( "ANDH", loc, data, end, nr, false ) {}

SecondaryParticleAngularDistributionBlock& operator=( const SecondaryParticleAngularDistributionBlock& ) = default;

SecondaryParticleAngularDistributionBlock& operator=( SecondaryParticleAngularDistributionBlock&& ) = default;
