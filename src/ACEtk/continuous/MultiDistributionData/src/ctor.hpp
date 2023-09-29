MultiDistributionData() = default;

MultiDistributionData( const MultiDistributionData& base ) :
  Base( base ), locb_( base.locb_ ),
  probabilities_( base.probabilities_ ),
  distributions_( base.distributions_ ) {

  if ( Base::owner() ) {

    this->probabilities_.clear();
    this->distributions_.clear();
    this->generateBlocks();
  }
}

MultiDistributionData( MultiDistributionData&& base ) :
  Base( std::move( base ) ), locb_( base.locb_ ),
  probabilities_( std::move( base.probabilities_ ) ),
  distributions_( std::move( base.distributions_ ) ) {

  if ( Base::owner() ) {

    this->probabilities_.clear();
    this->distributions_.clear();
    this->generateBlocks();
  }
}

/**
 *  @brief Constructor
 *
 *  @param[in] probabilities    the probabilities
 *  @param[in] distributions    the distributions
 *  @param[in] locb             the starting xss index with respect to the superblock
 */
MultiDistributionData(
    std::vector< DistributionProbability > probabilities,
    std::vector< DistributionData > distributions,
    std::size_t locb = 1 ) :
  Base( "MultiDistributionData",
        generateXSS( std::move( probabilities ), std::move( distributions ),
                     locb ) ),
  locb_( locb ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] locb    the starting xss index with respect to the superblock
 *  @param[in] sig     the begin iterator of the block in the XSS array
 *  @param[in] end     the end iterator of the block in the XSS array
 */
MultiDistributionData( std::size_t locb, Iterator begin, Iterator end ) :
  Base( "MultiDistributionData", begin, end ),
  locb_( locb ) {

  this->generateBlocks();
}

MultiDistributionData& operator=( const MultiDistributionData& base ) {

  new (this) MultiDistributionData( base );
  return *this;
}

MultiDistributionData& operator=( MultiDistributionData&& base ) {

  new (this) MultiDistributionData( std::move( base ) );
  return *this;
}
