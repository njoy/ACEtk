private:

/**
 *  @brief Private constructor
 */
AngularDistributionBlock( std::vector< DistributionData >&& distributions,
                          std::size_t nr, std::size_t offset ) :
  Base( "AND", generateXSS( std::move( distributions ) ) ),
  nr_( nr ),
  offset_( offset ) {

  this->and_ = this->begin() + this->nr_ + this->offset_;
}

/**
 *  @brief Private constructor
 */
AngularDistributionBlock( DistributionData&& elastic,
                          std::vector< DistributionData >&& distributions,
                          std::size_t nr ) :
  AngularDistributionBlock( insertElastic( std::move( elastic ),
                                           std::move( distributions ) ),
                            nr, 1 ) {}

public:

AngularDistributionBlock() = default;

AngularDistributionBlock( const AngularDistributionBlock& ) = default;
AngularDistributionBlock( AngularDistributionBlock&& ) = default;

/**
 *  @brief Constructor without elastic data
 *
 *  @param[in] distributions    the angular distribution data
 */
AngularDistributionBlock( std::vector< DistributionData > distributions ) :
  AngularDistributionBlock( std::move( distributions ),
                            distributions.size(), 0 ) {}

/**
 *  @brief Constructor with elastic data
 *
 *  @param[in] elastic          the angular distribution data for elastic
 *  @param[in] distributions    the angular distribution data
 */
AngularDistributionBlock( DistributionData elastic,
                          std::vector< DistributionData > distributions ) :
  AngularDistributionBlock( std::move( elastic ), std::move( distributions ),
                            distributions.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] land      the begin iterator of the LAND block in the XSS array
 *  @param[in] xand      the begin iterator of the AND block in the XSS array
 *  @param[in] end       the end iterator of the AND block in the XSS array
 *  @param[in] nr        the number of reactions producing the projectile
 *                       (excluding elastic)
 *  @param[in] offset    the index offset (1 with elastic, 0 without elastic)
 */
AngularDistributionBlock( Iterator land, Iterator xand, Iterator end,
                          unsigned int nr, std::size_t offset ) :
  Base( "AND", land, end ), nr_( nr ), and_( xand ), offset_( offset ) {

  verifySize( this->begin(), this->and_, this->end(), this->nr_, this->offset_ );
}

AngularDistributionBlock& operator=( const AngularDistributionBlock& ) = default;
AngularDistributionBlock& operator=( AngularDistributionBlock&& ) = default;
