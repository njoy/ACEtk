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
  Base( "ThermalScatteringElasticAngularDistributionBlock",
        generateXSS( std::move( cosines ) ) ),
  ne_( cosines.size() ),
  nc_( cosines.front().size() ) {

  verifySize( this->XSS().size(), this->NE(), this->NC() );
}

/**
 *  @brief Constructor
 *
 *  @param[in] ne         the number of incident energies
 *  @param[in] nc         the number of discrete cosines per incident energy
 *  @param[in] begin      the begin iterator of the angular distribution data
 *  @param[in] end        the end iterator of the angular distribution data
 */
ThermalScatteringElasticAngularDistributionBlock(
    std::size_t ne, std::size_t nc,
    Iterator begin, Iterator end ) :
  Base( "ThermalScatteringElasticAngularDistributionBlock", begin, end ),
  ne_( ne ),
  nc_( nc ) {

  verifySize( std::distance( begin, end ), this->NE(), this->NC() );
}

ThermalScatteringElasticAngularDistributionBlock& operator=( const ThermalScatteringElasticAngularDistributionBlock& ) = default;
ThermalScatteringElasticAngularDistributionBlock& operator=( ThermalScatteringElasticAngularDistributionBlock&& ) = default;
