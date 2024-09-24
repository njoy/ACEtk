ElasticAngularDistributionBlock() = default;

ElasticAngularDistributionBlock( const ElasticAngularDistributionBlock& ) = default;
ElasticAngularDistributionBlock( ElasticAngularDistributionBlock&& ) = default;

ElasticAngularDistributionBlock& operator=( const ElasticAngularDistributionBlock& ) = default;
ElasticAngularDistributionBlock& operator=( ElasticAngularDistributionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] distributions    the angular distribution data
 */
ElasticAngularDistributionBlock( std::vector< TabulatedAngularDistribution > distributions ) :
  ElectronBlockWithLocators( "ELAS", std::move( distributions ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator in the XSS array
 *  @param[in] end      the end iterator in the XSS array
 *  @param[in] na       the number of energies with angular distributions
 */
ElasticAngularDistributionBlock( Iterator begin, Iterator end, unsigned int na ) :
  ElectronBlockWithLocators( "ELAS", begin, end, na ) {}
