/**
 *  @brief Copy constructor using a generic table
 *
 *  @param[in] table    the generic table to be copied
 */
PhotoAtomicTable( const Table& table ): Table( table ) {

  this->generateBlocks();
}

/**
 *  @brief Move constructor using a generic table
 *
 *  @param[in] table    the generic table to be moved
 */
PhotoAtomicTable( Table&& table ): Table( std::move( table ) ) {

  this->generateBlocks();
}

/**
 *  @brief Copy constructor using a thermal scattering table
 *
 *  @param[in] table    the thermal scattering table to be copied
 */
PhotoAtomicTable( const PhotoAtomicTable& table ) :
  Table( table ) {

  this->generateBlocks();
}

/**
 *  @brief Move constructor using a thermal scattering table
 *
 *  @param[in] table    the thermal scattering table to be moved
 */
PhotoAtomicTable( PhotoAtomicTable&& table ) :
  Table( std::move( table ) ) {

  this->generateBlocks();
}

/**
 *  @brief Copy assignment using a thermal scattering table
 *
 *  @param[in] table    the thermal scattering table to be copied
 */
PhotoAtomicTable& operator=( const PhotoAtomicTable& base ) {

  new (this) PhotoAtomicTable( base );
  return *this;
}

/**
 *  @brief Move assignment using a thermal scattering table
 *
 *  @param[in] table    the thermal scattering table to be moved
 */
PhotoAtomicTable& operator=( PhotoAtomicTable&& base ) {

  new (this) PhotoAtomicTable( std::move( base ) );
  return *this;
}

/**
 *  @brief Constructor (from scratch)
 *
 *  @param[in] header    the header for the table
 *  @param[in] za        the list of ZA values
 *  @param[in] itie      the inelastic thermal scattering cross section block
 *  @param[in] itxe      the inelastic thermal scattering angular distribution block
 *  @param[in] itce      the coherent elastic thermal scattering cross section block
 *  @param[in] itca      the coherent elastic thermal scattering angular distribution block
 *  @param[in] itcei     the incoherent elastic thermal scattering cross section block
 *  @param[in] itcai     the incoherent elastic thermal scattering angular distribution block
 */
PhotoAtomicTable( Header header,
                  std::vector< unsigned int > za, std::vector< double > awr,
                  block::ESZG eszg, block::JINC jinc,
                  block::JCOH jcoh, block::LHNM lhnm ) :
  PhotoAtomicTable(
      Table( std::move( header ),
             generateData( std::move( za ), std::move( awr ),
                           std::move( eszg ), std::move( jinc ),
                           std::move( jcoh ), std::move( lhnm ) ) ) ) {}
