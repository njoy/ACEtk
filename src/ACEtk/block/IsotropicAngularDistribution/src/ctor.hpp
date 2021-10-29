IsotropicAngularDistribution() = default;

IsotropicAngularDistribution( const IsotropicAngularDistribution& ) = default;
IsotropicAngularDistribution( IsotropicAngularDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] incident        the incident energy value
 */
IsotropicAngularDistribution( double incident ) :
  incident_( incident ) {}

IsotropicAngularDistribution& operator=( const IsotropicAngularDistribution& ) = default;
IsotropicAngularDistribution& operator=( IsotropicAngularDistribution&& ) = default;
