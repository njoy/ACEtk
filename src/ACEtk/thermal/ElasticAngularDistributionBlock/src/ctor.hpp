ThermalScatteringElasticAngularDistributionBlock() = default;

ThermalScatteringElasticAngularDistributionBlock( const ThermalScatteringElasticAngularDistributionBlock& ) = default;
ThermalScatteringElasticAngularDistributionBlock( ThermalScatteringElasticAngularDistributionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] cosines    the discrete cosine values for each incident energy
 */
ThermalScatteringElasticAngularDistributionBlock(
    std::vector< std::vector< double > > cosines ) :
  ArrayData( "ThermalScatteringElasticAngularDistributionBlock",
             std::move( cosines ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin      the begin iterator of the angular distribution data
 *  @param[in] end        the end iterator of the angular distribution data
 *  @param[in] ne         the number of incident energies
 *  @param[in] nc         the number of discrete cosines per incident energy
 */
ThermalScatteringElasticAngularDistributionBlock(
    Iterator begin, Iterator end,
    std::size_t ne, std::size_t nc ) :
  ArrayData( "ThermalScatteringElasticAngularDistributionBlock",
             begin, end, nc, ne ) {}

ThermalScatteringElasticAngularDistributionBlock& operator=( const ThermalScatteringElasticAngularDistributionBlock& ) = default;
ThermalScatteringElasticAngularDistributionBlock& operator=( ThermalScatteringElasticAngularDistributionBlock&& ) = default;
