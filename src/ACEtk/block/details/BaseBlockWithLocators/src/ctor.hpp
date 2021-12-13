private:

/**
 *  @brief Private constructor
 */
BaseBlockWithLocators( std::string&& name, std::vector< Data >&& xs,
                       std::size_t ntr ) :
  Base( std::move( name ), Derived::generateXSS( std::move( xs ) ) ),
  ntr_( ntr ) {

  this->iterator_ = this->begin() + this->ntr_;
  this->generateBlocks();
}

public:

BaseBlockWithLocators() = default;

BaseBlockWithLocators( const BaseBlockWithLocators& base ) :
  Base( base ), ntr_( base.ntr_ ) {

  this->iterator_ = this->begin() + this->ntr_;
  this->generateBlocks();
}

BaseBlockWithLocators( BaseBlockWithLocators&& base ) :
  Base( std::move( base ) ), ntr_( base.ntr_ ) {

  this->iterator_ = this->begin() + this->ntr_;
  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] name    the block name
 *  @param[in] xs      the cross section data
 */
BaseBlockWithLocators( std::string name, std::vector< Data > xs ) :
  BaseBlockWithLocators( std::move( name ), std::move( xs ), xs.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] name    the block name
 *  @param[in] loc     the begin iterator of the LSIG block in the XSS array
 *  @param[in] data    the begin iterator of the SIG block in the XSS array
 *  @param[in] end     the end iterator of the SIG block in the XSS array
 *  @param[in] ntr     the number of reactions (excluding elastic)
 */
BaseBlockWithLocators( std::string name,
                       Iterator loc, Iterator data, Iterator end,
                       unsigned int ntr ) :
  Base( std::move( name ), loc, end ), ntr_( ntr ), iterator_( data ) {

  verifySize( this->begin(), this->iterator_, this->end(), this->ntr_ );
  this->generateBlocks();
}

BaseBlockWithLocators& operator=( const BaseBlockWithLocators& base ) {

  new (this) BaseBlockWithLocators( base );
  return *this;
}

BaseBlockWithLocators& operator=( BaseBlockWithLocators&& base ) {

  new (this) BaseBlockWithLocators( std::move( base ) );
  return *this;
}
