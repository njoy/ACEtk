private:

/**
 *  @brief Private constructor
 */
DelayedNeutronPrecursorBlock( std::vector< DelayedNeutronPrecursorData >&& groups,
                              std::size_t npcr ) :
  Base( "BDD", generateXSS( std::move( groups ) ) ),
  npcr_( npcr ) {

  this->generateBlocks();
}

public:

DelayedNeutronPrecursorBlock() = default;

DelayedNeutronPrecursorBlock( const DelayedNeutronPrecursorBlock& base ) :
  Base( base ), npcr_( base.npcr_ ),
  data_( base.data_ ) {

  if ( Base::owner() ) {

    this->data_.clear();
    this->generateBlocks();
  }
}

DelayedNeutronPrecursorBlock( DelayedNeutronPrecursorBlock&& base ) :
  Base( std::move( base ) ), npcr_( base.npcr_ ),
  data_( std::move( base.data_ ) ) {

  if ( Base::owner() ) {

    this->data_.clear();
    this->generateBlocks();
  }
}

/**
 *  @brief Constructor
 *
 *  @param[in] groups    the data for the precursor groups
 */
DelayedNeutronPrecursorBlock( std::vector< DelayedNeutronPrecursorData > groups ) :
  DelayedNeutronPrecursorBlock( std::move( groups ), groups.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] bdd    the begin iterator of the BDD block in the XSS array
 *  @param[in] end    the end iterator of the BDD block in the XSS array
 *  @param[in] npcr   the number of delayed precursor groups
 */
DelayedNeutronPrecursorBlock( Iterator bdd, Iterator end, unsigned int npcr ) :
  Base( "BDD", bdd, end ), npcr_( npcr ) {

  this->generateBlocks();
}

DelayedNeutronPrecursorBlock& operator=( const DelayedNeutronPrecursorBlock& base ) {

  new (this) DelayedNeutronPrecursorBlock( base );
  return *this;
}

DelayedNeutronPrecursorBlock& operator=( DelayedNeutronPrecursorBlock&& base ) {

  new (this) DelayedNeutronPrecursorBlock( std::move( base ) );
  return *this;
}
