MultiDistribution() = default;

MultiDistribution( const MultiDistribution& base ) :
  Base( base ), locb_( base.locb_ ),
  probabilities_( base.probabilities_ ),
  distributions_( base.distributions_ ) {

  if ( Base::owner() ) {

    this->probabilities_.clear();
    this->distributions_.clear();
    this->generateBlocks();
  }
}

MultiDistribution( MultiDistribution&& base ) :
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
MultiDistribution(
    std::string name,
    std::vector< DistributionProbability > probabilities,
    std::vector< DistributionData > distributions,
    std::size_t locb = 1 ) :
  Base( std::move( name ),
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
MultiDistribution( std::string name, std::size_t locb,
                   Iterator begin, Iterator end ) :
  Base( std::move( name ), begin, end ),
  locb_( locb ) {

  this->generateBlocks();
}

MultiDistribution& operator=( const MultiDistribution& base ) {

  new (this) MultiDistribution( base );
  return *this;
}

MultiDistribution& operator=( MultiDistribution&& base ) {

  new (this) MultiDistribution( std::move( base ) );
  return *this;
}
