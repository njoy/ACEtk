private:

/**
 *  @brief Private constructor
 */
PNLocatorBlock(
    std::vector< unsigned int > && locators,
    std::size_t nsec ) :
  Base( "PNL", generateXSS( std::move( locators ) ) ),
  nsec_( nsec ) {}

public:

PNLocatorBlock() = default;

PNLocatorBlock( const PNLocatorBlock& ) = default;
PNLocatorBlock( PNLocatorBlock&& ) = default;

PNLocatorBlock& operator=( const PNLocatorBlock& ) = default;
PNLocatorBlock& operator=( PNLocatorBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] locators    the locators for each PN block
 */
PNLocatorBlock(
    std::vector< unsigned int > locators ) :
  PNLocatorBlock( std::move( locators ), locators.size() - 1 ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin     the begin iterator of the PNL block in the XSS array
 *  @param[in] end       the end iterator of the PNL block in the XSS array
 *  @param[in] nsec      the number of secondary particle types
 */
PNLocatorBlock( Iterator begin, Iterator end, unsigned int nsec ) :
  Base( "PNL", begin, end ), nsec_( nsec ) {

  verifySize( this->begin(), this->end(), this->NSEC() );
}
