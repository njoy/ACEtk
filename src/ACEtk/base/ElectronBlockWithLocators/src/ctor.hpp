private:

/**
 *  @brief Private constructor
 */
ElectronBlockWithLocators( std::string&& name, std::vector< Data >&& xs,
                           std::size_t n ) :
  Base( std::move( name ), Derived::generateXSS( std::move( xs ) ) ), n_( n ) {

  static_cast< Derived* >( this )->generateBlocks();
}

protected:

ElectronBlockWithLocators() = default;

ElectronBlockWithLocators( const ElectronBlockWithLocators& base ) :
  Base( base ), n_( base.n_ ), information_( base.information_ ),
  data_( base.data_ ) {

  if ( Base::owner() ) {

    static_cast< Derived* >( this )->generateBlocks();
  }
}

ElectronBlockWithLocators( ElectronBlockWithLocators&& base ) :
  Base( std::move( base ) ), n_( base.n_ ),
  information_( std::move( base.information_ ) ), data_( std::move( base.data_ ) ) {

  if ( Base::owner() ) {

    static_cast< Derived* >( this )->generateBlocks();
  }
}

/**
 *  @brief Constructor for a block
 *
 *  @param[in] name    the block name
 *  @param[in] data    the data
 */
ElectronBlockWithLocators( std::string name, std::vector< Data > data ) :
  ElectronBlockWithLocators( std::move( name ), std::move( data ), data.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] name     the block name
 *  @param[in] begin    the begin iterator of the block in the XSS array
 *  @param[in] end      the end iterator of the SIG block in the XSS array
 *  @param[in] n        the number of reactions (excluding elastic)
 */
ElectronBlockWithLocators( std::string name, Iterator begin, Iterator end,
                           unsigned int n ) :
  Base( std::move( name ), begin, end ), n_( n ) {

  static_cast< Derived* >( this )->generateBlocks();
}

ElectronBlockWithLocators& operator=( const ElectronBlockWithLocators& base ) {

  if ( this != &base ) {

    Base::operator=( base );
    this->n_ = base.n_;
    this->information_ = base.information_;
    this->data_ = base.data_;
    if ( Base::owner() ) {

      static_cast< Derived* >( this )->generateBlocks();
    }
  }
  return *this;
}

ElectronBlockWithLocators& operator=( ElectronBlockWithLocators&& base ) {

  if ( this != &base ) {

    Base::operator=( std::move( base ) );
    this->n_ = base.n_;
    this->information_ = std::move( base.information_ );
    this->data_ = std::move( base.data_ );
    if ( Base::owner() ) {

      static_cast< Derived* >( this )->generateBlocks();
    }
  }
  return *this;
}
