PrincipalCrossSectionBlock() = default;

PrincipalCrossSectionBlock( const PrincipalCrossSectionBlock& ) = default;
PrincipalCrossSectionBlock( PrincipalCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energies         the energy values
 *  @param[in] total            the total cross section values
 *  @param[in] disappearance    the projectile disappearance cross section values
 *  @param[in] elastic          the elastic cross section values
 *  @param[in] heating          the average heating cross section values
 */
PrincipalCrossSectionBlock( std::vector< double > energies,
                            std::vector< double > total,
                            std::vector< double > disappearance,
                            std::vector< double > elastic,
                            std::vector< double > heating ) :
  ArrayData( "ESZ",
             std::move( energies ), std::move( total ),
             std::move( disappearance ), std::move( elastic ),
             std::move( heating ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] esz   the begin iterator of the ESZ block in the XSS array
 *  @param[in] end   the end iterator of the ESZ block in the XSS array
 *  @param[in] nes   the number of energy points
 */
PrincipalCrossSectionBlock( Iterator esz, Iterator end, unsigned int nes ) :
  ArrayData( "ESZ", esz, end, nes, 5 ) {}

PrincipalCrossSectionBlock& operator=( const PrincipalCrossSectionBlock& ) = default;
PrincipalCrossSectionBlock& operator=( PrincipalCrossSectionBlock&& ) = default;
