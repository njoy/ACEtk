RadiationStoppingPowerBlock() = default;

RadiationStoppingPowerBlock( const RadiationStoppingPowerBlock& ) = default;
RadiationStoppingPowerBlock( RadiationStoppingPowerBlock&& ) = default;

RadiationStoppingPowerBlock& operator=( const RadiationStoppingPowerBlock& ) = default;
RadiationStoppingPowerBlock& operator=( RadiationStoppingPowerBlock&& ) = default;

/**
 *  @brief Constructor (NEL != 3)
 *
 *  @param[in] energies           the energy values
 *  @param[in] stopping_powers    the normalized radiative stopping power values
 */
RadiationStoppingPowerBlock( std::vector< double > energies,
                             std::vector< double > stopping_powers ) :
  ArrayData( "RAD",
             std::move( energies), std::move( stopping_powers ) ) {}

/**
 *  @brief Constructor (NEL == 3)
 *
 *  @param[in] energies           the energy values
 *  @param[in] stopping_powers    the normalized radiative stopping power values
 *  @param[in] corrections        the electron-electron bremsstrahlung correction values
 */
RadiationStoppingPowerBlock( std::vector< double > energies,
                             std::vector< double > stopping_powers,
                             std::vector< double > corrections ) :
  ArrayData( "RAD",
             std::move( energies), std::move( stopping_powers ),
             std::move( corrections ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the RAD block in the XSS array
 *  @param[in] end     the end iterator of the RAD block in the XSS array
 *  @param[in] nrad    the number of energy points
 *  @param[in] nel     the el data format flag (0 or 3)
 */
RadiationStoppingPowerBlock( Iterator begin,
                             Iterator end,
                             unsigned int nrad,
                             unsigned int nel ) :
  ArrayData( "RAD", begin, end, nrad, ( nel == 3 ) ? 3 : 2 ) {}
