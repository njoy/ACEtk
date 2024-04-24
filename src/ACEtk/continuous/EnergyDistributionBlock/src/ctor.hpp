private:

/**
 *  @brief Private constructor
 */
EnergyDistributionBlock( std::pair< std::vector< double >,
                                    std::vector< unsigned int > >&& xss,
                         std::vector< ReferenceFrame >&& frames,
                         std::size_t nr ) :
  Base( "DLW", std::move( xss.first ) ),
  nr_( nr ),
  tyr_( std::move( frames ), std::move( xss.second ) ) {

  this->iterator_ = this->begin() + this->nr_;
  this->generateBlocks();
}

/**
 *  @brief Private constructor
 */
EnergyDistributionBlock( std::vector< EnergyDistributionData >&& distributions,
                         std::vector< MultiplicityData >&& multiplicities,
                         std::vector< ReferenceFrame >&& frames,
                         std::size_t nr ) :
  EnergyDistributionBlock( generateXSS( std::move( distributions ),
                                        std::move( multiplicities ) ),
                           std::move( frames ), nr ) {}

public:

EnergyDistributionBlock() = default;

EnergyDistributionBlock( const EnergyDistributionBlock& base ) :
  Base( base ), nr_( base.nr_ ), iterator_( base.iterator_ ),
  tyr_( base.tyr_ ),
  data_( base.data_ ),
  multiplicities_( base.multiplicities_ ),
  frames_( base.frames_ ) {

  if ( Base::owner() ) {

    this->iterator_ = this->begin() + this->nr_;
    this->data_.clear();
    this->multiplicities_.clear();
    this->frames_.clear();
    this->generateBlocks();
  }
}

EnergyDistributionBlock( EnergyDistributionBlock&& base ) :
  Base( std::move( base ) ), nr_( base.nr_ ), iterator_( base.iterator_ ),
  tyr_( std::move( base.tyr_ ) ),
  data_( std::move( base.data_ ) ),
  multiplicities_( std::move( base.multiplicities_ ) ),
  frames_( std::move( base.frames_ ) ) {

  if ( Base::owner() ) {

    this->iterator_ = this->begin() + this->nr_;
    this->data_.clear();
    this->multiplicities_.clear();
    this->frames_.clear();
    this->generateBlocks();
  }
}

/**
 *  @brief Constructor
 *
 *  @param[in] distributions     the energy distribution data
 *  @param[in] multiplicities    the multiplicity data
 *  @param[in] frames            the reference frames
 */
EnergyDistributionBlock( std::vector< EnergyDistributionData > distributions,
                         std::vector< MultiplicityData > multiplicities,
                         std::vector< ReferenceFrame > frames ) :
  EnergyDistributionBlock( std::move( distributions ),
                           std::move( multiplicities ),
                           std::move( frames ),
                           distributions.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] ldlw    the begin iterator of the LDLW block in the XSS array
 *  @param[in] dlw     the begin iterator of the DLW block in the XSS array
 *  @param[in] end     the end iterator of the DLW block in the XSS array
 *  @param[in] nr      the number of reactions
 */
EnergyDistributionBlock( Iterator loc, Iterator data, Iterator end,
                         continuous::TYR tyr, unsigned int nr ) :
  Base( "DLW", loc, end ), nr_( nr ), iterator_( data ),
  tyr_( std::move( tyr ) ) {

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
