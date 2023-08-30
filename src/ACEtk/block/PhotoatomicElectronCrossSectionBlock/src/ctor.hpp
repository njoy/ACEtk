PhotoatomicElectronCrossSectionBlock() = default;

PhotoatomicElectronCrossSectionBlock( const PhotoatomicElectronCrossSectionBlock& ) = default;
PhotoatomicElectronCrossSectionBlock( PhotoatomicElectronCrossSectionBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energies             the energy values
 *  @param[in] elastic              the elastic cross section values
 *  @param[in] bremsstrahlung       the Bremsstrahlung cross section values
 *  @param[in] excitation           the excitation cross section values
 *  @param[in] electroionisation    the electroionisation cross section values
 *                                  for each shell
 */
PhotoatomicElectronCrossSectionBlock( 
    std::vector< double > energies,
    std::vector< double > elastic,
    std::vector< double > bremsstrahlung,
    std::vector< double > excitation,
    std::vector< std::vector< double > > electroionisation ) :
  ArrayData( "ESZE",
             generateArrays( std::move( energies ), std::move( elastic ), 
                             std::move( bremsstrahlung ), std::move( excitation ),
                             std::move( electroionisation ) ) ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the ESZE block in the XSS array
 *  @param[in] end     the end iterator of the ESZE block in the XSS array
 *  @param[in] nssh    the number of electron shells
 *  @param[in] ne      the number of energy values
 */
PhotoatomicElectronCrossSectionBlock( Iterator begin, Iterator end, 
                                      unsigned int nssh, unsigned int ne ) :
  ArrayData( "ESZE", begin, end, ne, 6 + nssh ) {}

PhotoatomicElectronCrossSectionBlock& operator=( const PhotoatomicElectronCrossSectionBlock& ) = default;
PhotoatomicElectronCrossSectionBlock& operator=( PhotoatomicElectronCrossSectionBlock&& ) = default;
