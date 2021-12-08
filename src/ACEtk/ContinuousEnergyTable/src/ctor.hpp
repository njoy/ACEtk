ContinuousEnergyTable( const Table& table ): Table( table ) {

  this->generateBlocks();
}

ContinuousEnergyTable( Table&& table ): Table( std::move( table ) ) {

  this->generateBlocks();
}

ContinuousEnergyTable( const ContinuousEnergyTable& cetable ) :
  Table( cetable ) {

  this->generateBlocks();
}

ContinuousEnergyTable( ContinuousEnergyTable&& cetable ) :
  Table( std::move( cetable ) ) {

  this->generateBlocks();
}

ContinuousEnergyTable& operator=( const ContinuousEnergyTable& base ) {

  new (this) ContinuousEnergyTable( base );
  return *this;
}

ContinuousEnergyTable& operator=( ContinuousEnergyTable&& base ) {

  new (this) ContinuousEnergyTable( std::move( base ) );
  return *this;
}

/**
 *  @brief Constructor
 *
 *  @param[in] z         the Z number of the nuclide
 *  @param[in] a         the A number of the nuclide
 *  @param[in] header    the header for the table
 *  @param[in] esz       the principal cross section block
 *  @param[in] nu        the optional fission multiplicity block
 *  @param[in] mtr       the reaction number block
 *  @param[in] lqr       the reaction Q value block
 *  @param[in] tyr       the reference frame and multiplicity block
 *  @param[in] sig       the cross section data block
 *  @param[in] ang       the angular distribution data block
 *  @param[in] dlw       the energy distribution data block
 */
ContinuousEnergyTable( unsigned int z, unsigned int a, Header header,
                       block::ESZ esz, std::optional< block::NU > nu,
                       block::MTR mtr, block::LQR lqr, block::TYR tyr,
                       block::SIG sig, block::AND ang, block::DLW dlw ) :
  ContinuousEnergyTable( Table( std::move( header ),
                         generateData( z, a, std::move( esz ), std::move( nu ),
                                       std::move( mtr ), std::move( lqr ),
                                       std::move( tyr ), std::move( sig ),
                                       std::move( ang ), std::move( dlw ) ) ) ) {}
