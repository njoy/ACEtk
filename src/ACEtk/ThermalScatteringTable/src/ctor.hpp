/**
 *  @brief Copy constructor using a generic table
 *
 *  @param[in] table    the generic table to be copied
 */
ThermalScatteringTable( const Table& table ): Table( table ) {

  this->generateBlocks();
}

/**
 *  @brief Move constructor using a generic table
 *
 *  @param[in] table    the generic table to be moved
 */
ThermalScatteringTable( Table&& table ): Table( std::move( table ) ) {

  this->generateBlocks();
}

/**
 *  @brief Copy constructor using a thermal scattering table
 *
 *  @param[in] table    the thermal scattering table to be copied
 */
ThermalScatteringTable( const ThermalScatteringTable& table ) :
  Table( table ) {

  this->generateBlocks();
}

/**
 *  @brief Move constructor using a thermal scattering table
 *
 *  @param[in] table    the thermal scattering table to be moved
 */
ThermalScatteringTable( ThermalScatteringTable&& table ) :
  Table( std::move( table ) ) {

  this->generateBlocks();
}

/**
 *  @brief Copy assignment using a thermal scattering table
 *
 *  @param[in] table    the thermal scattering table to be copied
 */
ThermalScatteringTable& operator=( const ThermalScatteringTable& base ) {

  new (this) ThermalScatteringTable( base );
  return *this;
}

/**
 *  @brief Move assignment using a thermal scattering table
 *
 *  @param[in] table    the thermal scattering table to be moved
 */
ThermalScatteringTable& operator=( ThermalScatteringTable&& base ) {

  new (this) ThermalScatteringTable( std::move( base ) );
  return *this;
}
