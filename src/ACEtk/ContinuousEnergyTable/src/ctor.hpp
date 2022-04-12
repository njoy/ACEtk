/**
 *  @brief Copy constructor using a generic table
 *
 *  @param[in] table    the generic table to be copied
 */
ContinuousEnergyTable( const Table& table ): Table( table ) {

  this->generateBlocks();
}

/**
 *  @brief Move constructor using a generic table
 *
 *  @param[in] table    the generic table to be moved
 */
ContinuousEnergyTable( Table&& table ): Table( std::move( table ) ) {

  this->generateBlocks();
}

/**
 *  @brief Copy constructor using a continuous energy table
 *
 *  @param[in] table    the continuous energy table to be copied
 */
ContinuousEnergyTable( const ContinuousEnergyTable& table ) :
  Table( table ) {

  this->generateBlocks();
}

/**
 *  @brief Move constructor using a continuous energy table
 *
 *  @param[in] table    the continuous energy table to be moved
 */
ContinuousEnergyTable( ContinuousEnergyTable&& table ) :
  Table( std::move( table ) ) {

  this->generateBlocks();
}

/**
 *  @brief Copy assignment using a continuous energy table
 *
 *  @param[in] table    the continuous energy table to be copied
 */
ContinuousEnergyTable& operator=( const ContinuousEnergyTable& base ) {

  new (this) ContinuousEnergyTable( base );
  return *this;
}

/**
 *  @brief Move assignment using a continuous energy table
 *
 *  @param[in] table    the continuous energy table to be moved
 */
ContinuousEnergyTable& operator=( ContinuousEnergyTable&& base ) {

  new (this) ContinuousEnergyTable( std::move( base ) );
  return *this;
}

/**
 *  @brief Constructor (from scratch)
 *
 *  @param[in] z         the Z number of the nuclide
 *  @param[in] a         the A number of the nuclide
 *  @param[in] header    the header for the table
 *  @param[in] esz       the principal cross section block
 *  @param[in] nu        the optional fission neutron multiplicity block
 *  @param[in] dnu       the optional delayed fission neutron multiplicity block
 *  @param[in] mtr       the reaction number block
 *  @param[in] lqr       the reaction Q value block
 *  @param[in] sig       the cross section data block
 *  @param[in] ang       the angular distribution data block
 *  @param[in] dlw       the energy distribution data block
 *  @param[in] bdd       the delayed fission neutron precursor data block
 *  @param[in] dned      the delayed fission neutron energy distribution data block
 *  @param[in] gpd       the photon production block
 *  @param[in] mtrp      the photon production reaction number block
 *  @param[in] sigp      the photon production cross section data block
 *  @param[in] angp      the photon production angular distribution data block
 *  @param[in] dlwp      the photon production energy distribution data block
 *  @param[in] yp        the photon multiplicity reaction number block
 *  @param[in] unr       the unresolved resonance probability table block
 *  @param[in] ptype     the secondary particle type block
 *  @param[in] hpd       the secondary particle production blocks
 *  @param[in] mtrh      the secondary particle production reaction number blocks
 *  @param[in] tyrh      the secondary particle productionreference frame blocks
 *  @param[in] sigh      the secondary particle production cross section data blocks
 *  @param[in] angh      the secondary particle angular distribution data blocks
 *  @param[in] dlwh      the secondary particle energy distribution data blocks
 *  @param[in] yh        the secondary particle multiplicity reaction number blocks
 */
ContinuousEnergyTable( unsigned int z, unsigned int a, Header header,
                       block::ESZ esz, std::optional< block::NU > nu,
                       std::optional< block::DNU > dnu,
                       block::MTR mtr, block::LQR lqr,
                       block::SIG sig, block::AND ang, block::DLW dlw,
                       std::optional< block::BDD > bdd,
                       std::optional< block::DNED > dned,
                       std::optional< block::GPD > gpd,
                       std::optional< block::MTRP > mtrp,
                       std::optional< block::SIGP > sigp,
                       std::optional< block::ANDP > andp,
                       std::optional< block::DLWP > dlwp,
                       std::optional< block::YP > yp,
                       std::optional< block::UNR > unr,
                       std::optional< block::PTYPE > ptype,
                       std::optional< std::vector< block::HPD > > hpd,
                       std::optional< std::vector< block::MTRH > > mtrh,
                       std::optional< std::vector< block::TYRH > > tyrh,
                       std::optional< std::vector< block::SIGH > > sigh,
                       std::optional< std::vector< block::ANDH > > andh,
                       std::optional< std::vector< block::DLWH > > dlwh,
                       std::optional< std::vector< block::YH > > yh ) :
  ContinuousEnergyTable(
      Table( std::move( header ),
             generateData( z, a, std::move( esz ), std::move( nu ),
                           std::move( mtr ), std::move( lqr ),
                           std::move( sig ),
                           std::move( ang ), std::move( dlw ),
                           std::move( gpd ), std::move( mtrp ),
                           std::move( sigp ), std::move( andp ),
                           std::move( dlwp ), std::move( yp ),
                           std::move( unr ), std::move( dnu ),
                           std::move( bdd ), std::move( dned ),
                           std::move( ptype ), std::move( hpd ),
                           std::move( mtrh ), std::move( tyrh ),
                           std::move( sigh ), std::move( andh ),
                           std::move( dlwh ), std::move( yh ) ) ) ) {}
