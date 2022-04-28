NBodyPhaseSpaceDistribution() = default;

NBodyPhaseSpaceDistribution( const NBodyPhaseSpaceDistribution& ) = default;
NBodyPhaseSpaceDistribution( NBodyPhaseSpaceDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] emin    the minimum energy for the distribution
 *  @param[in] emax    the maximum energy for the distribution
 *  @param[in] npsx    the number of particles in the system
 *  @param[in] ap      the total mass ratio
 */
NBodyPhaseSpaceDistribution( double emin, double emax,
                             unsigned int npsx, double ap,
                             unsigned int interpolation,
                             std::vector< double > values,
                             std::vector< double > pdf,
                             std::vector< double > cdf ) :
  Base( "NBodyPhaseSpaceDistribution",
        generateXSS( npsx, ap, interpolation, std::move( values ),
                     std::move( pdf ), std::move( cdf ) ) ),
  emin_( emin ), emax_( emax ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the block
 *  @param[in] end     the end iterator of the block
 *  @param[in] emin    the minimum energy for the distribution
 *  @param[in] emax    the maximum energy for the distribution
 */
NBodyPhaseSpaceDistribution( Iterator begin, Iterator end,
                             double emin, double emax ) :
  Base( "NBodyPhaseSpaceDistribution", begin, end ),
  emin_( emin ), emax_( emax ) {

  verifySize( this->begin(), this->end() );
}

NBodyPhaseSpaceDistribution& operator=( const NBodyPhaseSpaceDistribution& ) = default;
NBodyPhaseSpaceDistribution& operator=( NBodyPhaseSpaceDistribution&& ) = default;
