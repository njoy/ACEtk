PhotonProductionCrossSectionBlock() = default;

PhotonProductionCrossSectionBlock( const PhotonProductionCrossSectionBlock& ) = default;
PhotonProductionCrossSectionBlock( PhotonProductionCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] xs    the cross section data
 */
PhotonProductionCrossSectionBlock( std::vector< PhotonProductionData > xs ) :
  BaseCrossSectionBlock( "SIGP", std::move( xs ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] lsigp    the begin iterator of the LSIGP block in the XSS array
 *  @param[in] sigp     the begin iterator of the SIGP block in the XSS array
 *  @param[in] end      the end iterator of the SIGP block in the XSS array
 *  @param[in] ntr      the number of reactions (excluding elastic)
 */
PhotonProductionCrossSectionBlock( Iterator lsigp, Iterator sigp, Iterator end,
                                   unsigned int ntr ) :
  BaseCrossSectionBlock( "SIGP", lsigp, sigp, end, ntr ) {}

PhotonProductionCrossSectionBlock& operator=( const PhotonProductionCrossSectionBlock& ) = default;
PhotonProductionCrossSectionBlock& operator=( PhotonProductionCrossSectionBlock&& ) = default;
