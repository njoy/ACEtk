/**
 *  @brief Copy constructor using a generic table
 *
 *  @param[in] table    the generic table to be copied
 */
ElectronTable( const Table& table ): Table( table ) {

  this->verifyType();
  this->generateBlocks();
}

/**
 *  @brief Move constructor using a generic table
 *
 *  @param[in] table    the generic table to be moved
 */
ElectronTable( Table&& table ): Table( std::move( table ) ) {

  this->verifyType();
  this->generateBlocks();
}

/**
 *  @brief Copy constructor using a photoatomic table
 *
 *  @param[in] table    the photoatomic table to be copied
 */
ElectronTable( const ElectronTable& table ) :
  Table( table ) {

  this->verifyType();
  this->generateBlocks();
}

/**
 *  @brief Move constructor using a photoatomic table
 *
 *  @param[in] table    the photoatomic table to be moved
 */
ElectronTable( ElectronTable&& table ) :
  Table( std::move( table ) ) {

  this->verifyType();
  this->generateBlocks();
}

/**
 *  @brief Copy assignment using a photoatomic table
 *
 *  @param[in] table    the photoatomic table to be copied
 */
ElectronTable& operator=( const ElectronTable& base ) {

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
ElectronTable& operator=( ElectronTable&& base ) {

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
 *  @param[in] ekt       the transition energy block
 *  @param[in] rad       the radiation stopping power block
 *  @param[in] mot       the Mott scattering correction block
 *  @param[in] rly       the Riley cross section block
 *  @param[in] xsb       the brmsstrahlung production block (NEL == 3)
 *  @param[in] crb       the bremsstrahlung correction factor block (NEL != 3)
 *  @param[in] hfb       the bremsstrahlung high-frequency block (NEL != 3)
 *  @param[in] rkt       the bremsstrahlung energy spectrum block (NEL == 3)
 *  @param[in] rka       the bremsstrahlung angular spectrum block (NEL == 3)
 *  @param[in] osc       the oscillator block (NEL == 3)
 */
ElectronTable( unsigned int z, HeaderVariant header,
               std::vector< unsigned int > za, std::vector< double > awr,
               electron::EKT ekt, electron::RAD rad,
               electron::MOT mot, electron::RLY rly,
               std::optional< electron::XSB > xsb,
               std::optional< electron::CRB > crb,
               std::optional< electron::HFB > hfb,
               std::optional< electron::RKT > rkt,
               std::optional< electron::RKA > rka,
               std::optional< electron::OSC > osc ) :
  ElectronTable(
    Table( std::move( header ),
           generateData( z, std::move( za ), std::move( awr ),
                         std::move( ekt ), std::move( rad ),
                         std::move( mot ), std::move( rly ),
                         std::move( xsb ), std::move( crb ),
                         std::move( hfb ), std::move( rkt ),
                         std::move( rka ), std::move( osc ) ) ) ) {}
