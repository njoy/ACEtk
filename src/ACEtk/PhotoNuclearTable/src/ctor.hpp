/**
 *  @brief Copy constructor using a generic table
 *
 *  @param[in] table    the generic table to be copied
 */
PhotoNuclearTable( const Table& table ): Table( table ) {

  this->generateBlocks();
}

/**
 *  @brief Move constructor using a generic table
 *
 *  @param[in] table    the generic table to be moved
 */
PhotoNuclearTable( Table&& table ): Table( std::move( table ) ) {

  this->generateBlocks();
}

/**
 *  @brief Copy constructor using a continuous energy table
 *
 *  @param[in] table    the continuous energy table to be copied
 */
PhotoNuclearTable( const PhotoNuclearTable& table ) :
  Table( table ) {

  this->generateBlocks();
}

/**
 *  @brief Move constructor using a continuous energy table
 *
 *  @param[in] table    the continuous energy table to be moved
 */
PhotoNuclearTable( PhotoNuclearTable&& table ) :
  Table( std::move( table ) ) {

  this->generateBlocks();
}

/**
 *  @brief Copy assignment using a continuous energy table
 *
 *  @param[in] table    the continuous energy table to be copied
 */
PhotoNuclearTable& operator=( const PhotoNuclearTable& base ) {

  new (this) PhotoNuclearTable( base );
  return *this;
}

/**
 *  @brief Move assignment using a continuous energy table
 *
 *  @param[in] table    the continuous energy table to be moved
 */
PhotoNuclearTable& operator=( PhotoNuclearTable&& base ) {

  new (this) PhotoNuclearTable( std::move( base ) );
  return *this;
}

/**
 *  @brief Constructor (from scratch)
 *
 *  @param[in] z         the Z number of the nuclide
 *  @param[in] a         the A number of the nuclide
 *  @param[in] header    the header for the table
 *  @param[in] eszu      the principal cross section block
 *  @param[in] mtr       the reaction number block
 *  @param[in] lqr       the reaction Q value block
 *  @param[in] sig       the cross section data block
 *  @param[in] ptype     the secondary particle types
 *  @param[in] pxs       the secondary particle production cross section data
 *  @param[in] phn       the secondary particle heating cross section data
 *  @param[in] mtrh      the secondary particle production reaction number blocks
 *  @param[in] sigh      the secondary particle production cross section data blocks
 *  @param[in] andh      the secondary particle angular distribution data blocks
 *  @param[in] dlwh      the secondary particle energy distribution data blocks
 */
PhotoNuclearTable( unsigned int z, unsigned int a, Header header,
                   block::ESZU eszu, block::MTR mtr, block::LQR lqr,
                   block::SIG sig,
                   std::optional< std::vector< unsigned int > > ptype,
                   std::optional< std::vector< block::CrossSectionData > > pxs,
                   std::optional< std::vector< block::CrossSectionData > > phn,
                   std::optional< std::vector< block::MTRH > > mtrh,
                   std::optional< std::vector< block::SIGH > > sigh,
                   std::optional< std::vector< block::ANDH > > andh,
                   std::optional< std::vector< block::DLWH > > dlwh ) :
  PhotoNuclearTable(
      Table( std::move( header ),
             generateData( z, a, std::move( eszu ),
                           std::move( mtr ), std::move( lqr ),
                           std::move( sig ),
                           std::move( ptype ),
                           std::move( pxs ), std::move( phn ),
                           std::move( mtrh ),
                           std::move( sigh ), std::move( andh ),
                           std::move( dlwh ) ) ) ) {}
