/**
 *  @brief Copy constructor using a generic table
 *
 *  @param[in] table    the generic table to be copied
 */
DosimetryTable( const Table& table ): Table( table ) {

  this->verifyType();
  this->generateBlocks();
}

/**
 *  @brief Move constructor using a generic table
 *
 *  @param[in] table    the generic table to be moved
 */
DosimetryTable( Table&& table ): Table( std::move( table ) ) {

  this->verifyType();
  this->generateBlocks();
}

/**
 *  @brief Copy constructor using a dosimetry table
 *
 *  @param[in] table    the dosimetry table to be copied
 */
DosimetryTable( const DosimetryTable& dostable ) :
  Table( dostable ) {

  this->verifyType();
  this->generateBlocks();
}

/**
 *  @brief Move constructor using a dosimetry table
 *
 *  @param[in] table    the dosimetry table to be moved
 */
DosimetryTable( DosimetryTable&& dostable ) :
  Table( std::move( dostable ) ) {

  this->verifyType();
  this->generateBlocks();
}

/**
 *  @brief Copy assignment using a dosimetry table
 *
 *  @param[in] table    the dosimetry table to be copied
 */
DosimetryTable& operator=( const DosimetryTable& base ) {

  new (this) DosimetryTable( base );
  return *this;
}

/**
 *  @brief Move assignment using a dosimetry table
 *
 *  @param[in] table    the dosimetry table to be moved
 */
DosimetryTable& operator=( DosimetryTable&& base ) {

  new (this) DosimetryTable( std::move( base ) );
  return *this;
}

/**
 *  @brief Constructor
 *
 *  @param[in] z         the Z number of the nuclide
 *  @param[in] a         the A number of the nuclide
 *  @param[in] header    the header for the table
 *  @param[in] mtr       the reaction number block
 *  @param[in] sigd      the cross section data block
 */
DosimetryTable( unsigned int z, unsigned int a,
                HeaderVariant header, block::MTR mtr, dosimetry::SIGD sigd ) :
  DosimetryTable( Table( std::move( header ),
                         generateData( z, a, std::move( mtr ),
                                       std::move( sigd ) ) ) ) {}
