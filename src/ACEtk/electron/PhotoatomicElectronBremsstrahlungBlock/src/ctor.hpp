PhotoatomicElectronBremsstrahlungBlock() = default;

PhotoatomicElectronBremsstrahlungBlock( const PhotoatomicElectronBremsstrahlungBlock& ) = default;
PhotoatomicElectronBremsstrahlungBlock( PhotoatomicElectronBremsstrahlungBlock&& ) = default;

/**
 *  @brief Constructor
 *
 *  @param[in] energies     the energy values
 *  @param[in] remaining    the average energy remaining after Bremsstrahlung
 */
PhotoatomicElectronBremsstrahlungBlock(
    std::vector< double > energies,
    std::vector< double > remaining ) :
  ArrayData( "BREML",
             std::vector< std::vector< double > > {

               std::move( energies ),
               std::move( remaining )
             } ) {}

/**
 *  @brief Constructor
 *
 *  @param[in] begin   the begin iterator of the BREML block in the XSS array
 *  @param[in] end     the end iterator of the BREML block in the XSS array
 *  @param[in] nxl     the number of energy values
 */
PhotoatomicElectronBremsstrahlungBlock( Iterator begin, Iterator end,
                                        unsigned int nbl ) :
  ArrayData( "BREML", begin, end, nbl, 2 ) {}

PhotoatomicElectronBremsstrahlungBlock& operator=( const PhotoatomicElectronBremsstrahlungBlock& ) = default;
PhotoatomicElectronBremsstrahlungBlock& operator=( PhotoatomicElectronBremsstrahlungBlock&& ) = default;
