PhotoatomicPrincipalCrossSectionBlock() = default;

PhotoatomicPrincipalCrossSectionBlock( const PhotoatomicPrincipalCrossSectionBlock& ) = default;
PhotoatomicPrincipalCrossSectionBlock( PhotoatomicPrincipalCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energies          the energy values
 *  @param[in] incoherent        the incoherent cross section values
 *  @param[in] coherent          the coherent cross section values
 *  @param[in] photoelectric     the photo-electric cross section values
 *  @param[in] pairproduction    the pair production cross section values
 */
PhotoatomicPrincipalCrossSectionBlock( std::vector< double > energies,
                                       std::vector< double > incoherent,
                                       std::vector< double > coherent,
                                       std::vector< double > photoelectric,
                                       std::vector< double > pairproduction ) :
  ArrayData( "ESZG",
             std::move( energies ), std::move( incoherent ),
             std::move( coherent ), std::move( photoelectric ),
             std::move( pairproduction ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the ESZG block in the XSS array
 *  @param[in] end     the end iterator of the ESZG block in the XSS array
 *  @param[in] nes     the number of energy points
 */
PhotoatomicPrincipalCrossSectionBlock( Iterator begin, Iterator end,
                                       unsigned int nes ) :
  ArrayData( "ESZG", begin, end, nes, 5 ) {}

PhotoatomicPrincipalCrossSectionBlock& operator=( const PhotoatomicPrincipalCrossSectionBlock& ) = default;
PhotoatomicPrincipalCrossSectionBlock& operator=( PhotoatomicPrincipalCrossSectionBlock&& ) = default;
