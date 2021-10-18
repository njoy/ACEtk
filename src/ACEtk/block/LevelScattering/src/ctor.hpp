LevelScattering() = default;

LevelScattering( const LevelScattering& ) = default;
LevelScattering( LevelScattering&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] c1    the value of C1 = ( A + 1 ) / A * abs( Q )
 *  @param[in] c2    the value of C2 = ( A / ( A + 1 ) )^2
 */
LevelScattering( double c1, double c2 ) :
  Base( "DLW::LevelScattering", { c1, c2 } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] mtr   the begin iterator of the MTR block in the XSS array
 *  @param[in] end   the end iterator of the MTR block in the XSS array
 *  @param[in] ntr   the number of reactions (excluding elastic)
 */
LevelScattering( Iterator begin, Iterator end ) :
  Base( "DLW::LevelScattering", begin, end ) {

  verifySize( this->begin(), this->end() );
}

LevelScattering& operator=( const LevelScattering& ) = default;
LevelScattering& operator=( LevelScattering&& ) = default;
