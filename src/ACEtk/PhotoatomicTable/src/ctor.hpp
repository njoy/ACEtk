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

  new (this) PhotoatomicTable( base );
  return *this;
}

/**
 *  @brief Move assignment using a photoatomic table
 *
 *  @param[in] table    the photoatomic table to be moved
 */
PhotoatomicTable& operator=( PhotoatomicTable&& base ) {

  new (this) PhotoatomicTable( std::move( base ) );
  return *this;
}

/**
 *  @brief Constructor (from scratch)
 *
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
 */
PhotoatomicTable( unsigned int z, HeaderVariant header,
                  std::vector< unsigned int > za, std::vector< double > awr,
                  block::ESZG eszg, block::JINC jinc,
                  block::JCOH jcoh, block::LHNM lhnm,
                  std::optional< block::JFLO > jflo,
                  std::optional< block::EPS > eps,
                  std::optional< block::SWD > swd ) :
  PhotoatomicTable(
      Table( std::move( header ),
             generateData( z, std::move( za ), std::move( awr ),
                           std::move( eszg ), std::move( jinc ),
                           std::move( jcoh ), std::move( lhnm ),
                           std::move( jflo ), std::move( eps ),
                           std::move( swd ) ) ) ) {}
