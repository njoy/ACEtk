ElectronBremsstrahlungEnergyDistributionBlock() = default;

ElectronBremsstrahlungEnergyDistributionBlock( const ElectronBremsstrahlungEnergyDistributionBlock& ) = default;
ElectronBremsstrahlungEnergyDistributionBlock( ElectronBremsstrahlungEnergyDistributionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] distributions    the energy distribution data
 */
ElectronBremsstrahlungEnergyDistributionBlock( std::vector< ElectronTabulatedEnergyDistribution > distributions ) :
  BaseElectronBlockWithLocators( "BREME", std::move( distributions ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator in the XSS array
 *  @param[in] end      the end iterator in the XSS array
 *  @param[in] nb       the number of energies with outgoing energy distributions
 */
ElectronBremsstrahlungEnergyDistributionBlock( Iterator begin, Iterator end,
                                         unsigned int nb ) :
  BaseElectronBlockWithLocators( "BREME", begin, end, nb ) {}

ElectronBremsstrahlungEnergyDistributionBlock& operator=( const ElectronBremsstrahlungEnergyDistributionBlock& ) = default;
ElectronBremsstrahlungEnergyDistributionBlock& operator=( ElectronBremsstrahlungEnergyDistributionBlock&& ) = default;
