// private:
//
// /**
//  *  @brief Private constructor
//  */
// AngularDistributionBlock( std::vector< CrossSectionData >&& xs, std::size_t ntr ) :
//   Base( "SIG", generateXSS( std::move( xs ) ) ),
//   ntr_( ntr ) {
//
//   this->sig_ = this->begin() + this->ntr_;
// }
//
// public:

AngularDistributionBlock() = default;

AngularDistributionBlock( const AngularDistributionBlock& ) = default;
AngularDistributionBlock( AngularDistributionBlock&& ) = default;

// /**
//  *  @brief Constructor
//  *
//  *  @param[in] xs    the cross section data
//  */
// AngularDistributionBlock( std::vector< CrossSectionData >&& xs ) :
//   AngularDistributionBlock( std::move( xs ), xs.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] land    the begin iterator of the LAND block in the XSS array
 *  @param[in] xand    the begin iterator of the AND block in the XSS array
 *  @param[in] end     the end iterator of the AND block in the XSS array
 *  @param[in] ntr     the number of reactions (excluding elastic)
 */
AngularDistributionBlock( Iterator land, Iterator xand, Iterator end,
                          unsigned int ntr ) :
  Base( "AND", land, end ), ntr_( ntr ), and_( xand ) {

  verifySize( this->begin(), this->and_, this->end(), this->ntr_ );
}

AngularDistributionBlock& operator=( const AngularDistributionBlock& ) = default;
AngularDistributionBlock& operator=( AngularDistributionBlock&& ) = default;
