PhotoAtomicComptonProfileBlock() = default;

PhotoAtomicComptonProfileBlock( const PhotoAtomicComptonProfileBlock& ) = default;
PhotoAtomicComptonProfileBlock( PhotoAtomicComptonProfileBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] profiles    the compton profile data
 */
PhotoAtomicComptonProfileBlock( std::vector< PhotoAtomicComptonProfile > profiles ) :
  BaseBlockWithLocators( "SWD", std::move( profiles ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] lswd    the begin iterator of the LSWD block in the XSS array
 *  @param[in] swd     the begin iterator of the SWD block in the XSS array
 *  @param[in] end     the end iterator of the SWD block in the XSS array
 *  @param[in] nsh     the number of shells
 */
PhotoAtomicComptonProfileBlock( Iterator lsig, Iterator sig, Iterator end,
                                unsigned int nsh ) :
  BaseBlockWithLocators( "SWD", lsig, sig, end, nsh ) {}

PhotoAtomicComptonProfileBlock& operator=( const PhotoAtomicComptonProfileBlock& ) = default;
PhotoAtomicComptonProfileBlock& operator=( PhotoAtomicComptonProfileBlock&& ) = default;
