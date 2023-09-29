private:

/**
 *  @brief Private constructor
 */
BaseAngularDistributionBlock( std::string&& name,
                              std::vector< DistributionData >&& xs,
                              std::size_t nr, bool zero ) :
  Base( std::move( name ), generateXSS( std::move( xs ) ) ),
  nr_( nr ), zero_index_( zero ) {

  this->iterator_ = this->begin() + this->nr_ + ( this->zero_index_ ? 1 : 0 );
  this->generateBlocks();
}

/**
 *  @brief Private constructor
 */
BaseAngularDistributionBlock( std::string&& name,
                              DistributionData&& zero,
                              std::vector< DistributionData >&& data,
                              std::size_t nr ) :
  BaseAngularDistributionBlock( std::move( name ),
                                insertZero( std::move( zero ),
                                            std::move( data ) ),
                                nr, true ) {}

protected:

BaseAngularDistributionBlock() = default;

BaseAngularDistributionBlock( const BaseAngularDistributionBlock& base ) :
  Base( base ), nr_( base.nr_ ), iterator_( base.iterator_ ),
  data_( base.data_ ), zero_index_( base.zero_index_ ) {

  if ( Base::owner() ) {

    this->data_.clear();
    this->iterator_ = this->begin() + this->nr_ + ( this->zero_index_ ? 1 : 0 );
    this->generateBlocks();
  }
}

BaseAngularDistributionBlock( BaseAngularDistributionBlock&& base ) :
  Base( std::move( base ) ), nr_( base.nr_ ), iterator_( base.iterator_ ),
  data_( std::move( base.data_ ) ), zero_index_( base.zero_index_ ) {

  if ( Base::owner() ) {

    this->data_.clear();
    this->iterator_ = this->begin() + this->nr_ + ( this->zero_index_ ? 1 : 0 );
    this->generateBlocks();
  }
}

/**
 *  @brief Constructor for a block without a zero index
 *
 *  @param[in] name    the block name
 *  @param[in] data    the data
 */
BaseAngularDistributionBlock( std::string name, std::vector< DistributionData > data ) :
  BaseAngularDistributionBlock( std::move( name ), std::move( data ),
                                data.size(), false ) {}

/**
 *  @brief Constructor for a block with a zero index
 *
 *  @param[in] name    the block name
 *  @param[in] zero    the data for index zero
 *  @param[in] data    the data
 */
BaseAngularDistributionBlock( std::string name, DistributionData zero,
                              std::vector< DistributionData > data ) :
  BaseAngularDistributionBlock( std::move( name ), std::move( zero ),
                                std::move( data ), data.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] name    the block name
 *  @param[in] loc     the begin iterator of the LSIG block in the XSS array
 *  @param[in] data    the begin iterator of the SIG block in the XSS array
 *  @param[in] end     the end iterator of the SIG block in the XSS array
 *  @param[in] nr     the number of reactions (excluding elastic)
 */
BaseAngularDistributionBlock( std::string name,
                              Iterator loc, Iterator data, Iterator end,
                              unsigned int nr, bool zero = false ) :
  Base( std::move( name ), loc, end ),
  nr_( nr ), iterator_( data ), zero_index_( zero ) {

  verifySize( this->begin(), this->iterator_, this->end(), this->nr_ );
  this->generateBlocks();
}

BaseAngularDistributionBlock& operator=( const BaseAngularDistributionBlock& base ) {

  new (this) BaseAngularDistributionBlock( base );
  return *this;
}

BaseAngularDistributionBlock& operator=( BaseAngularDistributionBlock&& base ) {

  new (this) BaseAngularDistributionBlock( std::move( base ) );
  return *this;
}
