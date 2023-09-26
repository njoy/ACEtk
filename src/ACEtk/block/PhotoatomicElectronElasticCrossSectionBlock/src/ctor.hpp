PhotoatomicElectronElasticCrossSectionBlock() = default;

PhotoatomicElectronElasticCrossSectionBlock( const PhotoatomicElectronElasticCrossSectionBlock& ) = default;
PhotoatomicElectronElasticCrossSectionBlock( PhotoatomicElectronElasticCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] transport    the transport elastic cross section values
 *  @param[in] total        the total elastic cross section values
 */
PhotoatomicElectronElasticCrossSectionBlock(
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
PhotoatomicElectronElasticCrossSectionBlock( Iterator begin, Iterator end,
                                      unsigned int ne ) :
  ArrayData( "SELAS", begin, end, ne, 2 ) {}

PhotoatomicElectronElasticCrossSectionBlock& operator=( const PhotoatomicElectronElasticCrossSectionBlock& ) = default;
PhotoatomicElectronElasticCrossSectionBlock& operator=( PhotoatomicElectronElasticCrossSectionBlock&& ) = default;
