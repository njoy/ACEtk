PhotoatomicSubshellTransitionDataBlock() = default;

PhotoatomicSubshellTransitionDataBlock( const PhotoatomicSubshellTransitionDataBlock& ) = default;
PhotoatomicSubshellTransitionDataBlock( PhotoatomicSubshellTransitionDataBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] xs    the cross section data
 */
PhotoatomicSubshellTransitionDataBlock( std::vector< PhotoatomicSubshellTransitionData > xs ) :
  BaseBlockWithLocators( "XPROB", std::move( xs ), false ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] lsig    the begin iterator of the RELO block in the XSS array
 *  @param[in] sig     the begin iterator of the XPROB block in the XSS array
 *  @param[in] end     the end iterator of the XPROB block in the XSS array
 *  @param[in] nssh    the number of electron subshells
 */
PhotoatomicSubshellTransitionDataBlock( Iterator relo, Iterator xprob,
                                        Iterator end, unsigned int nssh ) :
  BaseBlockWithLocators( "XPROB", relo, xprob, end, nssh, false ) {}

PhotoatomicSubshellTransitionDataBlock& operator=( const PhotoatomicSubshellTransitionDataBlock& ) = default;
PhotoatomicSubshellTransitionDataBlock& operator=( PhotoatomicSubshellTransitionDataBlock&& ) = default;
