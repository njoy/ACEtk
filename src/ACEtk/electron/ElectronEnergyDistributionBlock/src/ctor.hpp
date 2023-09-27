ElectronEnergyDistributionBlock() = default;

ElectronEnergyDistributionBlock( const ElectronEnergyDistributionBlock& ) = default;
ElectronEnergyDistributionBlock( ElectronEnergyDistributionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] distributions    the energy distribution data
 */
ElectronEnergyDistributionBlock( std::vector< ElectronTabulatedEnergyDistribution > distributions ) :
  BaseElectronBlockWithLocators( "BREME", std::move( distributions ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator in the XSS array
 *  @param[in] end      the end iterator in the XSS array
 *  @param[in] nb       the number of energies with outgoing energy distributions
 */
ElectronEnergyDistributionBlock( Iterator begin, Iterator end, unsigned int nb ) :
  BaseElectronBlockWithLocators( "BREME", begin, end, nb ) {}

ElectronEnergyDistributionBlock& operator=( const ElectronEnergyDistributionBlock& ) = default;
ElectronEnergyDistributionBlock& operator=( ElectronEnergyDistributionBlock&& ) = default;
