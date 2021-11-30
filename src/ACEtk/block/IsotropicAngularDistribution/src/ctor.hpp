IsotropicAngularDistribution() = default;

IsotropicAngularDistribution( const IsotropicAngularDistribution& ) = default;
IsotropicAngularDistribution( IsotropicAngularDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energy    the associated energy value
 */
IsotropicAngularDistribution( double energy ) :
  energy_( energy ) {}

IsotropicAngularDistribution& operator=( const IsotropicAngularDistribution& ) = default;
IsotropicAngularDistribution& operator=( IsotropicAngularDistribution&& ) = default;
