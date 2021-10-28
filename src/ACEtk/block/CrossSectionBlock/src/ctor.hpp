CrossSectionBlock() = default;

CrossSectionBlock( const CrossSectionBlock& ) = default;
CrossSectionBlock( CrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] xs    the cross section data
 */
CrossSectionBlock( std::vector< CrossSectionData >&& xs ) :
  BaseCrossSectionBlock( "SIG", std::move( xs ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] lsig    the begin iterator of the LSIG block in the XSS array
 *  @param[in] sig     the begin iterator of the SIG block in the XSS array
 *  @param[in] end     the end iterator of the SIG block in the XSS array
 *  @param[in] ntr     the number of reactions (excluding elastic)
 */
CrossSectionBlock( Iterator lsig, Iterator sig, Iterator end,
                   unsigned int ntr ) :
  BaseCrossSectionBlock( "SIG", lsig, sig, end, ntr ) {}

CrossSectionBlock& operator=( const CrossSectionBlock& ) = default;
CrossSectionBlock& operator=( CrossSectionBlock&& ) = default;
