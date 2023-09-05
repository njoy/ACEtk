PhotonuclearPrincipalCrossSectionBlock() = default;

PhotonuclearPrincipalCrossSectionBlock( const PhotonuclearPrincipalCrossSectionBlock& ) = default;
PhotonuclearPrincipalCrossSectionBlock( PhotonuclearPrincipalCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energies         the energy values
 *  @param[in] total            the total cross section values
 *  @param[in] elastic          the elastic cross section values
 *  @param[in] heating          the average heating cross section values
 */
PhotonuclearPrincipalCrossSectionBlock( std::vector< double > energies,
                                        std::vector< double > total,
                                        std::vector< double > elastic,
                                        std::vector< double > heating ) :
  ArrayData( "ESZU",
             std::move( energies ), std::move( total ),
             std::move( elastic ), std::move( heating ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] energies         the energy values
 *  @param[in] total            the total cross section values
 *  @param[in] heating          the average heating cross section values
 */
PhotonuclearPrincipalCrossSectionBlock( std::vector< double > energies,
                                        std::vector< double > total,
                                        std::vector< double > heating ) :
  ArrayData( "ESZU",
             std::move( energies ), std::move( total ),
             std::move( heating ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the ESZ block in the XSS array
 *  @param[in] end     the end iterator of the ESZ block in the XSS array
 *  @param[in] nes     the number of energy points
 */
PhotonuclearPrincipalCrossSectionBlock( Iterator begin, Iterator end,
                                        unsigned int nes, unsigned int size ) :
  ArrayData( "ESZU", begin, end, nes, size ) {}

PhotonuclearPrincipalCrossSectionBlock& operator=( const PhotonuclearPrincipalCrossSectionBlock& ) = default;
PhotonuclearPrincipalCrossSectionBlock& operator=( PhotonuclearPrincipalCrossSectionBlock&& ) = default;
