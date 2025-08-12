ElasticCrossSectionBlock() = default;

ElasticCrossSectionBlock( const ElasticCrossSectionBlock& ) = default;
ElasticCrossSectionBlock( ElasticCrossSectionBlock&& ) = default;

ElasticCrossSectionBlock& operator=( const ElasticCrossSectionBlock& ) = default;
ElasticCrossSectionBlock& operator=( ElasticCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] transport    the transport elastic cross section values
 *  @param[in] total        the total elastic cross section values
 */
ElasticCrossSectionBlock(
    std::vector< double > transport,
    std::vector< double > total ) :
  ArrayData( "SELAS", std::move( transport ), std::move( total ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the ESZE block in the XSS array
 *  @param[in] end     the end iterator of the ESZE block in the XSS array
 *  @param[in] nssh    the number of electron shells
 *  @param[in] ne      the number of energy values
 */
ElasticCrossSectionBlock( Iterator begin, Iterator end,
                                      unsigned int ne ) :
  ArrayData( "SELAS", begin, end, ne, 2 ) {}
