private:

/**
 *  @brief Private constructor
 */
AngularDistributionBlock( std::vector< DistributionData >&& distributions,
                          std::size_t nr ) :
  Base( "AND", generateXSS( std::move( distributions ) ) ),
  nr_( nr ) {

  this->and_ = this->begin() + this->nr_ + 1;
}

 public:

AngularDistributionBlock() = default;

AngularDistributionBlock( const AngularDistributionBlock& ) = default;
AngularDistributionBlock( AngularDistributionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] xs    the cross section data
 */
AngularDistributionBlock( std::vector< DistributionData >&& distributions ) :
  AngularDistributionBlock( std::move( distributions ),
                            distributions.size() - 1 ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] land    the begin iterator of the LAND block in the XSS array
 *  @param[in] xand    the begin iterator of the AND block in the XSS array
 *  @param[in] end     the end iterator of the AND block in the XSS array
 *  @param[in] nr      the number of reactions producing the projectile
 *                     (excluding elastic)
 */
AngularDistributionBlock( Iterator land, Iterator xand, Iterator end,
                          unsigned int nr ) :
  Base( "AND", land, end ), nr_( nr ), and_( xand ) {

  verifySize( this->begin(), this->and_, this->end(), this->nr_ );
}

AngularDistributionBlock& operator=( const AngularDistributionBlock& ) = default;
AngularDistributionBlock& operator=( AngularDistributionBlock&& ) = default;
