SecondaryParticleProductionCrossSectionBlock() = default;

SecondaryParticleProductionCrossSectionBlock( const SecondaryParticleProductionCrossSectionBlock& ) = default;
SecondaryParticleProductionCrossSectionBlock( SecondaryParticleProductionCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] xs    the cross section data
 */
SecondaryParticleProductionCrossSectionBlock( std::vector< TabulatedSecondaryParticleMultiplicity > xs ) :
  BlockWithLocators( "SIGH", std::move( xs ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] lsigh    the begin iterator of the LSIGH block in the XSS array
 *  @param[in] sigh     the begin iterator of the SIGH block in the XSS array
 *  @param[in] end      the end iterator of the SIGH block in the XSS array
 *  @param[in] np       the number of reactions
 */
SecondaryParticleProductionCrossSectionBlock( Iterator lsigh, Iterator sigh,
                                              Iterator end, unsigned int np ) :
  BlockWithLocators( "SIGH", lsigh, sigh, end, np ) {}

SecondaryParticleProductionCrossSectionBlock& operator=( const SecondaryParticleProductionCrossSectionBlock& ) = default;
SecondaryParticleProductionCrossSectionBlock& operator=( SecondaryParticleProductionCrossSectionBlock&& ) = default;
