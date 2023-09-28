EnergyDistributionBlock() = default;

EnergyDistributionBlock( const EnergyDistributionBlock& ) = default;
EnergyDistributionBlock( EnergyDistributionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] distributions    the energy distribution data
 */
EnergyDistributionBlock( std::vector< TabulatedEnergyDistribution > distributions ) :
  BaseElectronBlockWithLocators( "BREME", std::move( distributions ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator in the XSS array
 *  @param[in] end      the end iterator in the XSS array
 *  @param[in] nb       the number of energies with outgoing energy distributions
 */
EnergyDistributionBlock( Iterator begin, Iterator end, unsigned int nb ) :
  BaseElectronBlockWithLocators( "BREME", begin, end, nb ) {}

EnergyDistributionBlock& operator=( const EnergyDistributionBlock& ) = default;
EnergyDistributionBlock& operator=( EnergyDistributionBlock&& ) = default;
