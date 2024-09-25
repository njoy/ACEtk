/**
 *  @brief Copy constructor using a generic table
 *
 *  @param[in] table    the generic table to be copied
 */
PhotoatomicTable( const Table& table ): Table( table ) {

  this->verifyType();
  this->generateBlocks();
}

/**
 *  @brief Move constructor using a generic table
 *
 *  @param[in] table    the generic table to be moved
 */
PhotoatomicTable( Table&& table ): Table( std::move( table ) ) {

  this->verifyType();
  this->generateBlocks();
}

/**
 *  @brief Copy constructor using a photoatomic table
 *
 *  @param[in] table    the photoatomic table to be copied
 */
PhotoatomicTable( const PhotoatomicTable& table ) :
  Table( table ) {

  this->verifyType();
  this->generateBlocks();
}

/**
 *  @brief Move constructor using a photoatomic table
 *
 *  @param[in] table    the photoatomic table to be moved
 */
PhotoatomicTable( PhotoatomicTable&& table ) :
  Table( std::move( table ) ) {

  this->verifyType();
  this->generateBlocks();
}

/**
 *  @brief Copy assignment using a photoatomic table
 *
 *  @param[in] table    the photoatomic table to be copied
 */
PhotoatomicTable& operator=( const PhotoatomicTable& base ) {

  if ( this != &base ) {

    Table::operator=( base );
    this->verifyType();
    this->generateBlocks();
  }
  return *this;
}

/**
 *  @brief Move assignment using a photoatomic table
 *
 *  @param[in] table    the photoatomic table to be moved
 */
PhotoatomicTable& operator=( PhotoatomicTable&& base ) {

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
 *  @param[in] header    the header for the table
 *  @param[in] za        the list of ZA values
 *  @param[in] awr       the list of atomic mass values
 *  @param[in] eszg      the principal cross section block
 *  @param[in] jinc      the incoherent scattering function block
 *  @param[in] jcoh      the coherent form factor block
 *  @param[in] lhnm      the heating numbers block
 *  @param[in] jflo      the fluorescence data block
 *  @param[in] eps       the electron shell data block
 *  @param[in] swd       the compton profile block
 *  @param[in] subsh     the electron subshell data block
 *  @param[in] sphel     the photoelectric cross section block
 *  @param[in] xprob     the atomic relaxation data block
 *  @param[in] esze      the electron cross section block
 *  @param[in] excit     the excitation energy loss data block
 *  @param[in] elas      the electron elastic angular distribution block
 *  @param[in] eion      the electronionisation data block
 *  @param[in] breme     the photon energy distributions from Bremsstrahlung
 *  @param[in] breml     the electron average energy after Bremsstrahlung
 *  @param[in] selas     the additional electron elastic cross section block
 */
PhotoatomicTable( unsigned int z, HeaderVariant header,
                  std::vector< unsigned int > za, std::vector< double > awr,
                  photoatomic::ESZG eszg, photoatomic::JINC jinc,
                  photoatomic::JCOH jcoh, photoatomic::LHNM lhnm,
                  std::optional< photoatomic::JFLO > jflo,
                  std::optional< electron::EPS > eps,
                  std::optional< photoatomic::SWD > swd,
                  std::optional< electron::SUBSH > subsh,
                  std::optional< photoatomic::SPHEL > sphel,
                  std::optional< electron::XPROB > xprob,
                  std::optional< electron::ESZE > esze,
                  std::optional< electron::EXCIT > excit,
                  std::optional< electron::ELAS > elas,
                  std::vector< electron::EION > eion,
                  std::optional< electron::BREME > breme,
                  std::optional< electron::BREML > breml,
                  std::optional< electron::SELAS > selas ) :
  PhotoatomicTable(
      Table( std::move( header ),
             generateData( z, std::move( za ), std::move( awr ),
                           std::move( eszg ), std::move( jinc ),
                           std::move( jcoh ), std::move( lhnm ),
                           std::move( jflo ), std::move( eps ),
                           std::move( swd ), std::move( subsh ),
                           std::move( sphel ), std::move( xprob ),
                           std::move( esze ), std::move( excit ),
                           std::move( elas ), std::move( eion ),
                           std::move( breme ), std::move( breml ),
                           std::move( selas ) ) ) ) {}
