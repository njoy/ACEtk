private:

/**
 *  @brief Private constructor
 */
BlockWithLocators( std::string&& name, std::vector< Data >&& xs,
                   std::size_t n, bool locator ) :
  Base( std::move( name ), Derived::generateXSS( std::move( xs ), locator ) ),
  n_( n ), locator_( locator ) {

  this->iterator_ = this->begin() + this->N();
  static_cast< Derived* >( this )->generateBlocks();
}

protected:

BlockWithLocators() = default;

BlockWithLocators( const BlockWithLocators& base ) :
  Base( base ), n_( base.n_ ), locator_( base.locator_ ),
  iterator_( base.iterator_ ), data_( base.data_ ) {

  if ( Base::owner() ) {

    this->iterator_ = this->begin() + this->N();
    this->data_.clear();
    static_cast< Derived* >( this )->generateBlocks();
  }
}

BlockWithLocators( BlockWithLocators&& base ) :
  Base( std::move( base ) ), n_( base.n_ ), locator_( base.locator_ ),
  iterator_( base.iterator_ ), data_( std::move( base.data_ ) ) {

  if ( Base::owner() ) {

    this->iterator_ = this->begin() + this->N();
    this->data_.clear();
    static_cast< Derived* >( this )->generateBlocks();
  }
}

/**
 *  @brief Constructor for a block
 *
 *  @param[in] name       the block name
 *  @param[in] data       the data
 *  @param[in] locator    flag to indicate if the L values are to be interpreted
 *                        as locators or offsets
 */
BlockWithLocators( std::string name, std::vector< Data > data, bool locator = true ) :
  BlockWithLocators( std::move( name ), std::move( data ), data.size(), locator ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] name       the block name
 *  @param[in] loc        the begin iterator of the LSIG block in the XSS array
 *  @param[in] data       the begin iterator of the SIG block in the XSS array
 *  @param[in] end        the end iterator of the SIG block in the XSS array
 *  @param[in] n          the number of reactions (excluding elastic)
 *  @param[in] locator    flag to indicate if the L values are to be interpreted
 *                        as locators or offsets
 */
BlockWithLocators( std::string name,
                   Iterator loc, Iterator data, Iterator end,
                   unsigned int n, bool locator = true ) :
  Base( std::move( name ), loc, end ),
  n_( n ), locator_( locator ), iterator_( data ) {

  verifySize( this->begin(), this->iterator_, this->end(), this->N() );
  static_cast< Derived* >( this )->generateBlocks();
}

BlockWithLocators& operator=( const BlockWithLocators& base ) {

  new (this) BlockWithLocators( base );
  return *this;
}

BlockWithLocators& operator=( BlockWithLocators&& base ) {

  new (this) BlockWithLocators( std::move( base ) );
  return *this;
}
