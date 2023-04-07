MultiDistributionData() = default;

MultiDistributionData( const MultiDistributionData& base ) :
  Base( base ) {

  this->generateBlocks();
}

MultiDistributionData( MultiDistributionData&& base ) :
  Base( std::move( base ) ) {

  this->generateBlocks();
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
  Base( "DLW::MultiDistributionData",
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
  Base( "DLW::MultiDistributionData", begin, end ),
  locb_( locb ) {

//  std::size_t nr = static_cast< std::size_t >( this->XSS( 1 ) );
//  std::size_t ne = static_cast< std::size_t >( this->XSS( 1 + 2 * nr + 1 ) );
//  std::size_t nb = static_cast< std::size_t >( this->XSS( 1 + 2 * nr + 1 + ne + 1 ) );
//  verifySize( this->begin(), this->end(), nr, ne, nb );
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
