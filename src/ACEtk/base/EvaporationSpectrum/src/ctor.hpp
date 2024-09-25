EvaporationSpectrum() = default;

EvaporationSpectrum( const EvaporationSpectrum& base ) :
  Base( base ), tabulated_( base.tabulated_ ),
  type_( base.type_ ) {

  if ( Base::owner() ) {

    this->generateBlocks();
  }
}

EvaporationSpectrum( EvaporationSpectrum&& base ) :
  Base( std::move( base ) ), tabulated_( std::move( base.tabulated_ ) ),
  type_( base.type_ ) {

  if ( Base::owner() ) {

    this->generateBlocks();
  }
}

/**
 *  @brief Constructor
 *
 *  @param[in] name            the name of the block
 *  @param[in] type            the energy distribution type
 *  @param[in] boundaries      the interpolation range boundaries
 *  @param[in] interpolants    the interpolation types for each range
 *  @param[in] energies        the energy values
 *  @param[in] temperatures    the temperature values
 *  @param[in] energy          the restriction energy
 */
EvaporationSpectrum( std::string name, EnergyDistributionType type,
                     std::vector< long > boundaries, std::vector< long > interpolants,
                     std::vector< double > energies, std::vector< double > temperatures,
                     double energy ) :
  Base( std::move( name ),
        generateXSS( std::move( boundaries ), std::move( interpolants ),
                     std::move( energies ), std::move( temperatures ),
                     energy ) ),
  type_( type ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] name     the name of the block
 *  @param[in] type     the energy distribution type
 *  @param[in] begin    the begin iterator of the block in the XSS array
 *  @param[in] end      the end iterator of the block in the XSS array
 */
EvaporationSpectrum( std::string name, EnergyDistributionType type,
                     Iterator begin, Iterator end ) :
  Base( std::move( name ), begin, end ), type_( type ) {

  const auto nr = static_cast< std::size_t >( std::round( this->XSS( 1 ) ) );
  const auto ne = static_cast< std::size_t >( std::round( this->XSS( 1 + 2 * nr + 1 ) ) );
  verifySize( this->begin(), this->end(), nr, ne );
  this->generateBlocks();
}

EvaporationSpectrum& operator=( const EvaporationSpectrum& base ) {

  if ( this != &base ) {

    Base::operator=( base );
    this->tabulated_ = base.tabulated_;
    this->type_ = base.type_;
    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }
  return *this;
}

EvaporationSpectrum& operator=( EvaporationSpectrum&& base ) {

  if ( this != &base ) {

    Base::operator=( std::move( base ) );
    this->tabulated_ = std::move( base.tabulated_ );
    this->type_ = base.type_;
    if ( Base::owner() ) {

      this->generateBlocks();
    }
  }
  return *this;
}
