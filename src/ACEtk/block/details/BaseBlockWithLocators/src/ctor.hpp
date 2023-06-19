private:

/**
 *  @brief Private constructor
 */
BaseBlockWithLocators( std::string&& name, std::vector< Data >&& xs,
                       std::size_t nr ) :
  Base( std::move( name ), Derived::generateXSS( std::move( xs ) ) ),
  nr_( nr ) {

  this->iterator_ = this->begin() + this->nr_;
  static_cast< Derived* >( this )->generateBlocks();
}

protected:

BaseBlockWithLocators() = default;

BaseBlockWithLocators( const BaseBlockWithLocators& base ) :
  Base( base ), nr_( base.nr_ ), iterator_( base.iterator_ ),
  data_( base.data_ ) {

  if ( Base::owner() ) {

    this->iterator_ = this->begin() + this->nr_;
    this->data_.clear();
    static_cast< Derived* >( this )->generateBlocks();
  }
}

BaseBlockWithLocators( BaseBlockWithLocators&& base ) :
  Base( std::move( base ) ), nr_( base.nr_ ), iterator_( base.iterator_ ),
  data_( std::move( base.data_ ) ) {

  if ( Base::owner() ) {

    this->iterator_ = this->begin() + this->nr_;
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
 *  @param[in] nr     the number of reactions (excluding elastic)
 */
BaseBlockWithLocators( std::string name,
                       Iterator loc, Iterator data, Iterator end,
                       unsigned int nr ) :
  Base( std::move( name ), loc, end ),
  nr_( nr ), iterator_( data ) {

  verifySize( this->begin(), this->iterator_, this->end(), this->nr_ );
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
