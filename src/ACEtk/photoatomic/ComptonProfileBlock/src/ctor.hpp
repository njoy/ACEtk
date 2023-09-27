PhotoatomicComptonProfileBlock() = default;

PhotoatomicComptonProfileBlock( const PhotoatomicComptonProfileBlock& ) = default;
PhotoatomicComptonProfileBlock( PhotoatomicComptonProfileBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] profiles    the compton profile data
 */
PhotoatomicComptonProfileBlock( std::vector< PhotoatomicComptonProfile > profiles ) :
  BaseBlockWithLocators( "SWD", std::move( profiles ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] lswd    the begin iterator of the LSWD block in the XSS array
 *  @param[in] swd     the begin iterator of the SWD block in the XSS array
 *  @param[in] end     the end iterator of the SWD block in the XSS array
 *  @param[in] nsh     the number of shells
 */
PhotoatomicComptonProfileBlock( Iterator lsig, Iterator sig, Iterator end,
                                unsigned int nsh ) :
  BaseBlockWithLocators( "SWD", lsig, sig, end, nsh ) {}

PhotoatomicComptonProfileBlock& operator=( const PhotoatomicComptonProfileBlock& ) = default;
PhotoatomicComptonProfileBlock& operator=( PhotoatomicComptonProfileBlock&& ) = default;
