ProbabilityTableBlock() = default;

ProbabilityTableBlock( const ProbabilityTableBlock& base ) :
  Base( base ), data_( base.data_ ) {

  if ( Base::owner() ) {

    this->data_.clear();
    this->generateBlocks();
  }
}

ProbabilityTableBlock( ProbabilityTableBlock&& base ) :
  Base( std::move( base ) ), data_( std::move( base.data_ ) ) {

  if ( Base::owner() ) {

    this->data_.clear();
    this->generateBlocks();
  }
}

/**
 *  @brief Constructor
 *
 *  @param[in] interpolation    the interpolation type
 *  @param[in] inelastic        the inelastic competition flag
 *  @param[in] absorption       the absorption competition flag
 *  @param[in] type             the probability table type
 *  @param[in] tables           the probability tables
 */
ProbabilityTableBlock( unsigned int interpolation, int inelastic,
                       int absorption, unsigned int type,
                       std::vector< ProbabilityTable > tables ) :
  Base( "UNR", generateXSS( interpolation, inelastic, absorption, type,
                            std::move( tables ) ) ) {

  this->generateBlocks();
}

/**
 *  @brief Constructor
 *
 *  @param[in] bdd    the begin iterator of the BDD block in the XSS array
 *  @param[in] end    the end iterator of the BDD block in the XSS array
 *  @param[in] npcr   the number of delayed probability tables
 */
ProbabilityTableBlock( Iterator bdd, Iterator end ) :
  Base( "UNR", bdd, end ) {

  this->generateBlocks();
}

ProbabilityTableBlock& operator=( const ProbabilityTableBlock& base ) {

  new (this) ProbabilityTableBlock( base );
  return *this;
}

ProbabilityTableBlock& operator=( ProbabilityTableBlock&& base ) {

  new (this) ProbabilityTableBlock( std::move( base ) );
  return *this;
}
