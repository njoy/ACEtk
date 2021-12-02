LevelScatteringDistribution() = default;

LevelScatteringDistribution( const LevelScatteringDistribution& ) = default;
LevelScatteringDistribution( LevelScatteringDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] emin    the minimum energy for the distribution
 *  @param[in] emax    the maximum energy for the distribution
 *  @param[in] c1      the value of C1 = ( A + 1 ) / A * abs( Q )
 *  @param[in] c2      the value of C2 = ( A / ( A + 1 ) )^2
 */
LevelScatteringDistribution( double emin, double emax, double c1, double c2 ) :
  BaseTwoParameterDistribution( "LevelScatteringDistribution",
                                emin, emax, c1, c2 ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the block
 *  @param[in] end     the end iterator of the block
 *  @param[in] emin    the minimum energy for the distribution
 *  @param[in] emax    the maximum energy for the distribution
 */
LevelScatteringDistribution( Iterator begin, Iterator end,
                             double emin, double emax ) :
  BaseTwoParameterDistribution( "LevelScatteringDistribution",
                                begin, end, emin, emax ) {}

LevelScatteringDistribution& operator=( const LevelScatteringDistribution& ) = default;
LevelScatteringDistribution& operator=( LevelScatteringDistribution&& ) = default;
