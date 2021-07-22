CrossSectionBlock() = default;

CrossSectionBlock( const CrossSectionBlock& ) = default;
CrossSectionBlock( CrossSectionBlock&& ) = default;

// /**
//  *  @brief Constructor
//  *
//  *  @param[in] mts    the MT numbers
//  */
// CrossSectionBlock( std::vector< unsigned int >&& reactions ) :
//   Base( "MTR", generateXSS( std::move( reactions ) ) ),
//   ntr_( reactions.size() ) {}

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
  Base( "SIG", lsig, end ), ntr_( ntr ), sig_( sig ) {

  verifySize( this->begin(), this->sig_, this->end(), this->ntr_ );
}

CrossSectionBlock& operator=( const CrossSectionBlock& ) = default;
CrossSectionBlock& operator=( CrossSectionBlock&& ) = default;