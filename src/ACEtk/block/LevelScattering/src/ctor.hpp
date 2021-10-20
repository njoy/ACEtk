LevelScattering() = default;

LevelScattering( const LevelScattering& ) = default;
LevelScattering( LevelScattering&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] emin    the minimum energy for the distribution
 *  @param[in] emax    the maximum energy for the distribution
 *  @param[in] c1      the value of C1 = ( A + 1 ) / A * abs( Q )
 *  @param[in] c2      the value of C2 = ( A / ( A + 1 ) )^2
 */
LevelScattering( double emin, double emax, double c1, double c2 ) :
  Base( "DLW::LevelScattering", { c1, c2 } ), emin_( emin ), emax_( emax ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the blcok
 *  @param[in] end     the end iterator of the block
 *  @param[in] emin    the minimum energy for the distribution
 *  @param[in] emax    the maximum energy for the distribution
 */
LevelScattering( Iterator begin, Iterator end, double emin, double emax ) :
  Base( "DLW::LevelScattering", begin, end ), emin_( emin ), emax_( emax ) {

  verifySize( this->begin(), this->end() );
}

LevelScattering& operator=( const LevelScattering& ) = default;
LevelScattering& operator=( LevelScattering&& ) = default;
