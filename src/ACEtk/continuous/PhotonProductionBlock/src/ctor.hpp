PhotonProductionBlock() = default;

PhotonProductionBlock( const PhotonProductionBlock& ) = default;
PhotonProductionBlock( PhotonProductionBlock&& ) = default;

PhotonProductionBlock& operator=( const PhotonProductionBlock& ) = default;
PhotonProductionBlock& operator=( PhotonProductionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] production    the total photon production cross section values
 */
PhotonProductionBlock( std::vector< double > production ) :
  ArrayData( "GPD",
             std::vector< std::vector< double > >{ std::move( production ) } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the GPD block in the XSS array
 *  @param[in] end     the end iterator of the GPD block in the XSS array
 *  @param[in] nes     the number of energy points
 */
PhotonProductionBlock( Iterator begin, Iterator end, unsigned int nes ) :
  ArrayData( "GPD", begin, end, nes, 1 ) {}
