/**
 *  @brief Copy constructor using a generic table
 *
 *  @param[in] table    the generic table to be copied
 */
PhotonuclearTable( const Table& table ): Table( table ) {

  this->verifyType();
  this->setSZA();
  this->generateBlocks();
}

/**
 *  @brief Move constructor using a generic table
 *
 *  @param[in] table    the generic table to be moved
 */
PhotonuclearTable( Table&& table ): Table( std::move( table ) ) {

  this->verifyType();
  this->setSZA();
  this->generateBlocks();
}

/**
 *  @brief Copy constructor using a photonuclear table
 *
 *  @param[in] table    the photonuclear table to be copied
 */
PhotonuclearTable( const PhotonuclearTable& table ) :
  Table( table ) {

  this->verifyType();
  this->setSZA();
  this->generateBlocks();
}

/**
 *  @brief Move constructor using a photonuclear table
 *
 *  @param[in] table    the photonuclear table to be moved
 */
PhotonuclearTable( PhotonuclearTable&& table ) :
  Table( std::move( table ) ) {

  this->verifyType();
  this->setSZA();
  this->generateBlocks();
}

/**
 *  @brief Copy assignment using a photonuclear table
 *
 *  @param[in] table    the photonuclear table to be copied
 */
PhotonuclearTable& operator=( const PhotonuclearTable& base ) {

  if ( this != &base ) {

    Table::operator=( base );
    this->verifyType();
    this->generateBlocks();
  }
  return *this;
}

/**
 *  @brief Move assignment using a photonuclear table
 *
 *  @param[in] table    the photonuclear table to be moved
 */
PhotonuclearTable& operator=( PhotonuclearTable&& base ) {

  if ( this != &base ) {

    Table::operator=( std::move( base ) );
    this->verifyType();
    this->generateBlocks();
  }
  return *this;
}

/**
 *  @brief Constructor (from scratch)
 *
 *  @param[in] z         the Z number of the target
 *  @param[in] a         the A number of the target
 *  @param[in] s         the S number of the target
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
PhotonuclearTable( unsigned int z, unsigned int a, unsigned int s,
                   HeaderVariant header,
                   photonuclear::ESZU eszu, continuous::MTR mtr,
                   continuous::LQR lqr, continuous::SIG sig,
                   std::optional< std::vector< unsigned int > > ptype,
                   std::optional< std::vector< continuous::CrossSectionData > > pxs,
                   std::optional< std::vector< continuous::CrossSectionData > > phn,
                   std::optional< std::vector< continuous::MTRH > > mtrh,
                   std::optional< std::vector< continuous::SIGH > > sigh,
                   std::optional< std::vector< continuous::ANDH > > andh,
                   std::optional< std::vector< continuous::DLWH > > dlwh ) :
  PhotonuclearTable(
      Table( std::move( header ),
             generateData( z, a, s, std::move( eszu ),
                           std::move( mtr ), std::move( lqr ),
                           std::move( sig ),
                           std::move( ptype ),
                           std::move( pxs ), std::move( phn ),
                           std::move( mtrh ),
                           std::move( sigh ), std::move( andh ),
                           std::move( dlwh ) ) ) ) {}
