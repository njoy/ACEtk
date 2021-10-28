DosimetryCrossSectionBlock() = default;

DosimetryCrossSectionBlock( const DosimetryCrossSectionBlock& ) = default;
DosimetryCrossSectionBlock( DosimetryCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] xs    the cross section data
 */
DosimetryCrossSectionBlock( std::vector< DosimetryCrossSectionData >&& xs ) :
  BaseCrossSectionBlock( "SIGD", std::move( xs ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] lsig    the begin iterator of the LSIG block in the XSS array
 *  @param[in] sig     the begin iterator of the SIGD block in the XSS array
 *  @param[in] end     the end iterator of the SIGD block in the XSS array
 *  @param[in] ntr     the number of reactions (excluding elastic)
 */
DosimetryCrossSectionBlock( Iterator lsig, Iterator sig, Iterator end,
                   unsigned int ntr ) :
  BaseCrossSectionBlock( "SIGD", lsig, sig, end, ntr ) {}

DosimetryCrossSectionBlock& operator=( const DosimetryCrossSectionBlock& ) = default;
DosimetryCrossSectionBlock& operator=( DosimetryCrossSectionBlock&& ) = default;
