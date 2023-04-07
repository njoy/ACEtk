EquiprobableOutgoingEnergyBinData() = default;

EquiprobableOutgoingEnergyBinData( const EquiprobableOutgoingEnergyBinData& base ) :
  Base( base ) {

  this->generateBlocks();
}

EquiprobableOutgoingEnergyBinData( EquiprobableOutgoingEnergyBinData&& base ) :
  Base( std::move( base ) ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] boundaries       the interpolation range boundaries
 *  @param[in] interpolants     the interpolation types for each range
 *  @param[in] distributions    the distributions for each incident energy
 */
EquiprobableOutgoingEnergyBinData(
    std::vector< long > boundaries,
    std::vector< long > interpolants,
    std::vector< EquiprobableOutgoingEnergyBins > distributions ) :
  Base( "DLW::EquiprobableOutgoingEnergyBinData",
        generateXSS( std::move( boundaries ), std::move( interpolants ),
                     std::move( distributions ) ) ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor without interpolation data
 *
 *  @param[in] distributions    the distributions for each incident energy
 */
EquiprobableOutgoingEnergyBinData(
    std::vector< EquiprobableOutgoingEnergyBins >&& distributions ) :
  EquiprobableOutgoingEnergyBinData( {}, {}, std::move( distributions ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] locb    the starting xss index with respect to the superblock
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
EquiprobableOutgoingEnergyBinData( Iterator begin, Iterator end ) :
  Base( "DLW::EquiprobableOutgoingEnergyBinData", begin, end ) {

  std::size_t nr = static_cast< std::size_t >( this->XSS( 1 ) );
  std::size_t ne = static_cast< std::size_t >( this->XSS( 1 + 2 * nr + 1 ) );
  std::size_t nb = static_cast< std::size_t >( this->XSS( 1 + 2 * nr + 1 + ne + 1 ) );
  verifySize( this->begin(), this->end(), nr, ne, nb );
  this->generateBlocks();
}

EquiprobableOutgoingEnergyBinData& operator=( const EquiprobableOutgoingEnergyBinData& base ) {

  new (this) EquiprobableOutgoingEnergyBinData( base );
  return *this;
}

EquiprobableOutgoingEnergyBinData& operator=( EquiprobableOutgoingEnergyBinData&& base ) {

  new (this) EquiprobableOutgoingEnergyBinData( std::move( base ) );
  return *this;
}
