private:

/**
 *  @brief Private constructor
 */
XPNLocatorBlock(
    std::vector< unsigned int > && locators,
    std::size_t nsec ) :
  Base( "XPNL", generateXSS( std::move( locators ) ) ),
  nsec_( nsec ) {}

public:

XPNLocatorBlock() = default;

XPNLocatorBlock( const XPNLocatorBlock& ) = default;
XPNLocatorBlock( XPNLocatorBlock&& ) = default;

XPNLocatorBlock& operator=( const XPNLocatorBlock& ) = default;
XPNLocatorBlock& operator=( XPNLocatorBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] locators    the locators for each XPN block
 */
XPNLocatorBlock(
    std::vector< unsigned int > locators ) :
  XPNLocatorBlock( std::move( locators ), locators.size() - 1 ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin     the begin iterator of the XPNL block in the XSS array
 *  @param[in] end       the end iterator of the XPNL block in the XSS array
 *  @param[in] nsec      the number of secondary particle types
 */
XPNLocatorBlock( Iterator begin, Iterator end, unsigned int nsec ) :
  Base( "XPNL", begin, end ), nsec_( nsec ) {

  verifySize( this->begin(), this->end(), this->NSEC() );
}
