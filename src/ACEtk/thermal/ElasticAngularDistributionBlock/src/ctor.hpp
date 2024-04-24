ElasticAngularDistributionBlock() = default;

ElasticAngularDistributionBlock( const ElasticAngularDistributionBlock& ) = default;
ElasticAngularDistributionBlock( ElasticAngularDistributionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] cosines    the discrete cosine values for each incident energy
 */
ElasticAngularDistributionBlock( std::vector< std::vector< double > > cosines ) :
  ArrayData( "ElasticAngularDistributionBlock",
             std::move( cosines ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin      the begin iterator of the angular distribution data
 *  @param[in] end        the end iterator of the angular distribution data
 *  @param[in] ne         the number of incident energies
 *  @param[in] nc         the number of discrete cosines per incident energy
 */
ElasticAngularDistributionBlock(
    Iterator begin, Iterator end,
    std::size_t ne, std::size_t nc ) :
  ArrayData( "ElasticAngularDistributionBlock",
             begin, end, nc, ne ) {}

ElasticAngularDistributionBlock& operator=( const ElasticAngularDistributionBlock& ) = default;
ElasticAngularDistributionBlock& operator=( ElasticAngularDistributionBlock&& ) = default;
