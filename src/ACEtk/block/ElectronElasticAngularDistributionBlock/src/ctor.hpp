ElectronElasticAngularDistributionBlock() = default;

ElectronElasticAngularDistributionBlock( const ElectronElasticAngularDistributionBlock& ) = default;
ElectronElasticAngularDistributionBlock( ElectronElasticAngularDistributionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] xs    the cross section data
 */
ElectronElasticAngularDistributionBlock( std::vector< ElectronTabulatedAngularDistribution > distributions ) :
  BaseElectronBlockWithLocators( "ELAS", std::move( distributions ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator in the XSS array
 *  @param[in] end      the end iterator in the XSS array
 *  @param[in] na       the number of energies with angular distributions
 */
ElectronElasticAngularDistributionBlock( Iterator begin, Iterator end,
                                         unsigned int na ) :
  BaseElectronBlockWithLocators( "ELAS", begin, end, na ) {}

ElectronElasticAngularDistributionBlock& operator=( const ElectronElasticAngularDistributionBlock& ) = default;
ElectronElasticAngularDistributionBlock& operator=( ElectronElasticAngularDistributionBlock&& ) = default;
