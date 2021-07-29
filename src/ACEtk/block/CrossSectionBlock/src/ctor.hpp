private:

/**
 *  @brief Private constructor
 */
CrossSectionBlock( std::vector< CrossSectionData >&& xs, std::size_t ntr ) :
  Base( "SIG", generateXSS( std::move( xs ) ) ),
  ntr_( ntr ) {

  this->sig_ = this->begin() + this->ntr_;    
}

public:

CrossSectionBlock() = default;

CrossSectionBlock( const CrossSectionBlock& ) = default;
CrossSectionBlock( CrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] xs    the cross section data
 */
CrossSectionBlock( std::vector< CrossSectionData >&& xs ) :
  CrossSectionBlock( std::move( xs ), xs.size() ) {}

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
