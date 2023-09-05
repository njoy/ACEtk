private:

/**
 *  @brief Private constructor
 */
BaseBlockWithLocators( std::string&& name, std::vector< Data >&& xs,
                       std::size_t n ) :
  Base( std::move( name ), Derived::generateXSS( std::move( xs ) ) ),
  n_( n ) {

  this->iterator_ = this->begin() + this->N();
  static_cast< Derived* >( this )->generateBlocks();
}

protected:

BaseBlockWithLocators() = default;

BaseBlockWithLocators( const BaseBlockWithLocators& base ) :
  Base( base ), n_( base.n_ ), iterator_( base.iterator_ ),
  data_( base.data_ ) {

  if ( Base::owner() ) {

    this->iterator_ = this->begin() + this->N();
    this->data_.clear();
    static_cast< Derived* >( this )->generateBlocks();
  }
}

BaseBlockWithLocators( BaseBlockWithLocators&& base ) :
  Base( std::move( base ) ), n_( base.n_ ), iterator_( base.iterator_ ),
  data_( std::move( base.data_ ) ) {

  if ( Base::owner() ) {

    this->iterator_ = this->begin() + this->N();
    this->data_.clear();
    static_cast< Derived* >( this )->generateBlocks();
  }
}

/**
 *  @brief Constructor for a block
 *
 *  @param[in] name    the block name
 *  @param[in] data    the data
 */
BaseBlockWithLocators( std::string name, std::vector< Data > data ) :
  BaseBlockWithLocators( std::move( name ), std::move( data ), data.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] name    the block name
 *  @param[in] loc     the begin iterator of the LSIG block in the XSS array
 *  @param[in] data    the begin iterator of the SIG block in the XSS array
 *  @param[in] end     the end iterator of the SIG block in the XSS array
 *  @param[in] n       the number of reactions (excluding elastic)
 */
BaseBlockWithLocators( std::string name,
                       Iterator loc, Iterator data, Iterator end,
                       unsigned int n ) :
  Base( std::move( name ), loc, end ),
  n_( n ), iterator_( data ) {

  verifySize( this->begin(), this->iterator_, this->end(), this->N() );
  static_cast< Derived* >( this )->generateBlocks();
}

BaseBlockWithLocators& operator=( const BaseBlockWithLocators& base ) {

  new (this) BaseBlockWithLocators( base );
  return *this;
}

BaseBlockWithLocators& operator=( BaseBlockWithLocators&& base ) {

  new (this) BaseBlockWithLocators( std::move( base ) );
  return *this;
}
