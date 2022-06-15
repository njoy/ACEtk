private:

/**
 *  @brief Private constructor
 */
PhotoNuclearSecondaryParticleLocatorBlock(
    std::vector< unsigned int >&& types,
    std::vector< unsigned int >&& numbers,
    std::vector< std::array< unsigned int, 10 > >&& locators,
    std::size_t ntype ) :
  Base( "IXSU", generateXSS( std::move( types ), std::move( numbers ),
                             std::move( locators ) ) ),
  ntype_( ntype ) {}

public:

PhotoNuclearSecondaryParticleLocatorBlock() = default;

PhotoNuclearSecondaryParticleLocatorBlock( const PhotoNuclearSecondaryParticleLocatorBlock& ) = default;
PhotoNuclearSecondaryParticleLocatorBlock( PhotoNuclearSecondaryParticleLocatorBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] types       the particle types
 *  @param[in] numbers     the number of reactions for each particle type
 *  @param[in] locators    the locators for each secondary particle type
 */
PhotoNuclearSecondaryParticleLocatorBlock(
    std::vector< unsigned int > types,
    std::vector< unsigned int > numbers,
    std::vector< std::array< unsigned int, 10 > > locators ) :
  PhotoNuclearSecondaryParticleLocatorBlock(
    std::move( types ), std::move( numbers ),
    std::move( locators ), locators.size() ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] ixs     the begin iterator of the IXS block in the XSS array
 *  @param[in] end     the end iterator of the IXS block in the XSS array
 *  @param[in] ntype   the number of secondary particle types
 */
PhotoNuclearSecondaryParticleLocatorBlock( Iterator ixs, Iterator end,
                                           unsigned int ntype ) :
  Base( "IXSU", ixs, end ), ntype_( ntype ) {

  verifySize( this->begin(), this->end(), this->NTYPE() );
}

PhotoNuclearSecondaryParticleLocatorBlock& operator=( const PhotoNuclearSecondaryParticleLocatorBlock& ) = default;
PhotoNuclearSecondaryParticleLocatorBlock& operator=( PhotoNuclearSecondaryParticleLocatorBlock&& ) = default;
