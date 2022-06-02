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

/**
 *  @brief Constructor (from scratch)
 *
 *  @param[in] header    the header for the table
 *  @param[in] itie      the inelastic thermal scattering cross section block
 *  @param[in] itxe      the inelastic thermal scattering angular distribution block
 *  @param[in] itce      the coherent elastic thermal scattering cross section block
 *  @param[in] itca      the coherent elastic thermal scattering angular distribution block
 *  @param[in] itcei     the incoherent elastic thermal scattering cross section block
 *  @param[in] itcai     the incoherent elastic thermal scattering angular distribution block
 */
ThermalScatteringTable( Header header, std::vector< unsigned int > za,
                        block::ITIE itie, block::ITXE itxe,
                        std::optional< block::ITCE > itce,
                        std::optional< block::ITCA > itca,
                        std::optional< block::ITCEI > itcei,
                        std::optional< block::ITCAI > itcai ) :
  ThermalScatteringTable(
      Table( std::move( header ),
             generateData( std::move( za ),
                           std::move( itie ), std::move( itxe ),
                           std::move( itce ), std::move( itca ),
                           std::move( itcei ), std::move( itcai ) ) ) ) {}
