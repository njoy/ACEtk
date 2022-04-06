private:

/**
 *  @brief Private constructor
 */
EnergyDistributionBlock( std::vector< EnergyDistributionData >&& xs,
                         std::size_t nr ) :
  Base( "DLW", generateXSS( std::move( xs ) ) ),
  nr_( nr ) {

  this->iterator_ = this->begin() + this->nr_;
  this->generateBlocks();
}

public:

EnergyDistributionBlock() = default;

EnergyDistributionBlock( const EnergyDistributionBlock& base ) :
  Base( base ), nr_( base.nr_ ), iterator_( base.iterator_ ),
  data_( base.data_ ) {

  if ( Base::owner() ) {

    this->iterator_ = this->begin() + this->nr_;
    this->data_.clear();
    this->generateBlocks();
  }
}

EnergyDistributionBlock( EnergyDistributionBlock&& base ) :
  Base( std::move( base ) ), nr_( base.nr_ ), iterator_( base.iterator_ ),
  data_( std::move( base.data_ ) ) {

  if ( Base::owner() ) {

    this->iterator_ = this->begin() + this->nr_;
    this->data_.clear();
    this->generateBlocks();
  }
}

/**
 *  @brief Constructor
 *
 *  @param[in] distributions    the energy distribution data
 */
EnergyDistributionBlock( std::vector< EnergyDistributionData > distributions ) :
  EnergyDistributionBlock( std::move( distributions ), distributions.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] ldlw    the begin iterator of the LDLW block in the XSS array
 *  @param[in] dlw     the begin iterator of the DLW block in the XSS array
 *  @param[in] end     the end iterator of the DLW block in the XSS array
 *  @param[in] nr      the number of reactions
 */
EnergyDistributionBlock( Iterator loc, Iterator data, Iterator end,
                         unsigned int nr ) :
  Base( "DLW", loc, end ), nr_( nr ), iterator_( data ) {

  verifySize( this->begin(), this->iterator_, this->end(), this->nr_ );
  this->generateBlocks();
}

EnergyDistributionBlock& operator=( const EnergyDistributionBlock& base ) {

  new (this) EnergyDistributionBlock( base );
  return *this;
}

EnergyDistributionBlock& operator=( EnergyDistributionBlock&& base ) {

  new (this) EnergyDistributionBlock( std::move( base ) );
  return *this;
}
