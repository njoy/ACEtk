private:

/**
 *  @brief Private constructor
 */
BaseElectronBlockWithLocators( std::string&& name, std::vector< Data >&& xs,
                               std::size_t n ) :
  Base( std::move( name ), Derived::generateXSS( std::move( xs ) ) ), n_( n ) {

  static_cast< Derived* >( this )->generateBlocks();
}

protected:

BaseElectronBlockWithLocators() = default;

BaseElectronBlockWithLocators( const BaseElectronBlockWithLocators& base ) :
  Base( base ), n_( base.n_ ), information_( base.information_ ),
  data_( base.data_ ) {

  if ( Base::owner() ) {

    this->data_.clear();
    static_cast< Derived* >( this )->generateBlocks();
  }
}

BaseElectronBlockWithLocators( BaseElectronBlockWithLocators&& base ) :
  Base( std::move( base ) ), n_( base.n_ ),
  information_( std::move( base.information_ ) ), data_( std::move( base.data_ ) ) {

  if ( Base::owner() ) {

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
BaseElectronBlockWithLocators( std::string name, std::vector< Data > data ) :
  BaseElectronBlockWithLocators( std::move( name ), std::move( data ), data.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] name     the block name
 *  @param[in] begin    the begin iterator of the block in the XSS array
 *  @param[in] end      the end iterator of the SIG block in the XSS array
 *  @param[in] n        the number of reactions (excluding elastic)
 */
BaseElectronBlockWithLocators( std::string name, Iterator begin, Iterator end,
                               unsigned int n ) :
  Base( std::move( name ), begin, end ), n_( n ) {

  static_cast< Derived* >( this )->generateBlocks();
}

BaseElectronBlockWithLocators& operator=( const BaseElectronBlockWithLocators& base ) {

  new (this) BaseElectronBlockWithLocators( base );
  return *this;
}

BaseElectronBlockWithLocators& operator=( BaseElectronBlockWithLocators&& base ) {

  new (this) BaseElectronBlockWithLocators( std::move( base ) );
  return *this;
}
