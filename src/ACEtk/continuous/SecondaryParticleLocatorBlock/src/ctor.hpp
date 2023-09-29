private:

/**
 *  @brief Private constructor
 */
SecondaryParticleLocatorBlock(
    std::vector< std::array< unsigned int, 10 > >&& locators,
    std::size_t ntype ) :
  Base( "IXS", generateXSS( std::move( locators ) ) ),
  ntype_( ntype ) {}

public:

SecondaryParticleLocatorBlock() = default;

SecondaryParticleLocatorBlock( const SecondaryParticleLocatorBlock& ) = default;
SecondaryParticleLocatorBlock( SecondaryParticleLocatorBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] locators    the locators for each secondary particle type
 */
SecondaryParticleLocatorBlock(
    std::vector< std::array< unsigned int, 10 > > locators ) :
  SecondaryParticleLocatorBlock( std::move( locators ), locators.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] ixs     the begin iterator of the IXS block in the XSS array
 *  @param[in] end     the end iterator of the IXS block in the XSS array
 *  @param[in] ntype   the number of secondary particle types
 */
SecondaryParticleLocatorBlock( Iterator ixs, Iterator end, unsigned int ntype ) :
  Base( "IXS", ixs, end ), ntype_( ntype ) {

  verifySize( this->begin(), this->end(), this->NTYPE() );
}

SecondaryParticleLocatorBlock& operator=( const SecondaryParticleLocatorBlock& ) = default;
SecondaryParticleLocatorBlock& operator=( SecondaryParticleLocatorBlock&& ) = default;
