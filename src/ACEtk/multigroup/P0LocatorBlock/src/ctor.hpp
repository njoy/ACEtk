private:

/**
 *  @brief Private constructor
 */
P0LocatorBlock(
    std::vector< unsigned int > && locators,
    std::size_t nsec ) :
  Base( "P0L", generateXSS( std::move( locators ) ) ),
  nsec_( nsec ) {}

public:

P0LocatorBlock() = default;

P0LocatorBlock( const P0LocatorBlock& ) = default;
P0LocatorBlock( P0LocatorBlock&& ) = default;

P0LocatorBlock& operator=( const P0LocatorBlock& ) = default;
P0LocatorBlock& operator=( P0LocatorBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] locators    the locators for each P0 block
 */
P0LocatorBlock(
    std::vector< unsigned int > locators ) :
  P0LocatorBlock( std::move( locators ), locators.size() - 1 ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] p0l       the begin iterator of the P0L block in the XSS array
 *  @param[in] end       the end iterator of the P0L block in the XSS array
 *  @param[in] nsec      the number of secondary particle types
 */
P0LocatorBlock( Iterator p0l, Iterator end, unsigned int nsec ) :
  Base( "P0L", p0l, end ), nsec_( nsec ) {

  verifySize( this->begin(), this->end(), this->NSEC() );
}
