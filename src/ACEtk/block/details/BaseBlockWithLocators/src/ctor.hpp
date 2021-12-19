private:

/**
 *  @brief Private constructor
 */
BaseBlockWithLocators( std::string&& name, std::vector< Data >&& xs,
                       std::size_t nr, bool zero ) :
  Base( std::move( name ), Derived::generateXSS( std::move( xs ) ) ),
  nr_( nr ), zero_index_( zero ) {

  this->iterator_ = this->begin() + this->nr_ + ( this->zero_index_ ? 1 : 0 );
  this->generateBlocks();
}

/**
 *  @brief Private constructor
 */
BaseBlockWithLocators( std::string&& name,
                       Data&& zero,
                       std::vector< Data >&& data,
                       std::size_t nr ) :
  BaseBlockWithLocators( std::move( name ),
                         insertZero( std::move( zero ),
                                     std::move( data ) ),
                         nr, true ) {}

public:

BaseBlockWithLocators() = default;

BaseBlockWithLocators( const BaseBlockWithLocators& base ) :
  Base( base ), nr_( base.nr_ ), zero_index_( base.zero_index_ ) {

  this->iterator_ = this->begin() + this->nr_ + ( this->zero_index_ ? 1 : 0 );
  this->generateBlocks();
}

BaseBlockWithLocators( BaseBlockWithLocators&& base ) :
  Base( std::move( base ) ), nr_( base.nr_ ), zero_index_( base.zero_index_ ) {

  this->iterator_ = this->begin() + this->nr_ + ( this->zero_index_ ? 1 : 0 );
  this->generateBlocks();
}

/**
 *  @brief Constructor for a block without a zero index
 *
 *  @param[in] name    the block name
 *  @param[in] data    the data
 */
BaseBlockWithLocators( std::string name, std::vector< Data > data ) :
  BaseBlockWithLocators( std::move( name ), std::move( data ), data.size(),
                         false ) {}

/**
 *  @brief Constructor for a block with a zero index
 *
 *  @param[in] name    the block name
 *  @param[in] zero    the data for index zero
 *  @param[in] data    the data
 */
BaseBlockWithLocators( std::string name, Data zero, std::vector< Data > data ) :
  BaseBlockWithLocators( std::move( name ), std::move( zero ),
                         std::move( data ), data.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] name    the block name
 *  @param[in] loc     the begin iterator of the LSIG block in the XSS array
 *  @param[in] data    the begin iterator of the SIG block in the XSS array
 *  @param[in] end     the end iterator of the SIG block in the XSS array
 *  @param[in] nr     the number of reactions (excluding elastic)
 */
BaseBlockWithLocators( std::string name,
                       Iterator loc, Iterator data, Iterator end,
                       unsigned int nr, bool zero = false ) :
  Base( std::move( name ), loc, end ),
  nr_( nr ), iterator_( data ), zero_index_( zero ) {

  verifySize( this->begin(), this->iterator_, this->end(), this->nr_ );
  this->generateBlocks();
}

BaseBlockWithLocators& operator=( const BaseBlockWithLocators& base ) {

  new (this) BaseBlockWithLocators( base );
  return *this;
}

BaseBlockWithLocators& operator=( BaseBlockWithLocators&& base ) {

  new (this) BaseBlockWithLocators( std::move( base ) );
  return *this;
}
