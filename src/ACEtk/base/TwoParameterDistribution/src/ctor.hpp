TwoParameterDistribution() = default;

TwoParameterDistribution( const TwoParameterDistribution& ) = default;
TwoParameterDistribution( TwoParameterDistribution&& ) = default;

TwoParameterDistribution& operator=( const TwoParameterDistribution& ) = default;
TwoParameterDistribution& operator=( TwoParameterDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] name    the name of the block
 *  @param[in] emin    the minimum energy for the distribution
 *  @param[in] emax    the maximum energy for the distribution
 *  @param[in] c1      the value of C1
 *  @param[in] c2      the value of C2
 */
TwoParameterDistribution( std::string name, double emin, double emax,
                          double c1, double c2 ) :
  Base( std::move( name ), { c1, c2 } ),
  emin_( emin ), emax_( emax ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] name    the name of the block
 *  @param[in] begin   the begin iterator of the block
 *  @param[in] end     the end iterator of the block
 *  @param[in] emin    the minimum energy for the distribution
 *  @param[in] emax    the maximum energy for the distribution
 */
TwoParameterDistribution( std::string name, Iterator begin, Iterator end,
                          double emin, double emax ) :
  Base( std::move( name ), begin, end ),
  emin_( emin ), emax_( emax ) {

  verifySize( this->begin(), this->end() );
}
