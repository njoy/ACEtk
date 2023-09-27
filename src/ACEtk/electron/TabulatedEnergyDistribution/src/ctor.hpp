ElectronTabulatedEnergyDistribution() = default;

ElectronTabulatedEnergyDistribution( const ElectronTabulatedEnergyDistribution& ) = default;
ElectronTabulatedEnergyDistribution( ElectronTabulatedEnergyDistribution&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energy      the associated energy value
 *  @param[in] outgoing    the outgoing energy values (LB values)
 *  @param[in] cdf         the cdf values (LB values)
 */
ElectronTabulatedEnergyDistribution( double energy,
                                     std::vector< double > outgoing,
                                     std::vector< double > cdf ) :
  ArrayData( "ElectronTabulatedEnergyDistribution",
             std::move( outgoing ), std::move( cdf ) ),
  energy_( energy ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] energy    the associated energy value
 *  @param[in] begin     the begin iterator of the tabulated distribution data
 *  @param[in] end       the end iterator of the tabulated distribution data
 *  @param[in] lb        the number of outgoing energy values
 */
ElectronTabulatedEnergyDistribution( double energy,
                                      Iterator begin, Iterator end,
                                      unsigned int la ) :
  ArrayData( "ElectronTabulatedEnergyDistribution", begin, end, la, 2 ),
  energy_( energy ) {}

ElectronTabulatedEnergyDistribution& operator=( const ElectronTabulatedEnergyDistribution& ) = default;
ElectronTabulatedEnergyDistribution& operator=( ElectronTabulatedEnergyDistribution&& ) = default;
