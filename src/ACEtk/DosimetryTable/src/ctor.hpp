DosimetryTable( const Table& table ): Table( table ) {

  this->generateBlocks();
}

DosimetryTable( Table&& table ): Table( std::move( table ) ) {

  this->generateBlocks();
}

DosimetryTable( const DosimetryTable& dostable ) :
  Table( dostable ) {

  this->generateBlocks();
}

DosimetryTable( DosimetryTable&& dostable ) :
  Table( std::move( dostable ) ) {

  this->generateBlocks();
}

DosimetryTable& operator=( const DosimetryTable& base ) {

  new (this) DosimetryTable( base );
  return *this;
}

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
                Header header, block::MTR mtr, block::SIGD sigd ) :
  DosimetryTable( Table( std::move( header ),
                         generateData( z, a, std::move( mtr ),
                                       std::move( sigd ) ) ) ) {}
