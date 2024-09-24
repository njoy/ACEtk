DiscretePhotonDistribution() = default;

DiscretePhotonDistribution( const DiscretePhotonDistribution& ) = default;
DiscretePhotonDistribution( DiscretePhotonDistribution&& ) = default;

DiscretePhotonDistribution& operator=( const DiscretePhotonDistribution& ) = default;
DiscretePhotonDistribution& operator=( DiscretePhotonDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] emin      the minimum energy for the distribution
 *  @param[in] emax      the maximum energy for the distribution
 *  @param[in] lp        the primary photon flag (0, 1 or 2)
 *  @param[in] energy    the photon or binding energy
 */
DiscretePhotonDistribution( double emin, double emax,
                            unsigned int lp, double energy ) :
  TwoParameterDistribution( "DiscretePhotonDistribution", emin, emax,
                            static_cast< double >( lp ), energy ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the block
 *  @param[in] end     the end iterator of the block
 *  @param[in] emin    the minimum energy for the distribution
 *  @param[in] emax    the maximum energy for the distribution
 */
DiscretePhotonDistribution( Iterator begin, Iterator end,
                            double emin, double emax ) :
  TwoParameterDistribution( "DiscretePhotonDistribution", begin, end, emin, emax ) {}
