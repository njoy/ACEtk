ComptonProfileBlock() = default;

ComptonProfileBlock( const ComptonProfileBlock& ) = default;
ComptonProfileBlock( ComptonProfileBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] profiles    the compton profile data
 */
ComptonProfileBlock( std::vector< ComptonProfile > profiles ) :
  BlockWithLocators( "SWD", std::move( profiles ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] lswd    the begin iterator of the LSWD block in the XSS array
 *  @param[in] swd     the begin iterator of the SWD block in the XSS array
 *  @param[in] end     the end iterator of the SWD block in the XSS array
 *  @param[in] nsh     the number of shells
 */
ComptonProfileBlock( Iterator lsig, Iterator sig, Iterator end, unsigned int nsh ) :
  BlockWithLocators( "SWD", lsig, sig, end, nsh ) {}

ComptonProfileBlock& operator=( const ComptonProfileBlock& ) = default;
ComptonProfileBlock& operator=( ComptonProfileBlock&& ) = default;
