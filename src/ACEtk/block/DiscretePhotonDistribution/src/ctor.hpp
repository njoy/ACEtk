DiscretePhotonDistribution() = default;

DiscretePhotonDistribution( const DiscretePhotonDistribution& ) = default;
DiscretePhotonDistribution( DiscretePhotonDistribution&& ) = default;

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
  Base( "DLW::DiscretePhotonDistribution", { static_cast< double >( lp ),
                                             energy } ),
  emin_( emin ), emax_( emax ) {}

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
  Base( "DLW::DiscretePhotonDistribution", begin, end ),
  emin_( emin ), emax_( emax ) {

  verifySize( this->begin(), this->end() );
}

DiscretePhotonDistribution& operator=( const DiscretePhotonDistribution& ) = default;
DiscretePhotonDistribution& operator=( DiscretePhotonDistribution&& ) = default;
