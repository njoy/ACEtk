private:

/**
 *  @brief Private constructor
 */
BaseCrossSectionBlock( std::string&& name, std::vector< Data >&& xs,
                       std::size_t ntr ) :
  Base( std::move( name ), generateXSS( std::move( xs ) ) ),
  ntr_( ntr ) {

  this->sig_ = this->begin() + this->ntr_;
}

public:

BaseCrossSectionBlock() = default;

BaseCrossSectionBlock( const BaseCrossSectionBlock& base ) :
  Base( base ), ntr_( base.ntr_ ) {

  this->sig_ = this->begin() + this->ntr_;
}

BaseCrossSectionBlock( BaseCrossSectionBlock&& base ) :
  Base( std::move( base ) ), ntr_( base.ntr_ ) {

  this->sig_ = this->begin() + this->ntr_;
}

/**
 *  @brief Constructor
 *
 *  @param[in] name    the block name
 *  @param[in] xs      the cross section data
 */
BaseCrossSectionBlock( std::string&& name, std::vector< Data >&& xs ) :
  BaseCrossSectionBlock( std::move( name ), std::move( xs ), xs.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] name    the block name
 *  @param[in] lsig    the begin iterator of the LSIG block in the XSS array
 *  @param[in] sig     the begin iterator of the SIG block in the XSS array
 *  @param[in] end     the end iterator of the SIG block in the XSS array
 *  @param[in] ntr     the number of reactions (excluding elastic)
 */
BaseCrossSectionBlock( std::string&& name,
                       Iterator lsig, Iterator sig, Iterator end,
                       unsigned int ntr ) :
  Base( std::move( name ), lsig, end ), ntr_( ntr ), sig_( sig ) {

  verifySize( this->begin(), this->sig_, this->end(), this->ntr_ );
}

BaseCrossSectionBlock& operator=( const BaseCrossSectionBlock& base ) {

  new (this) BaseCrossSectionBlock( base );
  return *this;
}

BaseCrossSectionBlock& operator=( BaseCrossSectionBlock&& base ) {

  new (this) BaseCrossSectionBlock( std::move( base ) );
  return *this;
}
