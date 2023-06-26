PhotonProductionCrossSectionData() = default;

PhotonProductionCrossSectionData( const PhotonProductionCrossSectionData& ) = default;
PhotonProductionCrossSectionData( PhotonProductionCrossSectionData&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] index     the energy index
 *  @param[in] values    the cross section values
 */
PhotonProductionCrossSectionData( std::size_t index,
                                  std::vector< double > values ) :
  Base( "PhotonProductionCrossSectionData",
        generateXSS( index, std::move( values ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin    the begin iterator of the cross section data
 *  @param[in] end      the end iterator of the cross section data
 */
PhotonProductionCrossSectionData( Iterator begin, Iterator end ) :
  Base( "PhotonProductionCrossSectionData", begin, end ) {

  verifySize( this->begin(), this->end(), this->numberValues() );
}

PhotonProductionCrossSectionData& operator=( const PhotonProductionCrossSectionData& ) = default;
PhotonProductionCrossSectionData& operator=( PhotonProductionCrossSectionData&& ) = default;
