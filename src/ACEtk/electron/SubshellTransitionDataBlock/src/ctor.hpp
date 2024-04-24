SubshellTransitionDataBlock() = default;

SubshellTransitionDataBlock( const SubshellTransitionDataBlock& ) = default;
SubshellTransitionDataBlock( SubshellTransitionDataBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] transitions    the transition data
 */
SubshellTransitionDataBlock(
    std::vector< SubshellTransitionData > transitions ) :
  BlockWithLocators( "XPROB", std::move( transitions ), false ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] lsig    the begin iterator of the RELO block in the XSS array
 *  @param[in] sig     the begin iterator of the XPROB block in the XSS array
 *  @param[in] end     the end iterator of the XPROB block in the XSS array
 *  @param[in] nssh    the number of electron subshells
 */
SubshellTransitionDataBlock( Iterator relo, Iterator xprob,
                             Iterator end, unsigned int nssh ) :
  BlockWithLocators( "XPROB", relo, xprob, end, nssh, false ) {}

SubshellTransitionDataBlock& operator=( const SubshellTransitionDataBlock& ) = default;
SubshellTransitionDataBlock& operator=( SubshellTransitionDataBlock&& ) = default;
